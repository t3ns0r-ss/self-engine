import { useEffect, useState } from 'react';
import { getExams, saveExam, today, type ExamState } from '../lib/storage';
import { useStore } from '../lib/useStore';
import PlatformBadge from './PlatformBadge';

export type ExamProblem = {
  id: string; title: string; url: string; source: string; difficulty: string;
  /** Remediation map: where to go back to after a miss. */
  topic: string; topicTitle: string; cardName: string; theorem: string; cardsHref: string;
};

const fmt = (ms: number) => {
  const s = Math.max(0, Math.ceil(ms / 1000));
  const h = Math.floor(s / 3600), m = Math.floor((s % 3600) / 60), sec = s % 60;
  return `${h}:${String(m).padStart(2, '0')}:${String(sec).padStart(2, '0')}`;
};

/** Phase exam (PLAN.md Section 11.3): timer, hidden problems until start, self-reported results,
 *  pass rule, and a remediation map behind a reveal. */
export default function ExamIsland({ phase, hours, problems }: { phase: string; hours: number; problems: ExamProblem[] }) {
  const state: ExamState = useStore(() => getExams()[phase] ?? {}, {});
  const [now, setNow] = useState(() => Date.now());
  const [solved, setSolved] = useState<Record<string, boolean>>({});
  const [missed, setMissed] = useState<Record<string, boolean>>({});
  const [showMap, setShowMap] = useState(false);
  const [result, setResult] = useState('');
  const limit = hours * 3_600_000;
  const need = Math.ceil(problems.length * 0.6);
  const running = !!state.startedAt && !state.finished;
  const left = running ? Math.min(limit, state.startedAt! + limit - now) : 0;

  useEffect(() => {
    if (!running) return;
    const t = setInterval(() => setNow(Date.now()), 1000);
    return () => clearInterval(t);
  }, [running]);
  useEffect(() => {
    if (running && left <= 0) saveExam(phase, { finished: true });
  }, [running, left <= 0]);

  const rule = (
    <p>
      Pass rule: solve at least {need} of the {problems.length} problems ({Math.round((need / problems.length) * 100)}%) within {hours} hours,
      with no Recognition miss on a solved problem (a solved problem where the first tool you tried was the wrong one).
      The problems are hidden until you start, so they stay unseen.
    </p>
  );

  const remediation = (
    <div className="exam-map">
      <button type="button" className="secondary" onClick={() => setShowMap(!showMap)}>
        {showMap ? 'Hide the remediation map' : 'Show the remediation map'}
      </button>
      {showMap && (
        <table>
          <thead><tr><th>Problem</th><th>Topic</th><th>Card</th><th>Reread</th></tr></thead>
          <tbody>
            {problems.map((p) => (
              <tr key={p.id}>
                <td><a href={p.url} target="_blank" rel="noopener noreferrer">{p.title}</a></td>
                <td>{p.topic} {p.topicTitle}</td>
                <td>{p.cardName}</td>
                <td><a href={p.cardsHref}>Section 5 (cards) and {p.theorem}</a></td>
              </tr>
            ))}
          </tbody>
        </table>
      )}
    </div>
  );

  const list = (
    <ol>
      {problems.map((p) => (
        <li key={p.id}>
          <a href={p.url} target="_blank" rel="noopener noreferrer">{p.title}</a> <PlatformBadge source={p.source} /> <span className="muted">{p.difficulty}</span>
        </li>
      ))}
    </ol>
  );

  if (state.passedOn) {
    return (
      <div className="checkpoint exam">
        <p><strong>Passed on {state.passedOn}.</strong> The problems, for upsolving:</p>
        {list}
        {remediation}
      </div>
    );
  }

  if (!state.startedAt) {
    return (
      <div className="checkpoint exam">
        {rule}
        {result && <p role="status">{result}</p>}
        {state.lastAttemptOn && remediation}
        <button type="button" onClick={() => { setNow(Date.now()); setResult(''); setSolved({}); setMissed({}); setShowMap(false); saveExam(phase, { startedAt: Date.now(), finished: false }); }}>
          Start the {hours}-hour exam
        </button>
      </div>
    );
  }

  if (running) {
    return (
      <div className="checkpoint exam">
        <p className="timer" role="timer">Time left: <strong>{fmt(left)}</strong></p>
        {list}
        <button type="button" className="secondary" onClick={() => saveExam(phase, { finished: true })}>I'm done early</button>
      </div>
    );
  }

  function submit() {
    const ok = problems.filter((p) => solved[p.id]).map((p) => p.id);
    const misses = ok.filter((id) => missed[id]);
    const pass = ok.length >= need && misses.length === 0;
    saveExam(phase, { startedAt: null, finished: false, solved: ok, recognitionMisses: misses, lastAttemptOn: today(), passedOn: pass ? today() : null });
    if (!pass) {
      const why = [ok.length < need ? `${ok.length} solved in time (need ${need})` : '', misses.length ? `${misses.length} Recognition miss${misses.length > 1 ? 'es' : ''} on solved problems` : ''].filter(Boolean).join('; ');
      setResult(`Not passed yet: ${why}. Use the remediation map below to reread the cards behind the problems you missed, upsolve them, and sit the exam again later.`);
    }
  }

  return (
    <div className="checkpoint exam">
      <p><strong>Time is up.</strong> For each problem, mark whether you solved it in time (accepted on the judge), and whether the first tool you tried was the wrong one.</p>
      {problems.map((p) => (
        <div key={p.id} className="exam-row">
          <label className="check">
            <input type="checkbox" checked={!!solved[p.id]} onChange={(e) => setSolved({ ...solved, [p.id]: e.target.checked })} /> Solved: {p.title}
          </label>
          <label className="check">
            <input type="checkbox" checked={!!missed[p.id]} onChange={(e) => setMissed({ ...missed, [p.id]: e.target.checked })} /> Recognition miss
          </label>
        </div>
      ))}
      <button type="button" onClick={submit}>Submit results</button>
    </div>
  );
}
