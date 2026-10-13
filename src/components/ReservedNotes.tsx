// Records when reserved problems are first shown (PROFILE_SYNC_PLAN.md Section 10.1) and flags the ones the learner had
// already solved. Renders nothing unless a problem is compromised. Used where a page has no island of its own.
import { useEffect } from 'react';
import { COMPROMISED_NOTE, beginReservedSet } from '../lib/sync/reserved';
import { useCompromised, useSync } from '../lib/sync/useStatuses';

export default function ReservedNotes({ ids, titles }: { ids: string[]; titles?: string[] }) {
  const { entry } = useSync();
  const bad = useCompromised(ids);
  useEffect(() => { beginReservedSet(ids); }, []);
  if (!bad.size) return null;
  return (
    <div className="notice" role="note">
      {ids.filter((id) => bad.has(id)).map((id) => (
        <p key={id}>{titles ? `${titles[ids.indexOf(id)]}: ` : ''}{COMPROMISED_NOTE(entry(id)?.firstAc ?? null)}</p>
      ))}
    </div>
  );
}
