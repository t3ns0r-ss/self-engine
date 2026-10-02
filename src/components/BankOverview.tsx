// All topics with practice counts per tier and the learner's solved counts (bank plan Section 9.1).
import { useProblems } from '../lib/useProblems';
import { isSolved } from '../lib/storage';

export type OverviewRow = { id: string; title: string; phase: number; href: string; tiers: number[]; practiceIds: string[]; status: string };

export default function BankOverview({ rows }: { rows: OverviewRow[] }) {
  const logs = useProblems();
  return (
    <div className="table-scroll">
      <table className="bank-table">
        <thead>
          <tr><th>Phase</th><th>Topic</th><th>T1</th><th>T2</th><th>T3</th><th>T4</th><th>T5</th><th>Solved</th><th>Bank</th></tr>
        </thead>
        <tbody>
          {rows.map((r) => {
            const solved = r.practiceIds.filter((id) => isSolved(logs[id])).length;
            return (
              <tr key={r.id}>
                <td>{r.phase}</td>
                <td><a href={r.href}>{r.id} {r.title}</a></td>
                {r.tiers.map((c, i) => <td key={i}>{c}</td>)}
                <td>{r.practiceIds.length ? `${solved} / ${r.practiceIds.length}` : '—'}</td>
                <td>{r.status}</td>
              </tr>
            );
          })}
        </tbody>
      </table>
    </div>
  );
}
