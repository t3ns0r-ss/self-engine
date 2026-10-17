// Logs one attempt at an exercise (Section 11.2): minutes, hints opened, whether the kit tests passed, a measured value,
// the mistake category, and a note. Stored under cp:v1:design-attempts and included in export and import.
import { useState } from 'react';
import { DESIGN_MISTAKES, addDesignAttempt, getDesignAttempts, today } from '../../lib/storage';
import { useStore } from '../../lib/useStore';

export default function AttemptLog({ globalId, measured = false }: { globalId: string; measured?: boolean }) {
  const attempts = useStore(() => getDesignAttempts()[globalId] ?? [], []);
  const [minutes, setMinutes] = useState('');
  const [hints, setHints] = useState('0');
  const [passed, setPassed] = useState(false);
  const [value, setValue] = useState('');
  const [mistake, setMistake] = useState('');
  const [note, setNote] = useState('');
  return (
    <div className="attempt-log">
      <h4>Log an attempt</h4>
      <label>Minutes <input inputMode="numeric" value={minutes} onChange={(e) => setMinutes(e.target.value)} /></label>{' '}
      <label>Hints opened <input inputMode="numeric" value={hints} onChange={(e) => setHints(e.target.value)} /></label>{' '}
      <label><input type="checkbox" checked={passed} onChange={(e) => setPassed(e.target.checked)} /> The tests pass</label>
      {measured && <label> Measured value <input value={value} onChange={(e) => setValue(e.target.value)} /></label>}
      <label> Mistake{' '}
        <select value={mistake} onChange={(e) => setMistake(e.target.value)}>
          <option value="">none</option>
          {DESIGN_MISTAKES.map((m) => <option key={m}>{m}</option>)}
        </select>
      </label>
      <label> Note <input value={note} onChange={(e) => setNote(e.target.value)} /></label>{' '}
      <button type="button" onClick={() => { addDesignAttempt(globalId, { date: today(), minutes: minutes ? Number(minutes) : null, hints: Number(hints) || 0, testsPassed: passed, measured: value || null, mistake, note }); setMinutes(''); setNote(''); }}>Save</button>
      {attempts.length > 0 && (
        <ul>{attempts.map((a, i) => <li key={i}>{a.date}: {a.testsPassed ? 'passed' : 'not passed'}{a.minutes ? `, ${a.minutes} min` : ''}{a.mistake ? `, ${a.mistake}` : ''}{a.note ? `: ${a.note}` : ''}</li>)}</ul>
      )}
    </div>
  );
}
