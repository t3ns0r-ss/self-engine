// Runs a sync for one platform against browser storage and records the outcome (PROFILE_SYNC_PLAN.md Sections 3, 6, 11).
import { foldLeetCode, pruneCache, type Cache } from './core.ts';
import { CF_ALIASES } from './aliases.ts';
import { TransportError } from './transport.ts';
import { makeGate, newCounters, syncAc, syncCf, totalTries, verifyCfHandle, type Net } from './platforms.ts';
import { announceUpdate, appendSyncLog, clearCache, getCache, getProfiles, getSyncLog, nowSec, patchProfile, saveCache, saveProfiles } from './store.ts';
import type { LcPayload } from './schemas.ts';
import type { AcSubmission, CfSubmission } from './core.ts';
import { foldCodeforces, syncAtCoder } from './core.ts';
import type { TransportName } from './transport.ts';

let proxyBase: string | null | undefined;
/** Reads public/sync-config.json once (Section 7.3). */
async function loadProxyBase(base: string): Promise<string | null> {
  if (proxyBase !== undefined) return proxyBase;
  try {
    const res = await fetch(`${base.replace(/\/$/, '')}/sync-config.json`);
    const j = (await res.json()) as { proxyBase?: string | null };
    proxyBase = typeof j.proxyBase === 'string' ? j.proxyBase : null;
  } catch {
    proxyBase = null;
  }
  return proxyBase;
}

const gates = { cf: makeGate('cf'), ac: makeGate('ac') };
const preferred: { cf?: TransportName; ac?: TransportName } = {};
export interface SyncResult { added: number; error: string | null }
const running: { cf?: Promise<SyncResult>; ac?: Promise<SyncResult> } = {};
let siteBase = '/';
export const setSiteBase = (b: string) => { siteBase = b; };

async function netFor(p: 'cf' | 'ac'): Promise<Net> {
  return { gate: gates[p], transport: { proxyBase: await loadProxyBase(siteBase), preferred: preferred[p] } };
}
const describe = (e: unknown, platform?: 'cf' | 'ac') =>
  e instanceof TransportError
    ? platform === 'cf'
      ? 'Codeforces sync unavailable from this site address; use Import on this page.'
      : 'AtCoder Problems could not be reached from this site address or is down (see https://github.com/kenkoooo/AtCoderProblems); use Import on this page. Manual statuses still work.'
    : e instanceof Error ? e.message : String(e);
const MAX_CACHE_BYTES = 1_500_000;
/** The Codeforces keys the site uses, with their twins (Section 4: prune everything else when a cache grows too big). */
const SITE_CF_KEYS = new Set(Object.entries(CF_ALIASES).flat(2));

/** Consecutive failed runs of a platform at the end of the sync log (the dashboard banner shows at 3). */
export function failingRuns(platform: string): { count: number; since: number | null; message: string | null } {
  const rows = getSyncLog().filter((r) => r.platform === platform);
  let count = 0;
  let since: number | null = null;
  let message: string | null = null;
  for (let i = rows.length - 1; i >= 0 && rows[i].error; i--) { count++; since = rows[i].at; message ??= rows[i].error; }
  return { count, since, message };
}

async function run(platform: 'cf' | 'ac'): Promise<SyncResult> {
  const profiles = getProfiles();
  const t0 = Date.now();
  const c = newCounters();
  const key = platform === 'cf' ? 'codeforces' : 'atcoder';
  const prof = platform === 'cf' ? profiles.codeforces : profiles.atcoder;
  if (!prof) return { added: 0, error: 'No account is linked.' };
  const name = platform === 'cf' ? (prof as { handle: string }).handle : (prof as { userId: string }).userId;
  const before = getCache(platform);
  let error: string | null = null;
  let added = 0;
  const notes: string[] = [];
  try {
    const net = await netFor(platform);
    const base: Cache = before ?? { problems: {}, highWater: 0 };
    const synced = platform === 'cf' ? await syncCf(net, c, base, name) : await syncAc(net, c, base, name);
    const { cache: next, dropped } = pruneCache(synced, MAX_CACHE_BYTES, platform === 'cf' ? SITE_CF_KEYS : undefined);
    if (dropped) notes.push(`cache over 1.5 MB: dropped ${dropped} entries`);
    if (!saveCache(platform, next)) throw new Error('Browser storage is full or unavailable, so the synced data could not be saved.');
    if (platform === 'ac' && !before && Object.keys(next.problems).length === 0)
      error = 'No submissions found for this user id. AtCoder user ids are case-insensitive on AtCoder Problems, but check the spelling.';
    preferred[platform] = c.transport ?? preferred[platform];
    patchProfile(key, { lastSyncAt: nowSec(), lastError: error, transport: c.transport } as never);
    added = totalTries(next) - totalTries(before);
    announceUpdate({ platform, message: added > 0 ? `${added} new submission${added === 1 ? '' : 's'} synced from ${platform === 'cf' ? 'Codeforces' : 'AtCoder'}` : undefined });
    appendSyncLog({ at: nowSec(), platform, transport: c.transport, requests: c.requests, newSubmissions: added, ms: Date.now() - t0, error, ...(c.unknownVerdicts.size ? (notes.push(`unknown verdicts counted as attempts: ${[...c.unknownVerdicts].join(', ')}`), {}) : {}), ...(notes.length ? { note: notes.join('; ') } : {}) } as never);
  } catch (e) {
    error = describe(e, platform);
    patchProfile(key, { lastError: error } as never);
    appendSyncLog({ at: nowSec(), platform, transport: c.transport, requests: c.requests, newSubmissions: 0, ms: Date.now() - t0, error });
    announceUpdate({ platform });
  }
  return { added, error };
}

/** Syncs one platform now. Concurrent calls share one run. */
export function syncPlatform(platform: 'cf' | 'ac'): Promise<SyncResult> {
  return (running[platform] ??= run(platform).finally(() => { running[platform] = undefined; }));
}

/** Adds the learner's handle after checking it (Codeforces) and runs the first sync. */
export async function linkCodeforces(handle: string): Promise<string | null> {
  const c = newCounters();
  try {
    const canonical = await verifyCfHandle(await netFor('cf'), c, handle.trim());
    const all = getProfiles();
    if (all.codeforces?.handle !== canonical) clearCache('cf');
    all.codeforces = { handle: canonical, addedAt: nowSec(), lastSyncAt: null, lastError: null, transport: c.transport };
    saveProfiles(all);
    return (await syncPlatform('cf')).error;
  } catch (e) {
    return describe(e, 'cf');
  }
}
export async function linkAtCoder(userId: string): Promise<string | null> {
  const id = userId.trim();
  if (!/^[A-Za-z0-9_]{3,16}$/.test(id)) return 'AtCoder user ids are 3 to 16 letters, digits, or underscores.';
  const all = getProfiles();
  if (all.atcoder?.userId !== id) clearCache('ac');
  all.atcoder = { userId: id, addedAt: nowSec(), lastSyncAt: null, lastError: null, transport: null };
  saveProfiles(all);
  return (await syncPlatform('ac')).error;
}
/** Checks a Codeforces handle without saving it. Returns the canonical handle or an error message. */
export async function verifyCodeforces(handle: string): Promise<{ handle?: string; error?: string }> {
  try {
    return { handle: await verifyCfHandle(await netFor('cf'), newCounters(), handle.trim()) };
  } catch (e) {
    return { error: describe(e, 'cf') };
  }
}
export function setLeetCodeUsername(username: string): void {
  const all = getProfiles();
  all.leetcode = { ...all.leetcode, username: username.trim() };
  saveProfiles(all);
}
/** Removes a handle and its cached submissions; the learner's own log is untouched. */
export function removeProfile(which: 'codeforces' | 'atcoder' | 'leetcode'): void {
  const all = getProfiles();
  delete all[which];
  saveProfiles(all);
  clearCache(which === 'codeforces' ? 'cf' : which === 'atcoder' ? 'ac' : 'lc');
  announceUpdate({ platform: which });
}

/** Applies an imported LeetCode result or a saved Codeforces/AtCoder response. Returns a message. */
export function applyImport(result: { kind: 'lc'; payload: LcPayload } | { kind: 'cf'; submissions: CfSubmission[] } | { kind: 'ac'; submissions: AcSubmission[] }): Promise<string> | string {
  if (result.kind === 'lc') {
    const next = foldLeetCode(getCache('lc') ?? { problems: {} }, result.payload.statuses, nowSec());
    saveCache('lc', next);
    const all = getProfiles();
    all.leetcode = { username: all.leetcode?.username || result.payload.username, lastImportAt: nowSec(), method: result.payload.method };
    saveProfiles(all);
    announceUpdate({ platform: 'lc', message: `${Object.keys(result.payload.statuses).length} problems updated from LeetCode` });
    return `Imported ${Object.keys(result.payload.statuses).length} LeetCode problems.`;
  }
  if (result.kind === 'cf') {
    saveCache('cf', foldCodeforces(getCache('cf') ?? { problems: {}, highWater: 0 }, result.submissions));
    const all = getProfiles();
    if (all.codeforces) { all.codeforces.lastSyncAt = nowSec(); saveProfiles(all); }
    announceUpdate({ platform: 'cf', message: 'Codeforces submissions imported' });
    return `Imported ${result.submissions.length} Codeforces submissions.${all.codeforces ? '' : ' Save a handle to keep it in sync.'}`;
  }
  return syncAtCoder(getCache('ac') ?? {}, async (from) => result.submissions.filter((s) => s.epoch_second >= from)).then((next) => {
    saveCache('ac', next);
    const all = getProfiles();
    if (all.atcoder) { all.atcoder.lastSyncAt = nowSec(); saveProfiles(all); }
    announceUpdate({ platform: 'ac', message: 'AtCoder submissions imported' });
    return `Imported ${result.submissions.length} AtCoder submissions.`;
  });
}
