import { useEffect, useRef, useState } from 'react';
import { REVIEW_OFFSETS, addDays, getDrills, getTopics, saveTopic, today, type TopicState } from '../lib/storage';
import { useStore } from '../lib/useStore';
import { COMPROMISED_NOTE, beginReservedSet, ensureFresh, scaledPassRule, verifyWindow, type Verification } from '../lib/sync/reserved';
import { useCompromised, useSync } from '../lib/sync/useStatuses';
import { url } from '../lib/url';
import PlatformBadge from './PlatformBadge';

export type CheckpointProblem = { id: string; title: string; url: string; source: string; difficulty: string };

const fmt = (ms: number) => {
  const s = Math.max(0, Math.ceil(ms / 1000));
  const h = Math.floor(s / 3600), m = Math.floor((s % 3600) / 60), sec = s % 60;
  return `${h}:${String(m).padStart(2, '0')}:${String(sec).padStart(2, '0')}`;
};

export default function CheckpointIsland({ topic, minutes, problems, drill }: {
  topic: string; minutes: number; problems: CheckpointProblem[]; drill: { problem: string; answer: string }[];
}) {
  const state: TopicState = useStore(() => getTopics()[topic] ?? {}, {});
  const drills = useStore(getDrills, {});
  const [now, setNow] = useState(() => Date.now());
  const [solved, setSolved] = useState<Record<string, boolean>>({});
  const [result, setResult] = useState('');
  const [verified, setVerified] = useState<Record<string, { result: Verification; platform: string | null }>>({});
  const [touched, setTouched] = useState<Record<string, boolean>>({});
  const [busy, setBusy] = useState(false);
  const { entry } = useSync();
  const stored = state.checkpointCompromised ?? [];
  const drillBad = useCompromised(drill.map((d) => d.problem));
  const ids = problems.map((p) => p.id);
  const running = !!state.checkpointStartedAt && !state.checkpointFinished;
  // Clamped: the first render after Start can use a clock reading taken just before the start time.
  const left = running ? Math.min(minutes * 60_000, state.checkpointStartedAt! + minutes * 60_000 - now) : 0;

  useEffect(() => {
    if (!running) return;
    const t = setInterval(() => setNow(Date.now()), 1000);
    return () => clearInterval(t);
  }, [running]);
  useEffect(() => {
    if (running && left <= 0) saveTopic(topic, { checkpointFinished: true });
  }, [running, left <= 0]);

  // Compromised drill items are excluded from the score; the 8-right rule never asks for more than what remains.
  const drillUsable = drill.filter((d) => !drillBad.has(d.problem));
  const drillRight = drillUsable.filter((d) => drills[d.problem]?.revealed && drills[d.problem]?.chosenCard === d.answer).length;
  const drillNeed = Math.min(8, drillUsable.length);
  const scaled = scaledPassRule(problems.length, 2, stored.length);
  const rule = (
    <p>
      Pass rule: solve at least {scaled?.need ?? 2} of the {scaled?.of ?? problems.length} problems that count within {minutes} minutes, and get at least {drillNeed} drill items right
      (you have {drillRight} right so far). Problems are hidden until you start, so they stay unseen.
    </p>
  );
  const note = (id: string) => stored.includes(id) && <p className="notice">{COMPROMISED_NOTE(entry(id)?.firstAc ?? null)}</p>;

  // When the timer ends (or the learner finishes early), sync once and pre-fill "solved in time" from the platforms.
  const prefilled = useRef(false);
  useEffect(() => {
    if (!state.checkpointFinished || !state.checkpointStartedAt || prefilled.current) return;
    prefilled.current = true;
    const startSec = Math.floor(state.checkpointStartedAt / 1000);
    ensureFresh(ids, 0).then(() => {
      // Measured after the sync, so a submission accepted while it ran still counts.
      const endSec = Math.min(startSec + minutes * 60, Math.floor(Date.now() / 1000) + 1);
      const v = verifyWindow(ids, startSec, endSec);
      setVerified(v);
      setSolved(Object.fromEntries(ids.map((id) => [id, v[id].result === 'yes'])));
    });
  }, [state.checkpointFinished, state.checkpointStartedAt]);

  if (state.checkpointPassedOn) {
    return (
      <div className="checkpoint">
        <p><strong>Passed on {state.checkpointPassedOn}.</strong> Review sets are due on:</p>
        <ul>
          {([1, 2, 3] as const).map((s) => (
            <li key={s}><a href={url(`/review/${topic.replace('.', '-')}/${s}/`)}>Review set {s}</a>: {addDays(state.checkpointPassedOn!, REVIEW_OFFSETS[s])}</li>
          ))}
        </ul>
      </div>
    );
  }

  if (!state.checkpointStartedAt) {
    return (
      <div className="checkpoint">
        {rule}
        {result && <p role="status">{result}</p>}
        <button type="button" disabled={busy} onClick={async () => {
          setBusy(true);
          setResult('');
          // Before the problems are shown: bring the platforms up to date and find the ones already solved.
          await ensureFresh(ids, 300);
          const bad = [...beginReservedSet(ids)];
          prefilled.current = false;
          setVerified({}); setTouched({}); setSolved({});
          setNow(Date.now());
          saveTopic(topic, { checkpointStartedAt: Date.now(), checkpointFinished: false, checkpointCompromised: bad });
          setBusy(false);
        }}>
          Start the {minutes}-minute checkpoint
        </button>
      </div>
    );
  }

  const list = (
    <ol>
      {problems.map((p) => (
        <li key={p.id}>
          <a href={p.url} target="_blank" rel="noopener noreferrer">{p.title}</a> <PlatformBadge source={p.source} /> <span className="muted">{p.difficulty}</span>
          {note(p.id)}
        </li>
      ))}
    </ol>
  );
  const allBad = !scaled;
  const platformName = (c: string | null) => (c === 'cf' ? 'Codeforces' : c === 'ac' ? 'AtCoder' : c === 'lc' ? 'LeetCode' : c ?? '');

  if (allBad) {
    return (
      <div className="checkpoint">
        <p><strong>This checkpoint needs replacement problems.</strong> You had already solved all {problems.length} before they were assigned, so it cannot test recognition and cannot be passed. Use "Export feedback" on the Progress page and give it to the course author.</p>
        {list}
      </div>
    );
  }
  if (running) {
    return (
      <div className="checkpoint">
        <p className="timer" role="timer">Time left: <strong>{fmt(left)}</strong></p>
        {list}
        <button type="button" className="secondary" onClick={() => saveTopic(topic, { checkpointFinished: true })}>I'm done early</button>
      </div>
    );
  }

  function submit() {
    const done = problems.filter((p) => solved[p.id] && !stored.includes(p.id)).map((p) => p.id);
    const needed = scaled!.need;
    const pass = done.length >= needed && drillRight >= drillNeed;
    saveTopic(topic, { checkpointStartedAt: null, checkpointFinished: false, checkpointSolved: done, checkpointPassedOn: pass ? today() : null });
    if (!pass) {
      const why = [done.length < needed ? `${done.length} of ${scaled!.of} solved in time (need ${needed})` : '', drillRight < drillNeed ? `${drillRight} drill items right (need ${drillNeed})` : ''].filter(Boolean).join('; ');
      setResult(`Not passed yet: ${why}. Upsolve the problems you missed, reread the cards they needed, and try again with a fresh attempt later.`);
    }
  }

  return (
    <div className="checkpoint">
      <p><strong>Time is up.</strong> Mark the problems you solved within the time limit (accepted on the judge). Codeforces and AtCoder are checked for you; change a box if it is wrong.</p>
      {problems.map((p) => {
        const v = verified[p.id];
        const mine = touched[p.id] && !!solved[p.id] !== (v?.result === 'yes');
        return (
          <div key={p.id}>
            <label className="check">
              <input type="checkbox" checked={!!solved[p.id]} disabled={stored.includes(p.id)} onChange={(e) => { setSolved({ ...solved, [p.id]: e.target.checked }); setTouched({ ...touched, [p.id]: true }); }} /> {p.title}
            </label>
            {stored.includes(p.id) ? note(p.id)
              : mine ? <span className="muted"> confirmed by you</span>
              : v?.result === 'yes' ? <span className="muted"> verified on {platformName(v.platform)}</span>
              : v?.result === 'unknown' ? <span className="muted"> confirm by hand</span> : null}
          </div>
        );
      })}
      <button type="button" onClick={submit}>Submit results</button>
    </div>
  );
}
