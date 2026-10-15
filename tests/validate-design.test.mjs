import { test } from 'node:test';
import assert from 'node:assert/strict';
import { validateDesignCurriculum, keywordCollisions } from '../src/lib/validate-design.mjs';

const row = (o) => ({ track: 'lld', order: 1, id: 'L0.1', phase: 'L0', slug: 'a', kind: 'standard', title: 'T', requires: [], keywords: ['alpha'], ...o });
const good = () => [
  row({}),
  row({ order: 2, id: 'L0.2', slug: 'b', requires: ['L0.1'], keywords: ['beta'] }),
  row({ order: 3, id: 'L0.3', slug: 'c', kind: 'capstone', requires: ['L0.1', 'L0.2'], keywords: [] }),
];
const has = (errs, re) => assert.ok(errs.some((e) => re.test(e)), errs.join('\n'));

test('a valid track passes', () => assert.deepEqual(validateDesignCurriculum(good()), []));
test('order must be 1..n in listed order', () => { const g = good(); g[1].order = 5; has(validateDesignCurriculum(g), /L0\.2 has order 5/); });
test('requires must exist in the same track (no cross-track)', () => {
  const g = [...good(), row({ track: 'hld', order: 1, id: 'H0.1', phase: 'H0', slug: 'h', requires: [], keywords: ['k'] }),
    row({ track: 'hld', order: 2, id: 'H0.2', phase: 'H0', slug: 'h2', kind: 'capstone', requires: ['H0.1', 'L0.1'], keywords: [] })];
  has(validateDesignCurriculum(g), /H0\.2 requires L0\.1, which is not a topic of track hld/);
});
test('requires must be earlier', () => { const g = good(); g[1].requires = ['L0.3']; has(validateDesignCurriculum(g), /L0\.2 requires L0\.3, which is not earlier/); });
test('first topic has empty requires', () => { const g = good(); g[0].requires = ['L0.2']; has(validateDesignCurriculum(g), /first topic of a track/); });
test('id prefix and phase must match the track', () => { const g = good(); g[0].id = 'H0.1'; has(validateDesignCurriculum(g), /does not start with L/); g[1].phase = 'L1'; has(validateDesignCurriculum(g), /L0\.2 has phase L1/); });
test('HLD topics cannot be measured or light', () => {
  const g = [row({ track: 'hld', id: 'H0.1', phase: 'H0', kind: 'measured' }), row({ track: 'hld', order: 2, id: 'H0.2', phase: 'H0', slug: 'z', kind: 'capstone', requires: ['H0.1'], keywords: [] })];
  has(validateDesignCurriculum(g), /HLD topics are standard or capstone/);
});
test('capstone must be last, require everything earlier, and have no keywords', () => {
  const g = good(); g[2].requires = ['L0.1']; g[2].keywords = ['x']; has(validateDesignCurriculum(g), /missing L0\.2/); has(validateDesignCurriculum(g), /no keywords of its own/);
  const h = good(); h[1].kind = 'capstone'; has(validateDesignCurriculum(h), /only the last topic/);
});
test('keyword inside an earlier topic keyword is a collision', () => {
  const g = good(); g[1].keywords = ['alp']; has(keywordCollisions(g), /"alp" appears inside keyword "alpha" of earlier topic L0\.1/);
});
test('keyword inside a template heading is a collision', () => {
  const g = good(); g[1].keywords = ['checkpoint']; has(keywordCollisions(g), /template heading "Checkpoint"/);
});
test('the reverse (earlier keyword inside a later one) is allowed', () => {
  const g = good(); g[1].keywords = ['alpha beta']; assert.deepEqual(keywordCollisions(g), []);
});
