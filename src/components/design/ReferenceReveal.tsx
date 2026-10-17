// The reference solution, hidden until at least one attempt is logged for the exercise (Section 11.7).
import { getDesignAttempts } from '../../lib/storage';
import { useStore } from '../../lib/useStore';

export default function ReferenceReveal({ globalId, solution }: { globalId: string; solution: string }) {
  const attempts = useStore(getDesignAttempts, {});
  if (!(attempts[globalId]?.length > 0)) return <p className="muted">The reference solution unlocks after you log an attempt.</p>;
  return <details><summary>Reference solution</summary><pre className="solution">{solution}</pre></details>;
}
