import { useState } from 'react';
import { STATUS_LABELS, getProblems, getTopics } from '../lib/storage';
import { useStore } from '../lib/useStore';
import type { IndexedProblem } from '../lib/data';
import PlatformBadge from './PlatformBadge';

const HIDDEN = new Set(['checkpoint', 'review', 'exam']);
const ROLE_LABEL: Record<string, string> = { practice: 'practice', ladder: 'ladder', worked_example: 'worked example', drill: 'drill', lookalike: 'look-alike', checkpoint: 'checkpoint', review: 'review', exam: 'exam' };
type Key = 'title' | 'source' | 'difficulty' | 'topic' | 'role' | 'cardName' | 'status';
const num = (d: string) => (/^-?\d+$/.test(d) ? Number(d) : ({ Easy: 1, Medium: 2, Hard: 3 } as Record<string, number>)[d] ?? -1);

export default function ProblemsIsland({ rows, order }: { rows: IndexedProblem[]; order: Record<string, number> }) {
  const logs = useStore(getProblems, {});
  const topics = useStore(getTopics, {});
  const [f, setF] = useState({ source: '', topic: '', role: '', status: '', q: '' });
  const [sort, setSort] = useState<{ key: Key; dir: 1 | -1 }>({ key: 'topic', dir: 1 });
  const status = (id: string) => logs[id]?.status ?? '';

  const visible = rows
    .filter((r) => !HIDDEN.has(r.role) || topics[r.topic]?.checkpointPassedOn)
    .filter((r) => (!f.source || r.source === f.source) && (!f.topic || r.topic === f.topic) && (!f.role || r.role === f.role))
    .filter((r) => !f.status || (f.status === 'none' ? !status(r.id) : status(r.id) === f.status))
    .filter((r) => !f.q || `${r.title} ${r.id} ${r.cardName}`.toLowerCase().includes(f.q.toLowerCase()));
  const hiddenCount = rows.filter((r) => HIDDEN.has(r.role) && !topics[r.topic]?.checkpointPassedOn).length;
  const value = (r: IndexedProblem, k: Key): string | number =>
    k === 'topic' ? order[r.topic] : k === 'difficulty' ? num(r.difficulty) : k === 'status' ? status(r.id) : r[k];
  visible.sort((a, b) => {
    const x = value(a, sort.key), y = value(b, sort.key);
    return (x < y ? -1 : x > y ? 1 : a.id.localeCompare(b.id)) * sort.dir;
  });
  const th = (k: Key, label: string) => (
    <th aria-sort={sort.key === k ? (sort.dir === 1 ? 'ascending' : 'descending') : 'none'}>
      <button type="button" className="th-sort" onClick={() => setSort({ key: k, dir: sort.key === k ? (-sort.dir as 1 | -1) : 1 })}>
        {label}{sort.key === k ? (sort.dir === 1 ? ' ▲' : ' ▼') : ''}
      </button>
    </th>
  );
  const uniq = (k: 'source' | 'topic' | 'role') => [...new Set(rows.map((r) => r[k]))];
  const set = (k: keyof typeof f) => (e: { target: { value: string } }) => setF({ ...f, [k]: e.target.value });

  if (!rows.length) return <p>No problems yet. They appear here as the problem bank fills.</p>;
  return (
    <>
      <div className="filters">
        <input aria-label="Search" placeholder="Search" value={f.q} onChange={set('q')} />
        <select aria-label="Platform" value={f.source} onChange={set('source')}><option value="">All platforms</option>{uniq('source').map((s) => <option key={s} value={s}>{s}</option>)}</select>
        <select aria-label="Topic" value={f.topic} onChange={set('topic')}><option value="">All topics</option>{uniq('topic').sort((a, b) => order[a] - order[b]).map((s) => <option key={s} value={s}>{s}</option>)}</select>
        <select aria-label="Role" value={f.role} onChange={set('role')}><option value="">All roles</option>{uniq('role').map((s) => <option key={s} value={s}>{ROLE_LABEL[s]}</option>)}</select>
        <select aria-label="Status" value={f.status} onChange={set('status')}>
          <option value="">Any status</option><option value="none">Not started</option>
          {Object.entries(STATUS_LABELS).map(([k, l]) => <option key={k} value={k}>{l}</option>)}
        </select>
      </div>
      <p className="muted">{visible.length} shown{hiddenCount ? `; ${hiddenCount} hidden until their topic's checkpoint is passed` : ''}.</p>
      <div className="table-scroll">
        <table className="bank-table">
          <thead><tr>{th('title', 'Problem')}{th('source', 'Platform')}{th('difficulty', 'Difficulty')}{th('topic', 'Topic')}{th('role', 'Role')}{th('cardName', 'Card')}{th('status', 'Status')}</tr></thead>
          <tbody>
            {visible.map((r) => (
              <tr key={r.id} className={status(r.id) ? `status-${status(r.id)}` : undefined}>
                <td><a href={r.url} target="_blank" rel="noopener noreferrer">{r.title}</a><div className="problem-id">{r.id}</div></td>
                <td><PlatformBadge source={r.source} /></td>
                <td>{r.difficulty}</td>
                <td>{r.topic}</td>
                <td>{ROLE_LABEL[r.role]}{r.reviewSet ? ` ${r.reviewSet}` : ''}</td>
                <td>{r.cardName}</td>
                <td>{status(r.id) ? STATUS_LABELS[status(r.id) as keyof typeof STATUS_LABELS] : '—'}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </>
  );
}
