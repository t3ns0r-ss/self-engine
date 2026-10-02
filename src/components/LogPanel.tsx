// Per-problem log panel (PLAN.md Section 10.2), shared by the bank pages and, later, the ladder.
import { useState } from 'react';
import { MISTAKE_LABELS, STATUS_LABELS, saveProblem, today, type Mistake, type ProblemLog, type ProblemStatus } from '../lib/storage';

export default function LogPanel({ id, log, onDone }: { id: string; log?: ProblemLog; onDone?: () => void }) {
  const [form, setForm] = useState({
    budget: log?.budget ?? '',
    candidates: log?.candidates ?? '',
    property: log?.property ?? '',
    status: (log?.status ?? '') as ProblemStatus | '',
    minutes: log?.minutes != null ? String(log.minutes) : '',
    mistake: (log?.mistake ?? '') as Mistake,
    note: log?.note ?? '',
  });
  const [message, setMessage] = useState('');
  const set = (k: keyof typeof form) => (e: { target: { value: string } }) => setForm({ ...form, [k]: e.target.value });
  const fid = (k: string) => `log-${id}-${k}`;

  function save() {
    if (!form.status) {
      setMessage('Choose a status first.');
      return;
    }
    const minutes = form.minutes.trim() === '' ? null : Math.max(0, Math.round(Number(form.minutes)) || 0);
    const ok = saveProblem(id, {
      budget: form.budget.trim(),
      candidates: form.candidates.trim(),
      property: form.property.trim(),
      status: form.status,
      minutes,
      mistake: form.mistake,
      note: form.note.trim(),
      date: today(),
    });
    setMessage(ok ? 'Saved.' : 'Could not save: browser storage is unavailable.');
    if (ok) onDone?.();
  }

  return (
    <div className="log-panel">
      <p className="log-hint">Before coding, write these three lines. They are optional, but they are how recognition improves.</p>
      <label htmlFor={fid('budget')}>Budget (from the constraints)</label>
      <input id={fid('budget')} value={form.budget} onChange={set('budget')} placeholder="n ≤ 2·10^5 → O(n log n)" />
      <label htmlFor={fid('candidates')}>Candidate tools</label>
      <input id={fid('candidates')} value={form.candidates} onChange={set('candidates')} />
      <label htmlFor={fid('property')}>Property verified</label>
      <input id={fid('property')} value={form.property} onChange={set('property')} />
      <div className="log-row">
        <div>
          <label htmlFor={fid('status')}>Status</label>
          <select id={fid('status')} value={form.status} onChange={set('status')}>
            <option value="">—</option>
            {Object.entries(STATUS_LABELS).map(([v, l]) => (
              <option key={v} value={v}>{l}</option>
            ))}
          </select>
        </div>
        <div>
          <label htmlFor={fid('minutes')}>Minutes</label>
          <input id={fid('minutes')} type="number" min="0" inputMode="numeric" value={form.minutes} onChange={set('minutes')} />
        </div>
        <div>
          <label htmlFor={fid('mistake')}>Mistake</label>
          <select id={fid('mistake')} value={form.mistake} onChange={set('mistake')}>
            <option value="">None</option>
            {Object.entries(MISTAKE_LABELS).map(([v, l]) => (
              <option key={v} value={v}>{l}</option>
            ))}
          </select>
        </div>
      </div>
      <label htmlFor={fid('note')}>Note</label>
      <textarea id={fid('note')} rows={2} value={form.note} onChange={set('note')} />
      <div className="log-actions">
        <button type="button" onClick={save}>Save</button>
        {onDone && <button type="button" className="secondary" onClick={onDone}>Close</button>}
        <span role="status">{message}</span>
      </div>
    </div>
  );
}
