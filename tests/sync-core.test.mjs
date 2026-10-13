// Unit tests for src/lib/sync/core.ts (PROFILE_SYNC_PLAN.md Section 13), ported from the plan's reference tests.
import test from 'node:test';
import assert from 'node:assert/strict';
import * as c from '../src/lib/sync/core.ts';

const sub = (id, contestId, index, verdict, t) => ({ id, creationTimeSeconds: t, problem: { contestId, index, name: 'x' }, verdict });

test('parseProblemId handles all four formats and rejects others', () => {
  assert.deepEqual(c.parseProblemId('cf-1520B1'), { platform: 'cf', key: '1520B1' });
  assert.deepEqual(c.parseProblemId('ac-abc300_c'), { platform: 'ac', key: 'abc300_c' });
  assert.deepEqual(c.parseProblemId('lc-two-sum'), { platform: 'lc', key: 'two-sum' });
  assert.deepEqual(c.parseProblemId('cses-1640'), { platform: 'cses', key: '1640' });
  assert.equal(c.parseProblemId('x-1'), null);
});

test('cfKey ignores gym and problems without a contest', () => {
  assert.equal(c.cfKey({ contestId: 1234, index: 'A' }), '1234A');
  assert.equal(c.cfKey({ contestId: 100001, index: 'A' }), null);
  assert.equal(c.cfKey({ index: 'A' }), null);
});

test('foldCodeforces: attempts, first and last AC, compile errors ignored, idempotent', () => {
  const page = [sub(5, 1234, 'A', 'OK', 500), sub(4, 1234, 'A', 'WRONG_ANSWER', 400),
                sub(3, 1234, 'A', 'OK', 300), sub(2, 1234, 'B', 'COMPILATION_ERROR', 200),
                sub(1, 100001, 'A', 'OK', 100)];
  const a = c.foldCodeforces({ problems: {}, highWater: 0 }, page);
  assert.deepEqual(a.problems['1234A'], { firstAc: 300, lastAc: 500, acs: [300, 500], tries: 3, last: 500, acTimeKnown: true });
  assert.equal(a.problems['1234B'], undefined);
  assert.equal(a.highWater, 5);
  const b = c.foldCodeforces(a, page);
  assert.deepEqual(b, a);
  const d = c.foldCodeforces(a, [sub(6, 1234, 'B', 'WRONG_ANSWER', 600), ...page]);
  assert.deepEqual(d.problems['1234B'], { firstAc: null, lastAc: null, acs: [], tries: 1, last: 600, acTimeKnown: true });
});

test('foldLeetCode keeps the first observation time and marks it unknown', () => {
  const a = c.foldLeetCode({ problems: {} }, { 'two-sum': 'ac', 'lru-cache': 'notac', x: null }, 1000);
  assert.deepEqual(a.problems['two-sum'], { firstAc: 1000, lastAc: 1000, acs: [1000], tries: 1, last: 1000, acTimeKnown: false });
  assert.equal(a.problems['lru-cache'].firstAc, null);
  assert.equal(a.problems['x'], undefined);
  const b = c.foldLeetCode(a, { 'two-sum': 'ac', 'lru-cache': 'ac' }, 2000);
  assert.equal(b.problems['two-sum'].firstAc, 1000);
  assert.equal(b.problems['lru-cache'].firstAc, 2000);
});

test('effectiveStatus: manual solved statuses win; sync upgrades none and Attempted; hints respected', () => {
  const ac = { firstAc: 1, lastAc: 1, acs: [1], tries: 1, last: 1, acTimeKnown: true };
  const wa = { firstAc: null, lastAc: null, acs: [], tries: 2, last: 1, acTimeKnown: true };
  assert.deepEqual(c.effectiveStatus(undefined, undefined), { status: null, source: null, flag: null });
  assert.equal(c.effectiveStatus(undefined, wa).status, 'Attempted');
  assert.equal(c.effectiveStatus(undefined, wa).source, 'sync');
  assert.equal(c.effectiveStatus(undefined, ac).status, 'Solved');
  assert.equal(c.effectiveStatus({ status: 'Attempted', hintsOpened: 2 }, ac).status, 'Solved with hints');
  assert.deepEqual(c.effectiveStatus({ status: 'Read editorial' }, ac), { status: 'Read editorial', source: 'manual', flag: null });
  assert.equal(c.effectiveStatus({ status: 'Solved' }, wa).flag, 'no-ac-on-platform');
  assert.equal(c.effectiveStatus({ status: 'Solved' }, undefined).flag, null);
  assert.equal(c.effectiveStatus({ status: 'Attempted' }, undefined).status, 'Attempted');
  assert.equal(c.effectiveStatus({ status: 'Attempted' }, wa).source, 'manual');
});

test('lookup merges Codeforces aliases', () => {
  const caches = { cf: { problems: { '1233C': { firstAc: 50, lastAc: 50, acs: [50], tries: 1, last: 50, acTimeKnown: true },
                                     '1234A': { firstAc: null, lastAc: null, acs: [], tries: 2, last: 40, acTimeKnown: true } } } };
  const e = c.lookup('cf-1234A', caches, { '1234A': ['1233C'] });
  assert.deepEqual(e, { firstAc: 50, lastAc: 50, acs: [50], tries: 3, last: 50, acTimeKnown: true });
  assert.equal(c.lookup('ac-abc1_a', caches), undefined);
});

test('isCompromised, solvedInWindow, resolvedSince', () => {
  const e = { firstAc: 100, lastAc: 900, acs: [100, 900], tries: 3, last: 900, acTimeKnown: true };
  assert.equal(c.isCompromised(e, null), true);
  assert.equal(c.isCompromised(e, 50), false);
  assert.equal(c.isCompromised(e, 150), true);
  assert.equal(c.isCompromised({ firstAc: null }, null), false);
  assert.equal(c.solvedInWindow(e, 850, 950), 'yes');
  assert.equal(c.solvedInWindow(e, 50, 120), 'yes');
  assert.equal(c.solvedInWindow(e, 200, 300), 'no');
  assert.equal(c.solvedInWindow({ ...e, acTimeKnown: false }, 850, 950), 'unknown');
  assert.equal(c.resolvedSince(e, 900), true);
  assert.equal(c.resolvedSince(e, 901), false);
});

test('scaledPassRule scales "2 of 3" by compromised count (k = 0..3)', () => {
  assert.deepEqual(c.scaledPassRule(3, 2, 0), { need: 2, of: 3 });
  assert.deepEqual(c.scaledPassRule(3, 2, 1), { need: 2, of: 2 }); // ceil(2*2/3)=2
  assert.deepEqual(c.scaledPassRule(3, 2, 2), { need: 1, of: 1 }); // ceil(2*1/3)=1
  assert.equal(c.scaledPassRule(3, 2, 3), null);
});

test('pruneCache: untouched below the limit; drops unused keys first, then the oldest attempt-only entries', () => {
  const e = (firstAc, last) => ({ firstAc, lastAc: firstAc, acs: firstAc ? [firstAc] : [], tries: 1, last, acTimeKnown: true });
  const cache = { problems: { a: e(5, 5), b: e(null, 1), c: e(null, 9), d: e(7, 7) }, highWater: 3 };
  assert.deepEqual(c.pruneCache(cache, 1e6), { cache, dropped: 0 });
  const small = JSON.stringify({ ...cache, problems: { a: cache.problems.a, d: cache.problems.d } }).length;
  const byKeep = c.pruneCache(cache, small, new Set(['a', 'd']));
  assert.deepEqual(Object.keys(byKeep.cache.problems).sort(), ['a', 'd']);
  const oldest = JSON.stringify({ ...cache, problems: { a: cache.problems.a, c: cache.problems.c, d: cache.problems.d } }).length;
  const byAge = c.pruneCache(cache, oldest);
  assert.deepEqual(Object.keys(byAge.cache.problems).sort(), ['a', 'c', 'd']); // b is the oldest attempt-only entry
  assert.equal(byAge.cache.highWater, 3);
});

test('acs keeps the first AC and the newest ones, capped', () => {
  const subs = [];
  for (let i = 1; i <= 40; i++) subs.push(sub(i, 1, 'A', 'OK', i * 10));
  const a = c.foldCodeforces({ problems: {}, highWater: 0 }, subs);
  const e = a.problems['1A'];
  assert.equal(e.acs.length, c.MAX_ACS);
  assert.equal(e.firstAc, 10);
  assert.equal(e.lastAc, 400);
  assert.equal(e.acs[1], 400 - (c.MAX_ACS - 2) * 10);
});

test('syncCodeforces paginates until a short page or known submissions', async () => {
  const all = [];
  for (let i = 2500; i >= 1; i--) all.push(sub(i, 1000 + (i % 7), 'A', i % 3 === 0 ? 'OK' : 'WRONG_ANSWER', i));
  const calls = [];
  const fetchPage = async (from, count) => { calls.push([from, count]); return all.slice(from - 1, from - 1 + count); };
  const a = await c.syncCodeforces({ problems: {}, highWater: 0 }, fetchPage);
  assert.deepEqual(calls, [[1, 1000], [1001, 1000], [2001, 1000]]);
  assert.equal(a.highWater, 2500);
  assert.equal(Object.values(a.problems).reduce((x, e) => x + e.tries, 0), 2500);
  all.unshift(sub(2503, 1000, 'A', 'OK', 2503), sub(2502, 1000, 'A', 'OK', 2502), sub(2501, 1000, 'A', 'OK', 2501));
  calls.length = 0;
  const b = await c.syncCodeforces(a, fetchPage);
  assert.deepEqual(calls, [[1, 100]]);
  assert.equal(Object.values(b.problems).reduce((x, e) => x + e.tries, 0), 2503);
  const again = await c.syncCodeforces(b, fetchPage);
  assert.deepEqual(again, b);
});

test('syncAtCoder: pages by time, overlapping boundary second, idempotent across runs', async () => {
  const all = [];
  let id = 1;
  for (let t = 1; t <= 700; t++) all.push({ id: id++, problem_id: `abc${t % 5}_a`, result: t % 4 === 0 ? 'AC' : 'WA', epoch_second: t });
  all.push({ id: id++, problem_id: 'abc9_a', result: 'AC', epoch_second: 500 }, { id: id++, problem_id: 'abc9_a', result: 'WA', epoch_second: 500 });
  all.sort((x, y) => x.epoch_second - y.epoch_second || x.id - y.id);
  const fetchFrom = async (from) => all.filter((s) => s.epoch_second >= from).slice(0, c.ATCODER_PAGE);
  const a = await c.syncAtCoder({}, fetchFrom);
  const total = (st) => Object.values(st.problems).reduce((x, e) => x + e.tries, 0);
  assert.equal(total(a), all.length);
  assert.equal(a.lastEpoch, 700);
  const b = await c.syncAtCoder(a, fetchFrom);
  assert.equal(total(b), all.length);
  all.push({ id: id++, problem_id: 'abc1_a', result: 'AC', epoch_second: 700 }, { id: id++, problem_id: 'abc2_a', result: 'AC', epoch_second: 701 });
  const d = await c.syncAtCoder(b, fetchFrom);
  assert.equal(total(d), all.length);
  assert.equal(d.lastEpoch, 701);
  assert.equal(d.problems['abc9_a'].firstAc, 500);
});
