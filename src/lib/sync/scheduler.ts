// When to sync (PROFILE_SYNC_PLAN.md Section 1): on page open if the last sync is older than 15 minutes, and when the
// tab becomes visible again (at most once a minute per platform). "Sync now" calls syncPlatform directly.
import { getProfiles, nowSec } from './store.ts';
import { syncPlatform, setSiteBase } from './runner.ts';

export const OPEN_AGE_S = 15 * 60;
export const RETURN_GAP_S = 60;
const lastTry: Record<string, number> = {};

/** Pure decision, exported for tests. */
export function shouldSync(lastSyncAt: number | null | undefined, lastTryAt: number | undefined, now: number, minAgeS: number): boolean {
  if (lastTryAt !== undefined && now - lastTryAt < RETURN_GAP_S) return false;
  return !lastSyncAt || now - lastSyncAt >= minAgeS;
}

function maybeSync(minAgeS: number) {
  const p = getProfiles();
  const now = nowSec();
  const jobs: ['cf' | 'ac', number | null | undefined][] = [];
  if (p.codeforces) jobs.push(['cf', p.codeforces.lastSyncAt]);
  if (p.atcoder) jobs.push(['ac', p.atcoder.lastSyncAt]);
  for (const [platform, last] of jobs) {
    if (!shouldSync(last, lastTry[platform], now, minAgeS)) continue;
    lastTry[platform] = now;
    void syncPlatform(platform);
  }
}

let started = false;
export function startScheduler(siteBase: string): void {
  if (started || typeof window === 'undefined') return;
  started = true;
  setSiteBase(siteBase);
  maybeSync(OPEN_AGE_S);
  document.addEventListener('visibilitychange', () => {
    // Returning from a problem tab: sync if the last sync is more than a minute old.
    if (document.visibilityState === 'visible') maybeSync(RETURN_GAP_S);
  });
}
