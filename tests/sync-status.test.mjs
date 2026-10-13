// Every row of the PROFILE_SYNC_PLAN.md Section 9 table, through computeStatus.
import test from 'node:test';
import assert from 'node:assert/strict';
import { computeStatus } from '../src/lib/sync/status.ts';

const ac = { firstAc: 5, lastAc: 5, acs: [5], tries: 2, last: 5, acTimeKnown: true };
const wa = { firstAc: null, lastAc: null, acs: [], tries: 1, last: 4, acTimeKnown: true };
const cf = (problems) => ({ cf: { problems, highWater: 1 } });
const profiles = { codeforces: { handle: 'h', addedAt: 1, lastSyncAt: 99 } };

test('manual solved wins; flag only when linked and no accepted submission', () => {
  for (const s of ['solved', 'solved_hints', 'editorial']) {
    const v = computeStatus('cf-1A', { status: s, hintsOpened: 0 }, cf({ '1A': ac }), profiles);
    assert.equal(v.status, s); assert.equal(v.source, 'manual'); assert.equal(v.flag, null);
  }
  assert.equal(computeStatus('cf-1A', { status: 'solved', hintsOpened: 0 }, cf({ '1A': wa }), profiles).flag, 'no-ac-on-platform');
  assert.equal(computeStatus('cf-1A', { status: 'solved', hintsOpened: 0 }, cf({}), profiles).flag, 'no-ac-on-platform'); // linked, never submitted
  assert.equal(computeStatus('cf-1A', { status: 'solved', hintsOpened: 0 }, {}, {}).flag, null); // not linked
});

test('attempted or none + accepted -> Solved (or with hints), source sync', () => {
  let v = computeStatus('cf-1A', { status: 'attempted', hintsOpened: 0 }, cf({ '1A': ac }), profiles);
  assert.deepEqual([v.status, v.source, v.platform, v.syncedAt], ['solved', 'sync', 'cf', 99]);
  v = computeStatus('cf-1A', { status: 'attempted', hintsOpened: 2 }, cf({ '1A': ac }), profiles);
  assert.equal(v.status, 'solved_hints');
  v = computeStatus('cf-1A', undefined, cf({ '1A': ac }), profiles);
  assert.equal(v.status, 'solved');
  v = computeStatus('cf-1A', { hintsOpened: 1 }, cf({ '1A': ac }), profiles); // hint opened on the site, no manual status
  assert.equal(v.status, 'solved_hints');
});

test('attempted rows', () => {
  assert.deepEqual(computeStatus('cf-1A', { status: 'attempted', hintsOpened: 0 }, cf({ '1A': wa }), profiles).source, 'manual');
  assert.deepEqual(computeStatus('cf-1A', { status: 'attempted', hintsOpened: 0 }, {}, {}).source, 'manual');
  const v = computeStatus('cf-1A', undefined, cf({ '1A': wa }), profiles);
  assert.deepEqual([v.status, v.source], ['attempted', 'sync']);
});

test('none rows', () => {
  assert.equal(computeStatus('cf-1A', undefined, cf({}), profiles).status, null);
  assert.equal(computeStatus('cf-1A', undefined, {}, {}).status, null);
  assert.equal(computeStatus('cses-1640', undefined, cf({}), profiles).status, null);
});

test('aliases and removing a handle', () => {
  const caches = cf({ '2B': ac });
  assert.equal(computeStatus('cf-1A', undefined, caches, profiles, { '1A': ['2B'] }).status, 'solved');
  // handle removed: cache gone, hand-set status stays and nothing else shows
  assert.equal(computeStatus('cf-1A', undefined, {}, {}, { '1A': ['2B'] }).status, null);
  assert.equal(computeStatus('cf-1A', { status: 'editorial', hintsOpened: 0 }, {}, {}).status, 'editorial');
});

test('computeStatus never mutates its inputs', () => {
  const local = { status: 'attempted', hintsOpened: 0 };
  const caches = cf({ '1A': ac });
  const before = JSON.stringify([local, caches]);
  computeStatus('cf-1A', local, caches, profiles);
  assert.equal(JSON.stringify([local, caches]), before);
});
