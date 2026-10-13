import test from 'node:test';
import assert from 'node:assert/strict';
import { shouldSync, OPEN_AGE_S, RETURN_GAP_S } from '../src/lib/sync/scheduler.ts';

test('shouldSync: page open needs a 15-minute-old sync; tab return at most once a minute', () => {
  const now = 10_000;
  assert.equal(shouldSync(null, undefined, now, OPEN_AGE_S), true);
  assert.equal(shouldSync(now - 14 * 60, undefined, now, OPEN_AGE_S), false);
  assert.equal(shouldSync(now - 16 * 60, undefined, now, OPEN_AGE_S), true);
  assert.equal(shouldSync(now - 120, undefined, now, RETURN_GAP_S), true);
  assert.equal(shouldSync(now - 120, now - 30, now, RETURN_GAP_S), false); // tried 30 s ago
  assert.equal(shouldSync(now - 20, undefined, now, RETURN_GAP_S), false);
});
