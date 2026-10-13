// Builds src/data/sync/cf-aliases.json (PROFILE_SYNC_PLAN.md Section 5.2): for every Codeforces problem key used on the
// site, the keys of its twin in a parallel round (same start time, same problem name), for example 1234A <-> 1233C.
// Run by hand (Node 18+) whenever Codeforces problems are added. Responses are cached in .cache/cf/ (gitignored);
// calls are spaced 2.1 s apart as Codeforces asks. Use --refresh to ignore the cache.
import { mkdirSync, readFileSync, writeFileSync, existsSync, readdirSync } from 'node:fs';
import { join } from 'node:path';

const ROOT = new URL('..', import.meta.url).pathname;
const CACHE = join(ROOT, '.cache', 'cf');
const refresh = process.argv.includes('--refresh');
mkdirSync(CACHE, { recursive: true });

/** Every cf-... id mentioned in the topic and bank data files, as a cache key like 1234A. */
export function siteCfKeys(root = ROOT) {
  const keys = new Set();
  for (const dir of ['src/data/topics', 'src/data/bank']) {
    for (const f of readdirSync(join(root, dir))) {
      if (!f.endsWith('.yaml')) continue;
      for (const m of readFileSync(join(root, dir, f), 'utf8').matchAll(/\bcf-(\d+[A-Z]\d?)\b/g)) keys.add(m[1]);
    }
  }
  return [...keys].sort();
}

/** Contest ids that share a start time with at least one other contest and include a contest the site uses. */
export function parallelContests(siteKeys, contests) {
  const siteContests = new Set(siteKeys.map((k) => Number(/^\d+/.exec(k)[0])));
  const byStart = new Map();
  for (const c of contests) {
    if (c.startTimeSeconds === undefined) continue;
    if (!byStart.has(c.startTimeSeconds)) byStart.set(c.startTimeSeconds, []);
    byStart.get(c.startTimeSeconds).push(c.id);
  }
  const need = new Set();
  for (const ids of byStart.values()) if (ids.length > 1 && ids.some((i) => siteContests.has(i))) ids.forEach((i) => need.add(i));
  return [...need].sort((a, b) => a - b);
}

/**
 * Pure: twins from the contest list and each contest's problem list.
 * S0 finding: problemset.problems lists a shared problem only once (under the Div. 1 round), so the Div. 2 copy
 * (for example 1501C for 1500A) must come from contest.standings, which lists every problem of that round. Codeforces allows it only as a bare
 * `contest.standings?contestId=<id>` request (no from/count), so each response is large (a few MB); they are trimmed and cached.
 * problemsOf(contestId) -> [{index, name}] (empty when unknown).
 */
export function buildAliases(siteKeys, contests, problemsOf) {
  const startOf = new Map(contests.map((c) => [c.id, c.startTimeSeconds]));
  const byStart = new Map();
  for (const c of contests) {
    if (c.startTimeSeconds === undefined) continue;
    if (!byStart.has(c.startTimeSeconds)) byStart.set(c.startTimeSeconds, []);
    byStart.get(c.startTimeSeconds).push(c.id);
  }
  const out = {};
  for (const key of siteKeys) {
    const m = /^(\d+)(.+)$/.exec(key);
    const contestId = Number(m[1]);
    const name = problemsOf(contestId).find((p) => p.index === m[2])?.name;
    const twins = [];
    if (name !== undefined) {
      for (const other of byStart.get(startOf.get(contestId)) ?? []) {
        if (other === contestId) continue;
        for (const p of problemsOf(other)) if (p.name === name) twins.push(`${other}${p.index}`);
      }
    }
    out[key] = twins.sort();
  }
  return out;
}

// `trim` reduces a response before it is cached (contest.standings carries thousands of rows we do not need).
async function cached(name, url, trim = (r) => r) {
  const file = join(CACHE, name);
  if (!refresh && existsSync(file)) return JSON.parse(readFileSync(file, 'utf8'));
  await new Promise((r) => setTimeout(r, 2100));
  const res = await fetch(url);
  const body = await res.json();
  if (body.status !== 'OK') throw new Error(`${url}: ${body.comment ?? res.status}`);
  const result = trim(body.result);
  writeFileSync(file, JSON.stringify(result));
  return result;
}

if (process.argv[1] && process.argv[1].endsWith('cf_aliases.mjs')) {
  const keys = siteCfKeys();
  const contests = await cached('contest.list.json', 'https://codeforces.com/api/contest.list');
  const need = parallelContests(keys, contests);
  console.log(`${keys.length} site keys; fetching ${need.length} contests that ran in parallel with another (about ${Math.ceil((need.length * 2.1) / 60)} minutes uncached)`);
  const problems = new Map();
  for (const id of need) {
    try {
      const r = await cached(`standings-${id}.json`, `https://codeforces.com/api/contest.standings?contestId=${id}`, (res) => ({ problems: res.problems.map((p) => ({ index: p.index, name: p.name })) }));
      problems.set(id, r.problems);
    } catch (e) {
      console.warn(`contest ${id}: ${e.message}`);
    }
  }
  const aliases = buildAliases(keys, contests, (id) => problems.get(id) ?? []);
  writeFileSync(join(ROOT, 'src/data/sync/cf-aliases.json'), JSON.stringify(aliases, null, 1) + '\n');
  console.log(`${keys.length} Codeforces keys, ${Object.values(aliases).filter((a) => a.length).length} with a twin`);
}
