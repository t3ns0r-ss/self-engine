import type { ReactNode } from 'react';
import { MISTAKE_LABELS, REVIEW_OFFSETS, addDays, getProblems, getSettings, getTopics, isSolved, resolveDue, today, type Mistake } from '../lib/storage';
import { useStore } from '../lib/useStore';
import { url } from '../lib/url';

export type DashTopic = {
  id: string; order: number; title: string; href: string; hasLesson: boolean; hasCheckpoint: boolean;
  ladder: { id: string; label: string }[]; reviews: string[][];
};
export type DashProblem = { title: string; url: string; topic: string; card: string };

export default function DashboardIsland({ topics, problems }: { topics: DashTopic[]; problems: Record<string, DashProblem> }) {
  const logs = useStore(getProblems, {});
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
      .filter((r) => r.ids.length && r.due <= now && r.ids.some((id) => !logs[id]?.status));
  });
  const dueResolves = Object.entries(logs)
    .map(([id, log]) => ({ id, due: resolveDue(log) }))
    .filter((r) => r.due && r.due <= now && problems[r.id]);

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
    const open = current.ladder.find((p) => !isSolved(logs[p.id]));
    const after = topics.find((t) => t.order === current.order + 1);
    if (open) next = <>Next: <a href={current.href}>{current.hasLesson ? `finish ${open.label}` : open.label}</a>.</>;
    else if (current.hasCheckpoint && !topicState[current.id]?.checkpointPassedOn) next = <>Take the <a href={`${current.href}#13-checkpoint`}>{current.id} checkpoint</a>.</>;
    else if (after) next = <>Move on to <a href={after.href}>{after.id} {after.title}</a>.</>;
    else next = <>You have finished the programme. Keep doing contests and upsolving.</>;
  }

  const solved = current ? current.ladder.filter((p) => isSolved(logs[p.id])).length : 0;
  return (
    <div className="dashboard">
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
        {dueReviews.length === 0 && dueResolves.length === 0 && <p>Nothing due.</p>}
        {dueReviews.length > 0 && (
          <ul>{dueReviews.map((r) => <li key={`${r.t.id}-${r.s}`}><a href={url(`/review/${r.t.id.replace('.', '-')}/${r.s}/`)}>Review set {r.s} for {r.t.id}</a> (due {r.due})</li>)}</ul>
        )}
        {dueResolves.length > 0 && (
          <>
            <p>Re-solve without hints (you needed hints 2–3 or the editorial a week ago):</p>
            <ul>{dueResolves.map((r) => <li key={r.id}><a href={problems[r.id].url} target="_blank" rel="noopener noreferrer">{problems[r.id].title}</a> (due {r.due})</li>)}</ul>
          </>
        )}
      </section>
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
