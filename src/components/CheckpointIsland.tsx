import { useEffect, useState } from 'react';
import { REVIEW_OFFSETS, addDays, getDrills, getTopics, saveTopic, today, type TopicState } from '../lib/storage';
import { useStore } from '../lib/useStore';
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

  const drillRight = drill.filter((d) => drills[d.problem]?.revealed && drills[d.problem]?.chosenCard === d.answer).length;
  const rule = (
    <p>
      Pass rule: solve at least 2 of the 3 problems within {minutes} minutes, and get at least 8 drill items right
      (you have {drillRight} right so far). Problems are hidden until you start, so they stay unseen.
    </p>
  );

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
        <button type="button" onClick={() => { setNow(Date.now()); setResult(''); saveTopic(topic, { checkpointStartedAt: Date.now(), checkpointFinished: false }); }}>
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
        </li>
      ))}
    </ol>
  );

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
    const ids = problems.filter((p) => solved[p.id]).map((p) => p.id);
    const pass = ids.length >= 2 && drillRight >= 8;
    saveTopic(topic, { checkpointStartedAt: null, checkpointFinished: false, checkpointSolved: ids, checkpointPassedOn: pass ? today() : null });
    if (!pass) {
      const why = [ids.length < 2 ? `${ids.length} of 3 solved in time (need 2)` : '', drillRight < 8 ? `${drillRight} drill items right (need 8)` : ''].filter(Boolean).join('; ');
      setResult(`Not passed yet: ${why}. Upsolve the problems you missed, reread the cards they needed, and try again with a fresh attempt later.`);
    }
  }

  return (
    <div className="checkpoint">
      <p><strong>Time is up.</strong> Mark the problems you solved within the time limit (accepted on the judge).</p>
      {problems.map((p) => (
        <label key={p.id} className="check">
          <input type="checkbox" checked={!!solved[p.id]} onChange={(e) => setSolved({ ...solved, [p.id]: e.target.checked })} /> {p.title}
        </label>
      ))}
      <button type="button" onClick={submit}>Submit results</button>
    </div>
  );
}
