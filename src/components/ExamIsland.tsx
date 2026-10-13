import { useEffect, useRef, useState } from 'react';
import { getExams, saveExam, today, type ExamState } from '../lib/storage';
import { useStore } from '../lib/useStore';
import { COMPROMISED_NOTE, beginReservedSet, ensureFresh, scaledPassRule, verifyWindow, type Verification } from '../lib/sync/reserved';
import { useSync } from '../lib/sync/useStatuses';
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
  const [verified, setVerified] = useState<Record<string, { result: Verification; platform: string | null }>>({});
  const [touched, setTouched] = useState<Record<string, boolean>>({});
  const [busy, setBusy] = useState(false);
  const { entry } = useSync();
  const stored = state.compromised ?? [];
  const ids = problems.map((p) => p.id);
  const limit = hours * 3_600_000;
  // 60% of the problems that still test recognition (Section 10.2: pass rules scale, rounding up).
  const scaled = scaledPassRule(problems.length, Math.ceil(problems.length * 0.6), stored.length);
  const need = scaled?.need ?? Math.ceil(problems.length * 0.6);
  const counted = scaled?.of ?? problems.length;
  const note = (id: string) => stored.includes(id) && <p className="notice">{COMPROMISED_NOTE(entry(id)?.firstAc ?? null)}</p>;
  const platformName = (c: string | null) => (c === 'cf' ? 'Codeforces' : c === 'ac' ? 'AtCoder' : c === 'lc' ? 'LeetCode' : c ?? '');
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
  // After the timer: sync once and pre-fill "solved in time" from the platforms.
  const prefilled = useRef(false);
  useEffect(() => {
    if (!state.finished || !state.startedAt || prefilled.current) return;
    prefilled.current = true;
    const startSec = Math.floor(state.startedAt / 1000);
    ensureFresh(ids, 0).then(() => {
      // Measured after the sync, so a submission accepted while it ran still counts.
      const endSec = Math.min(startSec + hours * 3600, Math.floor(Date.now() / 1000) + 1);
      const v = verifyWindow(ids, startSec, endSec);
      setVerified(v);
      setSolved(Object.fromEntries(ids.map((id) => [id, v[id].result === 'yes'])));
    });
  }, [state.finished, state.startedAt]);

  const rule = (
    <p>
      Pass rule: solve at least {need} of the {counted} problems that count ({Math.round((need / counted) * 100)}%) within {hours} hours,
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
          {note(p.id)}
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
        <button type="button" disabled={busy} onClick={async () => {
          setBusy(true);
          await ensureFresh(ids, 300);
          const bad = [...beginReservedSet(ids)];
          prefilled.current = false;
          setNow(Date.now()); setResult(''); setSolved({}); setMissed({}); setVerified({}); setTouched({}); setShowMap(false);
          saveExam(phase, { startedAt: Date.now(), finished: false, compromised: bad });
          setBusy(false);
        }}>
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
    const ok = problems.filter((p) => solved[p.id] && !stored.includes(p.id)).map((p) => p.id);
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
      <p><strong>Time is up.</strong> For each problem, mark whether you solved it in time (accepted on the judge), and whether the first tool you tried was the wrong one. Codeforces and AtCoder are checked for you; change a box if it is wrong.</p>
      {problems.map((p) => {
        const v = verified[p.id];
        const mine = touched[p.id] && !!solved[p.id] !== (v?.result === 'yes');
        return (
        <div key={p.id} className="exam-row">
          <label className="check">
            <input type="checkbox" checked={!!solved[p.id]} disabled={stored.includes(p.id)} onChange={(e) => { setSolved({ ...solved, [p.id]: e.target.checked }); setTouched({ ...touched, [p.id]: true }); }} /> Solved: {p.title}
          </label>
          {stored.includes(p.id) ? note(p.id) : mine ? <span className="muted">confirmed by you</span> : v?.result === 'yes' ? <span className="muted">verified on {platformName(v.platform)}</span> : v?.result === 'unknown' ? <span className="muted">confirm by hand</span> : null}
          <label className="check">
            <input type="checkbox" checked={!!missed[p.id]} onChange={(e) => setMissed({ ...missed, [p.id]: e.target.checked })} /> Recognition miss
          </label>
        </div>
        );
      })}
      <button type="button" onClick={submit}>Submit results</button>
    </div>
  );
}
