// Constants with sources and caveats, plus a place for the learner's own measured value of each (Section 11.5).
import { getNumbers, saveNumber } from '../../lib/storage';
import { useStore } from '../../lib/useStore';

export type NumRow = { id: string; quantity: string; value: number; unit: string; display: string; source: { title: string; url: string; accessed: string; section: string }; caveat: string };

export default function NumbersTable({ constants }: { constants: NumRow[] }) {
  const mine = useStore(getNumbers, {});
  if (!constants.length) return <p className="muted">No constants yet; they are added with the first topic that uses them.</p>;
  return (
    <div className="table-scroll">
      <table>
        <thead><tr><th>Quantity</th><th>Constant</th><th>Source</th><th>Caveat</th><th>Your measured value</th></tr></thead>
        <tbody>
          {constants.map((c) => (
            <tr key={c.id}>
              <td>{c.quantity}</td>
              <td>{c.display} ({c.value} {c.unit})</td>
              <td><a href={c.source.url} rel="noopener noreferrer">{c.source.title}</a>, {c.source.section}, opened {c.source.accessed}</td>
              <td>{c.caveat}</td>
              <td><input aria-label={`Your measured ${c.quantity}`} inputMode="decimal" defaultValue={mine[c.id]?.own ?? ''} onBlur={(e) => saveNumber(c.id, { own: e.target.value === '' ? null : Number(e.target.value), unit: c.unit })} /></td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}
