// Table of labs with the learner's progress (rungs with a passing attempt).
import { getDesignAttempts } from '../../lib/storage';
import { useStore } from '../../lib/useStore';

export type LabItem = { id: string; title: string; lab: string; infra: string[]; href: string | null; rungs: string[] };

export default function LabProgress({ items }: { items: LabItem[] }) {
  const attempts = useStore(getDesignAttempts, {});
  return (
    <div className="table-scroll">
      <table>
        <thead><tr><th>Topic</th><th>What is built</th><th>Infra</th><th>Rungs done</th></tr></thead>
        <tbody>
          {items.map((i) => {
            const done = i.rungs.filter((r) => attempts[r]?.some((a) => a.testsPassed)).length;
            return (
              <tr key={i.id}>
                <td>{i.href ? <a href={i.href}>{i.id} {i.title}</a> : `${i.id} ${i.title}`}</td>
                <td>{i.lab}</td>
                <td>{i.infra.length ? i.infra.join(', ') : '—'}</td>
                <td>{i.rungs.length ? `${done} of ${i.rungs.length}` : 'not planned yet'}</td>
              </tr>
            );
          })}
        </tbody>
      </table>
    </div>
  );
}
