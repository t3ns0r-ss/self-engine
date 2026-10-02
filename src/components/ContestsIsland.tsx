import { useState } from 'react';
import { getContests, saveContests, today, type ContestEntry } from '../lib/storage';
import { useStore } from '../lib/useStore';

// An upsolve target is stored as text (a problem id or URL); a leading "✓ " marks it done.
const DONE = '✓ ';

export default function ContestsIsland() {
  const contests = useStore(getContests, []);
  const empty = { date: today(), platform: 'AtCoder', name: '', solved: '', targets: '', note: '' };
  const [form, setForm] = useState(empty);
  const [msg, setMsg] = useState('');
  const set = (k: keyof typeof form) => (e: { target: { value: string } }) => setForm({ ...form, [k]: e.target.value });

  function add() {
    if (!form.name.trim()) {
      setMsg('Give the contest a name.');
      return;
    }
    const entry: ContestEntry = {
      date: form.date, platform: form.platform, name: form.name.trim(), solved: Math.max(0, Number(form.solved) || 0),
      upsolved: form.targets.split(/[\n,]+/).map((s) => s.trim()).filter(Boolean), note: form.note.trim(),
    };
    setMsg(saveContests([entry, ...contests]) ? 'Saved.' : 'Could not save: browser storage is unavailable.');
    setForm({ ...empty, platform: form.platform });
  }
  function toggle(ci: number, ti: number) {
    const list = structuredClone(contests);
    const t = list[ci].upsolved[ti];
    list[ci].upsolved[ti] = t.startsWith(DONE) ? t.slice(DONE.length) : DONE + t;
    saveContests(list);
  }
  function remove(ci: number) {
    if (confirm(`Delete "${contests[ci].name}"?`)) saveContests(contests.filter((_, i) => i !== ci));
  }
  const open = contests.flatMap((c) => c.upsolved.filter((t) => !t.startsWith(DONE)).map((t) => `${t} (${c.name})`));
  const link = (t: string) => (/^https?:\/\//.test(t) ? <a href={t} target="_blank" rel="noopener noreferrer">{t}</a> : t);

  return (
    <div>
      <h2 id="add">Add a contest</h2>
      <div className="contest-form">
        <div className="log-row">
          <label>Date <input type="date" value={form.date} onChange={set('date')} /></label>
          <label>Platform <select value={form.platform} onChange={set('platform')}>{['AtCoder', 'Codeforces', 'Other'].map((p) => <option key={p}>{p}</option>)}</select></label>
          <label>Solved in contest <input type="number" min="0" value={form.solved} onChange={set('solved')} /></label>
        </div>
        <label>Name <input value={form.name} onChange={set('name')} placeholder="AtCoder Beginner Contest 400" /></label>
        <label>Upsolve targets (problem links or ids, one per line or comma-separated) <textarea rows={3} value={form.targets} onChange={set('targets')} /></label>
        <label>Note <textarea rows={2} value={form.note} onChange={set('note')} /></label>
        <div className="log-actions"><button type="button" onClick={add}>Add contest</button><span role="status">{msg}</span></div>
      </div>
      <h2 id="upsolve">Open upsolve targets</h2>
      {open.length ? <ul>{open.map((t, i) => <li key={i}>{t}</li>)}</ul> : <p>None open.</p>}
      <h2 id="history">History</h2>
      {contests.length === 0 && <p>No contests logged yet.</p>}
      {contests.map((c, ci) => (
        <section key={ci} className="ladder-item">
          <header>{c.date} · {c.platform} · {c.name} · solved {c.solved}</header>
          {c.note && <p>{c.note}</p>}
          <ul className="upsolve-list">
            {c.upsolved.map((t, ti) => (
              <li key={ti}>
                <label><input type="checkbox" checked={t.startsWith(DONE)} onChange={() => toggle(ci, ti)} /> {link(t.replace(DONE, ''))}</label>
              </li>
            ))}
          </ul>
          <button type="button" className="secondary" onClick={() => remove(ci)}>Delete</button>
        </section>
      ))}
    </div>
  );
}
