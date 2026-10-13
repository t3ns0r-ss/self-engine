// A problem's shown status plus where it came from (PROFILE_SYNC_PLAN.md Section 11). Text is always present, so colour is never the only signal.
import { STATUS_LABELS } from '../lib/storage';
import type { StatusView } from '../lib/sync/status';

const PLATFORM_NAME = { cf: 'Codeforces', ac: 'AtCoder', lc: 'LeetCode', cses: 'CSES' } as const;
const MARK = { cf: 'CF', ac: 'AC', lc: 'LC', cses: '' } as const;

const fmt = (s: number | null) => (s ? new Date(s * 1000).toLocaleDateString(undefined, { day: 'numeric', month: 'short' }) : '');

export default function StatusChip({ view }: { view: StatusView }) {
  const label = view.status ? STATUS_LABELS[view.status] : 'Not started';
  const name = view.platform ? PLATFORM_NAME[view.platform] : '';
  const synced = view.source === 'sync' && view.platform;
  return (
    <span className="status-chip">
      <span>{label}</span>
      {synced && (
        <span className="sync-mark" title={`Synced from ${name}${view.syncedAt ? `, ${fmt(view.syncedAt)}` : ''}`} aria-label={`synced from ${name}`}>
          {MARK[view.platform!]}{view.syncedAt ? ` synced ${fmt(view.syncedAt)}` : ''}
        </span>
      )}
      {view.flag === 'no-ac-on-platform' && (
        <span className="sync-flag" role="img" title={`Marked solved here, but no accepted submission found on ${name}`} aria-label={`Marked solved here, but no accepted submission found on ${name}`}>⚠</span>
      )}
    </span>
  );
}
