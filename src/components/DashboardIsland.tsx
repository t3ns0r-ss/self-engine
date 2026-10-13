import { useState, type ReactNode } from 'react';
import { MISTAKE_LABELS, REVIEW_OFFSETS, addDays, getSettings, getTopics, resolveDue, saveProblem, today, type Mistake } from '../lib/storage';
import { useStore } from '../lib/useStore';
import { url } from '../lib/url';
import { resolvedSince } from '../lib/sync/core';
import { failingRuns, syncPlatform } from '../lib/sync/runner';
import { isSolvedView } from '../lib/sync/status';
import { useSync } from '../lib/sync/useStatuses';
import LogPanel from './LogPanel';

export type DashTopic = {
  id: string; order: number; title: string; href: string; hasLesson: boolean; hasCheckpoint: boolean;
  ladder: { id: string; label: string }[]; reviews: string[][];
};
export type DashProblem = { title: string; url: string; topic: string; card: string };

export default function DashboardIsland({ topics, problems }: { topics: DashTopic[]; problems: Record<string, DashProblem> }) {
  const { logs, status: st, entry, profiles } = useSync();
  const [logOpen, setLogOpen] = useState<string | null>(null);
  const [syncing, setSyncing] = useState(false);
  const [syncMsg, setSyncMsg] = useState('');
  const topicState = useStore(getTopics, {});
  const settings = useStore(getSettings, {});
  const now = today();
  const current = topics.find((t) => t.id === settings.currentTopic);

  // Due reviews: a set is due from its date until every problem in it has a logged status.
  const dueReviews = topics.flatMap((t) => {
    const passed = topicState[t.id]?.checkpointPassedOn;
    if (!passed) return [];
    return ([1, 2, 3] as const)
      .map((s) => ({ t, s, due: addDays(passed, REVIEW_OFFSETS[s]), ids: t.reviews[s - 1] }))
      .filter((r) => r.ids.length && r.due <= now && r.ids.some((id) => !st(id).status));
  });
  const allResolves = Object.entries(logs)
    .map(([id, log]) => ({ id, due: resolveDue(log) }))
    .filter((r) => r.due && r.due <= now && problems[r.id]);
  // A re-solve is done automatically when a platform shows an accepted submission at or after its due date (Section 9).
  const detected = allResolves.filter((r) => !logs[r.id]?.resolveUndone && resolvedSince(entry(r.id), Date.parse(`${r.due}T00:00:00Z`) / 1000));
  const detectedIds = new Set(detected.map((r) => r.id));
  const dueResolves = allResolves.filter((r) => !detectedIds.has(r.id));

  // Synced solves with no minutes or mistake category logged: the log is what drives the mistake summary.
  const needsLog = topics.flatMap((t) => t.ladder).filter((p) => problems[p.id] && st(p.id).source === 'sync' && isSolvedView(st(p.id)) && !logs[p.id]?.minutes && !logs[p.id]?.mistake);

  // Sync line and error banners.
  const linked = [
    profiles.codeforces && { key: 'cf' as const, name: 'Codeforces' },
    profiles.atcoder && { key: 'ac' as const, name: 'AtCoder' },
  ].filter(Boolean) as { key: 'cf' | 'ac'; name: string }[];
  const lastSync = Math.max(0, profiles.codeforces?.lastSyncAt ?? 0, profiles.atcoder?.lastSyncAt ?? 0);
  const minutesAgo = lastSync ? Math.max(0, Math.round((Date.now() / 1000 - lastSync) / 60)) : null;
  const failing = linked.map((l) => ({ ...l, ...failingRuns(l.key) })).filter((f) => f.count >= 3);
  async function syncNow() {
    setSyncing(true);
    setSyncMsg('');
    const results = await Promise.all(linked.map(async (l) => ({ name: l.name, r: await syncPlatform(l.key) })));
    setSyncing(false);
    const failed = results.filter((x) => x.r.error);
    const added = results.reduce((n, x) => n + x.r.added, 0);
    setSyncMsg(failed.length ? failed.map((x) => `${x.name}: ${x.r.error}`).join(' ') : added ? `Synced: ${added} new submission${added === 1 ? '' : 's'}.` : 'Synced: already up to date.');
  }

  // Mistakes in the last 30 days.
  const since = addDays(now, -30);
  const recent = Object.entries(logs).filter(([, l]) => l.mistake && l.date && l.date >= since);
  const counts = new Map<Mistake, number>();
  for (const [, l] of recent) counts.set(l.mistake!, (counts.get(l.mistake!) ?? 0) + 1);
  const recCards = new Map<string, number>();
  for (const [id, l] of recent)
    if (l.mistake === 'recognition' && problems[id]) {
      const k = `${problems[id].card} (${problems[id].topic})`;
      recCards.set(k, (recCards.get(k) ?? 0) + 1);
    }
  const topRec = [...recCards.entries()].sort((a, b) => b[1] - a[1]).slice(0, 3);

  // Next step.
  let next: ReactNode;
  if (!current) {
    next = <>Open <a href={topics[0].href}>{topics[0].id} {topics[0].title}</a> and press "Make this my current topic".</>;
  } else {
    const open = current.ladder.find((p) => !isSolvedView(st(p.id)));
    const after = topics.find((t) => t.order === current.order + 1);
    if (open) next = <>Next: <a href={current.href}>{current.hasLesson ? `finish ${open.label}` : open.label}</a>.</>;
    else if (current.hasCheckpoint && !topicState[current.id]?.checkpointPassedOn) next = <>Take the <a href={`${current.href}#13-checkpoint`}>{current.id} checkpoint</a>.</>;
    else if (after) next = <>Move on to <a href={after.href}>{after.id} {after.title}</a>.</>;
    else next = <>You have finished the programme. Keep doing contests and upsolving.</>;
  }

  const solved = current ? current.ladder.filter((p) => isSolvedView(st(p.id))).length : 0;
  return (
    <div className="dashboard">
      {failing.map((f) => (
        <p key={f.key} className="sync-banner" role="alert">
          {f.name} sync failing since {f.since ? new Date(f.since * 1000).toLocaleString() : 'a while ago'}: {f.message}
        </p>
      ))}
      {linked.length > 0 && (
        <p className="muted">
          {minutesAgo === null ? 'Not synced yet' : minutesAgo < 1 ? 'Last synced just now' : `Last synced ${minutesAgo} minute${minutesAgo === 1 ? '' : 's'} ago`} ·{' '}
          <button type="button" className="secondary" disabled={syncing} onClick={syncNow}>{syncing ? 'Syncing…' : 'Sync now'}</button>{' '}
          <span role="status">{syncMsg}</span>
        </p>
      )}
      <section>
        <h2 id="current-topic">Current topic</h2>
        {current ? (
          <>
            <p><a href={current.href}>{current.id} {current.title}</a>{current.hasLesson ? '' : ' (lesson coming; practising from the bank)'}</p>
            <div className="progress"><div style={{ width: `${(100 * solved) / Math.max(1, current.ladder.length)}%` }} /><span>{solved} / {current.ladder.length} {current.hasLesson ? 'ladder problems' : 'practice problems'} solved</span></div>
          </>
        ) : (
          <p>No current topic yet.</p>
        )}
        <p><strong>{next}</strong></p>
      </section>
      <section>
        <h2 id="due-today">Due today</h2>
        {dueReviews.length === 0 && dueResolves.length === 0 && detected.length === 0 && <p>Nothing due.</p>}
        {dueReviews.length > 0 && (
          <ul>{dueReviews.map((r) => <li key={`${r.t.id}-${r.s}`}><a href={url(`/review/${r.t.id.replace('.', '-')}/${r.s}/`)}>Review set {r.s} for {r.t.id}</a> (due {r.due})</li>)}</ul>
        )}
        {dueResolves.length > 0 && (
          <>
            <p>Re-solve without hints (you needed hints 2–3 or the editorial a week ago):</p>
            <ul>{dueResolves.map((r) => <li key={r.id}><a href={problems[r.id].url} target="_blank" rel="noopener noreferrer">{problems[r.id].title}</a> (due {r.due})</li>)}</ul>
          </>
        )}
        {detected.length > 0 && (
          <ul>
            {detected.map((r) => (
              <li key={r.id}>
                <a href={problems[r.id].url} target="_blank" rel="noopener noreferrer">{problems[r.id].title}</a>: re-solve detected on{' '}
                {new Date((entry(r.id)?.lastAc ?? 0) * 1000).toLocaleDateString()}{' '}
                <button type="button" className="secondary" onClick={() => saveProblem(r.id, { resolveUndone: true })}>Undo</button>
              </li>
            ))}
          </ul>
        )}
      </section>
      {needsLog.length > 0 && (
        <section>
          <h2 id="needs-log">{needsLog.length} synced solve{needsLog.length === 1 ? '' : 's'} need a log entry</h2>
          <p>Solved on a platform, but no minutes or mistake category logged. Your log is what drives the mistake summary.</p>
          <ul>
            {needsLog.map((p) => (
              <li key={p.id}>
                {problems[p.id].title} <button type="button" className="secondary" aria-expanded={logOpen === p.id} onClick={() => setLogOpen(logOpen === p.id ? null : p.id)}>Log</button>
                {logOpen === p.id && <LogPanel id={p.id} log={{ ...logs[p.id], hintsOpened: logs[p.id]?.hintsOpened ?? 0, status: st(p.id).status ?? undefined }} onDone={() => setLogOpen(null)} />}
              </li>
            ))}
          </ul>
        </section>
      )}
      <section>
        <h2 id="mistakes">Mistakes in the last 30 days</h2>
        {recent.length === 0 ? <p>No mistakes logged.</p> : (
          <>
            <ul>{(Object.keys(MISTAKE_LABELS) as Exclude<Mistake, ''>[]).filter((k) => counts.get(k)).map((k) => <li key={k}>{MISTAKE_LABELS[k]}: {counts.get(k)}</li>)}</ul>
            {topRec.length > 0 && <p>Cards with the most recognition misses: {topRec.map(([k, n]) => `${k} ×${n}`).join(', ')}. Reread their weak and kill signals.</p>}
          </>
        )}
      </section>
    </div>
  );
}
