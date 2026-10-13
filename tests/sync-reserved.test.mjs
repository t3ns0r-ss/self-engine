import test from 'node:test';
import assert from 'node:assert/strict';
import { compromisedIn } from '../src/lib/sync/reserved.ts';
import { scaledPassRule } from '../src/lib/sync/core.ts';

const ac = (t) => ({ firstAc: t, lastAc: t, acs: [t], tries: 1, last: t, acTimeKnown: true });
const caches = { cf: { problems: { '1A': ac(100), '2B': ac(300), '3C': { firstAc: null, lastAc: null, acs: [], tries: 2, last: 5, acTimeKnown: true } } } };

test('compromised: accepted before shown, or accepted and never shown; not after; attempts alone never', () => {
  const ids = ['cf-1A', 'cf-2B', 'cf-3C', 'cf-9Z'];
  assert.deepEqual([...compromisedIn(ids, caches, {})].sort(), ['cf-1A', 'cf-2B']); // first display: any AC counts
  assert.deepEqual([...compromisedIn(ids, caches, { 'cf-1A': 200, 'cf-2B': 200 })], ['cf-1A']); // 2B accepted after shown
  assert.deepEqual([...compromisedIn(['cf-1A'], {}, {})], []); // no profile cache
});

test('scaled pass rules for checkpoints of 3 (k = 0..3) and exams', () => {
  assert.deepEqual([0, 1, 2, 3].map((k) => scaledPassRule(3, 2, k)), [{ need: 2, of: 3 }, { need: 2, of: 2 }, { need: 1, of: 1 }, null]);
  // exam of 8 needs ceil(0.6*8)=5; with 2 compromised: ceil(5*6/8)=4 of 6
  assert.deepEqual(scaledPassRule(8, 5, 2), { need: 4, of: 6 });
});
