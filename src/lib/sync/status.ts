// The one function that decides every status shown on the site (PROFILE_SYNC_PLAN.md Sections 3 and 9).
// Manual statuses live in cp:v1:problems; platform statuses are derived here at read time and never stored.
import { effectiveStatus, lookup, parseProblemId, type Cache, type Entry, type Platform } from './core.ts';
import type { Profiles } from './store.ts';
import type { ProblemLog, ProblemStatus } from '../storage.ts';

const KEY_TO_LABEL: Record<ProblemStatus, string> = {
  attempted: 'Attempted',
  solved: 'Solved',
  solved_hints: 'Solved with hints',
  editorial: 'Read editorial',
};
const LABEL_TO_KEY: Record<string, ProblemStatus> = Object.fromEntries(Object.entries(KEY_TO_LABEL).map(([k, v]) => [v, k as ProblemStatus]));

export interface StatusView {
  status: ProblemStatus | null;
  source: 'manual' | 'sync' | null;
  flag: 'no-ac-on-platform' | null;
  /** Platform behind a synced status or a flag (cf, ac, lc), when there is one. */
  platform: Platform | null;
  /** Unix seconds of the last sync/import of that platform. */
  syncedAt: number | null;
}

const EMPTY_ENTRY: Entry = { firstAc: null, lastAc: null, acs: [], tries: 0, last: 0, acTimeKnown: true };

/** Pure: combines the learner's own log with the caches. A linked platform with no record of the problem counts as "no accepted submission". */
export function computeStatus(
  problemId: string,
  local: ProblemLog | undefined,
  caches: Partial<Record<Platform, Cache>>,
  profiles: Profiles,
  aliases: Record<string, string[]> = {},
): StatusView {
  const p = parseProblemId(problemId);
  const entryFound = lookup(problemId, caches, aliases);
  const synced = p ? caches[p.platform] !== undefined : false;
  const entry = entryFound ?? (synced ? EMPTY_ENTRY : undefined);
  const eff = effectiveStatus(local ? { status: local.status ? KEY_TO_LABEL[local.status] : undefined, hintsOpened: local.hintsOpened } : undefined, entry);
  const syncedAt = !p ? null
    : p.platform === 'cf' ? profiles.codeforces?.lastSyncAt ?? null
    : p.platform === 'ac' ? profiles.atcoder?.lastSyncAt ?? null
    : p.platform === 'lc' ? profiles.leetcode?.lastImportAt ?? null : null;
  return {
    status: eff.status ? LABEL_TO_KEY[eff.status] : null,
    source: eff.source,
    flag: eff.flag,
    platform: eff.source === 'sync' || eff.flag ? p?.platform ?? null : null,
    syncedAt,
  };
}

/** "Solved" for ladder progress and counts: solved, or solved with hints (the same rule as storage.isSolved). */
export const isSolvedView = (v: StatusView) => v.status === 'solved' || v.status === 'solved_hints';
