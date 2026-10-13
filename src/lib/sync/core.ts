// Pure sync logic: no network, no storage (PROFILE_SYNC_PLAN.md Section 13).
// Imported by Node tests directly, so keep it free of imports and of TypeScript-only runtime syntax.

export type Platform = 'cf' | 'ac' | 'lc' | 'cses';

/** One cache entry per platform problem key. Times are Unix seconds. */
export interface Entry {
  firstAc: number | null;
  lastAc: number | null;
  /** Sorted: the first accepted time plus the newest ones (at most MAX_ACS). */
  acs: number[];
  tries: number;
  last: number;
  acTimeKnown: boolean;
}
export interface Cache {
  problems: Record<string, Entry>;
  highWater?: number;
  lastEpoch?: number;
  edgeIds?: number[];
}
export interface CfSubmission {
  id: number;
  creationTimeSeconds: number;
  problem: { contestId?: number; index: string };
  verdict?: string;
}
export interface AcSubmission {
  id: number;
  epoch_second: number;
  problem_id: string;
  result: string;
}
/** What the learner set by hand (the relevant part of a stored problem log). */
export interface LocalLog {
  status?: string;
  hintsOpened?: number;
}
export type Effective = { status: string | null; source: 'manual' | 'sync' | null; flag: 'no-ac-on-platform' | null };

// Site problem id -> { platform, key }. Formats from PLAN.md Section 9.1.
export function parseProblemId(id: string): { platform: Platform; key: string } | null {
  const m = /^(cf|ac|lc|cses)-(.+)$/.exec(id);
  if (!m) return null;
  return { platform: m[1] as Platform, key: m[2] };
}

// Codeforces API problem -> cache key "1234A", or null for problems the site never uses
// (no contestId, or Gym contests, whose ids are 100000 and above).
export function cfKey(problem?: { contestId?: number; index: string } | null): string | null {
  if (!problem || !Number.isInteger(problem.contestId) || (problem.contestId as number) >= 100000) return null;
  return `${problem.contestId}${problem.index}`;
}

export const MAX_ACS = 16;
function touch(map: Record<string, Entry>, key: string, t: number, accepted: boolean): void {
  const old = map[key];
  const e: Entry = old ? { ...old, acs: [...old.acs] } : { firstAc: null, lastAc: null, acs: [], tries: 0, last: 0, acTimeKnown: true };
  e.tries += 1;
  e.last = Math.max(e.last, t);
  if (accepted && !e.acs.includes(t)) {
    e.acs.push(t);
    e.acs.sort((x, y) => x - y);
    if (e.acs.length > MAX_ACS) e.acs.splice(1, e.acs.length - MAX_ACS); // keep the first AC and the newest ones
    e.firstAc = e.acs[0];
    e.lastAc = e.acs[e.acs.length - 1];
  }
  map[key] = e;
}

// Codeforces user.status result (any order). Only submissions with id > cache.highWater are applied,
// so folding the same page twice changes nothing. Unknown verdicts count as attempts.
export function foldCodeforces(cache: Cache, submissions: CfSubmission[]): Cache {
  const map = { ...cache.problems };
  let hw = cache.highWater ?? 0;
  for (const s of submissions) {
    if (s.id <= (cache.highWater ?? 0)) continue;
    const key = cfKey(s.problem);
    if (key && s.verdict !== 'COMPILATION_ERROR' && s.verdict !== 'TESTING' && s.verdict !== undefined) {
      touch(map, key, s.creationTimeSeconds, s.verdict === 'OK');
    }
    hw = Math.max(hw, s.id);
  }
  return { problems: map, highWater: hw };
}

// LeetCode snippet output: { slug: "ac" | "notac" | null }. No submission times are available,
// so the time an "ac" is first observed is used, flagged acTimeKnown = false.
export function foldLeetCode(cache: Cache, statuses: Record<string, string | null>, observedAt: number): Cache {
  const map = { ...cache.problems };
  for (const [slug, st] of Object.entries(statuses)) {
    const old = map[slug];
    if (st === 'ac') {
      if (old && old.firstAc !== null) continue; // keep the first observation
      map[slug] = { firstAc: observedAt, lastAc: observedAt, acs: [observedAt], tries: Math.max(1, old?.tries ?? 0), last: observedAt, acTimeKnown: false };
    } else if (st === 'notac' && !old) {
      map[slug] = { firstAc: null, lastAc: null, acs: [], tries: 1, last: observedAt, acTimeKnown: false };
    }
  }
  return { problems: map, highWater: cache.highWater ?? 0 };
}

const SOLVED = new Set(['Solved', 'Solved with hints', 'Read editorial']);

// Effective status shown everywhere. Manual statuses are stored; synced statuses are derived on read,
// never stored, so changing or removing a handle cannot corrupt the learner's log.
// local: the cp:v1:problems entry or undefined. entry: platform cache entry (after alias resolution) or undefined.
// Statuses use the display labels of PLAN.md 10.2; src/lib/sync/status.ts maps them to the site's storage keys.
export function effectiveStatus(local: LocalLog | undefined, entry: Entry | undefined): Effective {
  const manual = local?.status;
  if (manual && SOLVED.has(manual)) {
    return { status: manual, source: 'manual', flag: entry !== undefined && entry.firstAc == null ? 'no-ac-on-platform' : null };
  }
  if (entry && entry.firstAc !== null) {
    const hinted = (local?.hintsOpened ?? 0) > 0;
    return { status: hinted ? 'Solved with hints' : 'Solved', source: 'sync', flag: null };
  }
  if (manual === 'Attempted') return { status: 'Attempted', source: 'manual', flag: null };
  if (entry && entry.tries > 0) return { status: 'Attempted', source: 'sync', flag: null };
  return { status: null, source: null, flag: null };
}

// Look up a site problem in the caches, following Codeforces aliases (same problem in parallel divisions).
export function lookup(problemId: string, caches: Partial<Record<Platform, Cache>>, cfAliases: Record<string, string[]> = {}): Entry | undefined {
  const p = parseProblemId(problemId);
  if (!p || !caches[p.platform]) return undefined;
  const keys = p.platform === 'cf' ? [p.key, ...(cfAliases[p.key] ?? [])] : [p.key];
  let best: Entry | undefined;
  for (const k of keys) {
    const e = caches[p.platform]!.problems[k];
    if (!e) continue;
    if (!best) { best = { ...e, acs: [...e.acs] }; continue; }
    best.tries += e.tries;
    best.last = Math.max(best.last, e.last);
    best.acTimeKnown = best.acTimeKnown && e.acTimeKnown;
    best.acs = [...new Set([...best.acs, ...e.acs])].sort((x, y) => x - y);
    best.firstAc = best.acs.length ? best.acs[0] : null;
    best.lastAc = best.acs.length ? best.acs[best.acs.length - 1] : null;
  }
  return best;
}

// A reserved problem (drill, look-alike, checkpoint, review, exam) is compromised if it was accepted
// before the learner was first shown it. shownAt: seconds, or null if never shown.
export function isCompromised(entry: Entry | undefined, shownAt: number | null | undefined): boolean {
  if (!entry || entry.firstAc === null) return false;
  if (shownAt === null || shownAt === undefined) return true;
  return entry.firstAc < shownAt;
}

// Checkpoint and exam: solved in time if an accepted submission falls inside [start, end] (seconds).
// LeetCode entries have no submission times (acTimeKnown false), so the learner confirms by hand.
export function solvedInWindow(entry: Entry | undefined, start: number, end: number): 'yes' | 'no' | 'unknown' {
  if (!entry || entry.firstAc === null) return 'no';
  if (!entry.acTimeKnown) return 'unknown';
  return entry.acs.some((t) => t >= start && t <= end) ? 'yes' : 'no';
}

// Re-solve (PLAN.md 10.5): done if there is an accepted submission at or after the due time.
export function resolvedSince(entry: Entry | undefined, dueAt: number): boolean {
  if (!entry || !entry.acTimeKnown) return false;
  return entry.lastAc !== null && entry.lastAc >= dueAt;
}

// Pass rule scaling (Section 10.2): "need `need` of `total`" with k compromised problems becomes
// ceil(need * (total - k) / total) of the remaining total - k. null when nothing remains.
export function scaledPassRule(total: number, need: number, compromised: number): { need: number; of: number } | null {
  const rest = total - compromised;
  if (rest <= 0) return null;
  return { need: Math.ceil((need * rest) / total), of: rest };
}

// Cache size guard (Section 4): above `maxBytes` of JSON, drop entries for keys the site does not use (when `keep` is
// given), then the oldest attempt-only entries. Returns the pruned cache and how many entries were dropped.
export function pruneCache(cache: Cache, maxBytes: number, keep?: Set<string>): { cache: Cache; dropped: number } {
  if (JSON.stringify(cache).length <= maxBytes) return { cache, dropped: 0 };
  const problems = { ...cache.problems };
  let dropped = 0;
  const drop = (k: string) => { delete problems[k]; dropped++; };
  const size = () => JSON.stringify({ ...cache, problems }).length;
  if (keep) for (const k of Object.keys(problems)) if (!keep.has(k)) drop(k);
  if (size() > maxBytes) {
    const attemptsOnly = Object.entries(problems).filter(([, e]) => e.firstAc === null).sort((a, b) => a[1].last - b[1].last);
    for (const [k] of attemptsOnly) { if (size() <= maxBytes) break; drop(k); }
  }
  return { cache: { ...cache, problems }, dropped };
}

// Codeforces pagination. fetchPage(from, count) resolves to user.status "result" (newest first; from is 1-based).
// The caller's fetchPage enforces the rate limit. Stops at a short page or once it reaches submissions already applied.
export async function syncCodeforces(cache: Cache, fetchPage: (from: number, count: number) => Promise<CfSubmission[]>): Promise<Cache> {
  const known = cache.highWater ?? 0;
  const count = known === 0 ? 1000 : 100;
  const collected: CfSubmission[] = [];
  for (let from = 1; ; from += count) {
    const page = await fetchPage(from, count);
    collected.push(...page);
    if (page.length < count || page.some((s) => s.id <= known)) break;
  }
  return foldCodeforces(cache, collected);
}

// AtCoder Problems pagination. fetchFrom(fromSecond) resolves to up to 500 submissions with epoch_second >= fromSecond
// (S0 verified: the boundary second is inclusive). Cache: { problems, lastEpoch, edgeIds } where edgeIds are the ids
// already applied whose epoch_second == lastEpoch.
export const ATCODER_PAGE = 500;
export async function syncAtCoder(cache: Partial<Cache>, fetchFrom: (fromSecond: number) => Promise<AcSubmission[]>): Promise<Cache> {
  const map = { ...(cache.problems ?? {}) };
  let lastEpoch = cache.lastEpoch ?? 0;
  let edge = new Set<number>(cache.edgeIds ?? []);
  const seen = new Set<number>();
  let from = lastEpoch;
  for (;;) {
    const page = await fetchFrom(from);
    for (const s of [...page].sort((x, y) => x.epoch_second - y.epoch_second || x.id - y.id)) {
      if (seen.has(s.id)) continue;
      seen.add(s.id);
      if (s.epoch_second < lastEpoch || (s.epoch_second === lastEpoch && edge.has(s.id))) continue;
      if (s.result !== 'CE' && s.result !== 'WJ') touch(map, s.problem_id, s.epoch_second, s.result === 'AC');
      if (s.epoch_second > lastEpoch) { lastEpoch = s.epoch_second; edge = new Set(); }
      edge.add(s.id);
    }
    if (page.length < ATCODER_PAGE) break;
    const maxT = Math.max(...page.map((s) => s.epoch_second));
    from = maxT > from ? maxT : from + 1;
  }
  return { problems: map, lastEpoch, edgeIds: [...edge] };
}
