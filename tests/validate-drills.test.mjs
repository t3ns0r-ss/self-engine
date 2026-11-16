// Tests for src/lib/validate-drills.mjs and the drills/read_solution schemas (CURRICULUM_GAPS_PLAN.md Section 6).
import test from 'node:test';
import assert from 'node:assert/strict';
import { loadAll } from '../scripts/lib/load.mjs';
import { validateDrills } from '../src/lib/validate-drills.mjs';
import { drillsFile, topicFile } from '../src/lib/schemas.mjs';

const real = loadAll();
const all = () => true;
const run = (over = {}) => validateDrills({ curriculum: real.curriculum, topics: real.topics, drills: real.drills, ...over }, all);

test('the real drills pass', () => {
  assert.deepEqual(run(), []);
  assert.ok(real.drills.length >= 8 && real.drills.length <= 12);
});
test('too few drills fail', () => {
  assert.match(run({ drills: real.drills.slice(0, 3) }).join('\n'), /expected 8 to 12/);
});
test('a drill in an unknown topic, or outside its topic folder, fails', () => {
  const bad = real.drills.map((d, i) => (i === 0 ? { ...d, topic: '9.9' } : d));
  assert.match(run({ drills: bad }).join('\n'), /unknown or draft topic 9.9/);
  const moved = real.drills.map((d, i) => (i === 0 ? { ...d, unit: '1.1/drill-x' } : d));
  assert.match(run({ drills: moved }).join('\n'), /must live under code/);
});
test('a missing unit file fails', () => {
  const errs = validateDrills({ curriculum: real.curriculum, topics: real.topics, drills: real.drills }, (f) => !f.endsWith('brute.cpp'));
  assert.match(errs.join('\n'), /missing code\/.*brute\.cpp/);
});
test('read_solution is rejected before Phase 3', () => {
  const topics = { ...real.topics, '1.1': { ...real.topics['1.1'], read_solution: { questions: ['a', 'b', 'c'] } } };
  assert.match(run({ topics }).join('\n'), /read_solution is for Phase 3 onwards/);
});
test('read_solution needs exactly three questions', () => {
  const tf = { ...real.topics['3.3'], read_solution: { questions: ['a', 'b'] } };
  assert.equal(topicFile.safeParse(tf).success, false);
  assert.equal(drillsFile.safeParse([{ id: 'x', title: 't', topic: '1.1', minutes: 9, unit: '1.1/drill-x', task: 't', check: ['a', 'b'], bug: 'b' }]).success, false);
});
