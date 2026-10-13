// Protecting reserved problems (PROFILE_SYNC_PLAN.md Section 10): a drill item, look-alike, checkpoint, review or exam
// problem that was accepted before it was first shown no longer tests recognition.
import { isCompromised, lookup, parseProblemId, scaledPassRule, solvedInWindow, type Cache, type Entry, type Platform } from './core.ts';
import { CF_ALIASES } from './aliases.ts';
import { getCaches, getProfiles, getShown, markShown, nowSec } from './store.ts';
import { syncPlatform } from './runner.ts';

export type Verification = 'yes' | 'no' | 'unknown';

/** Platforms (cf, ac) that have a linked profile among these problem ids. */
export function syncablePlatforms(ids: string[]): ('cf' | 'ac')[] {
  const p = getProfiles();
  const wanted = new Set(ids.map((id) => parseProblemId(id)?.platform));
  const out: ('cf' | 'ac')[] = [];
  if (wanted.has('cf') && p.codeforces) out.push('cf');
  if (wanted.has('ac') && p.atcoder) out.push('ac');
  return out;
}

/** Syncs the platforms involved unless a sync ran within `maxAgeS` seconds (Section 10.2: 5 minutes; 0 forces one). */
export async function ensureFresh(ids: string[], maxAgeS: number): Promise<void> {
  const p = getProfiles();
  const jobs = syncablePlatforms(ids).filter((pl) => {
    const last = pl === 'cf' ? p.codeforces?.lastSyncAt : p.atcoder?.lastSyncAt;
    return maxAgeS === 0 || !last || nowSec() - last > maxAgeS;
  });
  await Promise.all(jobs.map((pl) => syncPlatform(pl)));
}

const entryIn = (caches: Partial<Record<Platform, Cache>>, id: string): Entry | undefined => lookup(id, caches, CF_ALIASES);

/** Pure: which of `ids` are compromised given the caches and the shown times. */
export function compromisedIn(ids: string[], caches: Partial<Record<Platform, Cache>>, shown: Record<string, number>): Set<string> {
  return new Set(ids.filter((id) => isCompromised(entryIn(caches, id), shown[id] ?? null)));
}

/**
 * Called when a set of reserved problems is about to be displayed: finds the compromised ones (judged against the
 * time they were first shown, which is "never" for the first display), then records the display time.
 */
export function beginReservedSet(ids: string[]): Set<string> {
  const bad = compromisedIn(ids, getCaches(), getShown());
  markShown(ids);
  return bad;
}

/** Checkpoint and exam: verification of each problem inside the timer window, from the freshly synced caches. */
export function verifyWindow(ids: string[], startSec: number, endSec: number): Record<string, { result: Verification; platform: Platform | null }> {
  const caches = getCaches();
  const out: Record<string, { result: Verification; platform: Platform | null }> = {};
  for (const id of ids) {
    const platform = parseProblemId(id)?.platform ?? null;
    // Nothing to check against (platform not linked, or CSES): the learner confirms by hand.
    const checkable = platform !== null && platform !== 'cses' && caches[platform] !== undefined;
    out[id] = { result: checkable ? solvedInWindow(entryIn(caches, id), startSec, endSec) : 'unknown', platform };
  }
  return out;
}

export { scaledPassRule };
export const COMPROMISED_NOTE = (firstAc: number | null) =>
  `You solved this before it was assigned${firstAc ? ` (${new Date(firstAc * 1000).toLocaleDateString()})` : ''}. It no longer tests recognition, so it does not count toward the pass rule.`;
