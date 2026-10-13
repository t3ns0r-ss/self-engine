// Storage for profile sync (PROFILE_SYNC_PLAN.md Section 4), on top of the site's storage module.
import { KEYS, SYNC_KEYS, read, write } from '../storage.ts';
import type { Cache, Platform } from './core.ts';

export const SYNC_EVENT = 'cp:sync-updated';

export interface CfProfile { handle: string; addedAt: number; lastSyncAt?: number | null; lastError?: string | null; transport?: string | null }
export interface AcProfile { userId: string; addedAt: number; lastSyncAt?: number | null; lastError?: string | null; transport?: string | null }
export interface LcProfile { username: string; lastImportAt?: number | null; method?: string | null }
export interface Profiles { codeforces?: CfProfile; atcoder?: AcProfile; leetcode?: LcProfile }
export interface SyncLogRow { at: number; platform: string; transport: string | null; requests: number; newSubmissions: number; ms: number; error: string | null; note?: string }

const obj = <T>(v: unknown): T => (v && typeof v === 'object' && !Array.isArray(v) ? (v as T) : ({} as T));
export const nowSec = () => Math.floor(Date.now() / 1000);

export const getProfiles = (): Profiles => obj<Profiles>(read(KEYS.profiles, {}));
export function saveProfiles(next: Profiles): boolean {
  return write(KEYS.profiles, next);
}
export function patchProfile<K extends keyof Profiles>(key: K, patch: Partial<NonNullable<Profiles[K]>>): boolean {
  const all = getProfiles();
  const current = all[key];
  if (!current) return false;
  all[key] = { ...current, ...patch } as Profiles[K];
  return saveProfiles(all);
}

const cacheKey = (p: 'cf' | 'ac' | 'lc') => (p === 'cf' ? SYNC_KEYS.cf : p === 'ac' ? SYNC_KEYS.ac : KEYS.syncLc);
/** The cache for a platform, or undefined if it has never been synced. */
export function getCache(p: 'cf' | 'ac' | 'lc'): Cache | undefined {
  const v = read<unknown>(cacheKey(p), null);
  return v && typeof v === 'object' && !Array.isArray(v) && typeof (v as Cache).problems === 'object' ? (v as Cache) : undefined;
}
export function saveCache(p: 'cf' | 'ac' | 'lc', cache: Cache): boolean {
  return write(cacheKey(p), cache);
}
export function clearCache(p: 'cf' | 'ac' | 'lc'): void {
  try {
    globalThis.localStorage?.removeItem(cacheKey(p));
    globalThis.dispatchEvent?.(new CustomEvent(SYNC_EVENT));
  } catch { /* storage unavailable */ }
}
export const getCaches = (): Partial<Record<Platform, Cache>> => ({ cf: getCache('cf'), ac: getCache('ac'), lc: getCache('lc') });

/** When each reserved problem was first displayed (Section 10.1). */
export const getShown = (): Record<string, number> => obj<Record<string, number>>(read(KEYS.shown, {}));
export function markShown(ids: string[]): void {
  const all = getShown();
  let changed = false;
  for (const id of ids) if (all[id] === undefined) { all[id] = nowSec(); changed = true; }
  if (changed) write(KEYS.shown, all);
}

export const getSyncLog = (): SyncLogRow[] => {
  const v = read<unknown>(SYNC_KEYS.log, []);
  return Array.isArray(v) ? (v as SyncLogRow[]) : [];
};
export function appendSyncLog(row: SyncLogRow): void {
  write(SYNC_KEYS.log, [...getSyncLog(), row].slice(-20));
}

/** Tells every island that cached submissions or profiles changed. */
export function announceUpdate(detail: { platform: string; message?: string }): void {
  globalThis.dispatchEvent?.(new CustomEvent(SYNC_EVENT, { detail }));
}
