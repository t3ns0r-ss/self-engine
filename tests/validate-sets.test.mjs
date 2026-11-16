// Tests for src/lib/validate-sets.mjs and the set schemas (CURRICULUM_GAPS_PLAN.md Section 6, items 2 and 3).
import test from 'node:test';
import assert from 'node:assert/strict';
import { loadAll } from '../scripts/lib/load.mjs';
import { validateSets } from '../src/lib/validate-sets.mjs';
import { volumeSetFile, bridgeSetFile } from '../src/lib/schemas.mjs';

const real = loadAll();
const base = { curriculum: real.curriculum, banks: real.banks, topics: real.topics };
const run = (sets) => validateSets({ ...base, sets: { ...real.sets, ...sets } });
const withVol = (f) => run({ 'volume-0': { ...real.sets['volume-0'], problems: real.sets['volume-0'].problems.map(f) } });
const withBri = (f) => run({ 'bridge-4-5': { ...real.sets['bridge-4-5'], problems: real.sets['bridge-4-5'].problems.map(f) } });

test('the real sets pass', () => {
  assert.deepEqual(run({}), []);
  assert.equal(real.sets['volume-0'].problems.length, 40);
  assert.ok(real.sets['bridge-4-5'].problems.length >= 10 && real.sets['bridge-4-5'].problems.length <= 15);
});
test('a problem that is also in a bank fails', () => {
  const someBankId = real.banks['0.1'].problems[0];
  const errs = withVol((p, i) => (i === 0 ? { ...p, id: someBankId.id, source: someBankId.source, url: someBankId.url } : p));
  assert.match(errs.join('\n'), /already in the bank of topic 0\.1/);
});
test('a reserved exam problem cannot be reused in a set', () => {
  const exam = Object.entries(real.banks).flatMap(([t, b]) => b.problems.filter((p) => p.reserved_for === 'exam').map((p) => ({ t, p })))[0];
  const errs = withBri((p, i) => (i === 0 ? { ...p, id: exam.p.id, source: exam.p.source, url: exam.p.url } : p));
  assert.match(errs.join('\n'), /may not duplicate a bank or exam problem/);
});
test('a problem in both sets fails', () => {
  const v = real.sets['volume-0'].problems[0];
  const errs = withBri((p, i) => (i === 0 ? { ...p, id: v.id, source: v.source, url: v.url } : p));
  assert.match(errs.join('\n'), /already appears in src\/data\/sets\/volume-0\.yaml/);
});
test('a duplicate inside a set fails', () => {
  const first = real.sets['volume-0'].problems[0];
  const errs = withVol((p, i) => (i === 1 ? { ...p, id: first.id, source: first.source, url: first.url } : p));
  assert.match(errs.join('\n'), /already appears/);
});
test('volume: rating outside 800 to 1000, a wrong url, a Phase 2 topic and a later keyword fail', () => {
  const cf = real.sets['volume-0'].problems.findIndex((p) => p.source === 'codeforces');
  assert.match(withVol((p, i) => (i === cf ? { ...p, difficulty: '1400' } : p)).join('\n'), /outside the volume band/);
  assert.match(withVol((p, i) => (i === cf ? { ...p, url: 'https://codeforces.com/problemset/problem/1/A' } : p)).join('\n'), /does not match the codeforces URL format/);
  assert.match(withVol((p, i) => (i === 0 ? { ...p, topic: '2.1' } : p)).join('\n'), /Phase 2/);
  assert.match(withVol((p, i) => (i === 0 ? { ...p, topic: '0.1', summary: 'Use a segment tree here.' } : p)).join('\n'), /later-topic keywords/);
});
test('volume: too few problems fail', () => {
  assert.match(run({ 'volume-0': { ...real.sets['volume-0'], problems: real.sets['volume-0'].problems.slice(0, 5) } }).join('\n'), /expected 20 to 60/);
});
test('bridge: count, band, unread statement, later topic and later keyword fail', () => {
  assert.match(run({ 'bridge-4-5': { ...real.sets['bridge-4-5'], problems: real.sets['bridge-4-5'].problems.slice(0, 4) } }).join('\n'), /expected 10 to 15/);
  assert.match(withBri((p, i) => (i === 0 ? { ...p, difficulty: '1200' } : p)).join('\n'), /outside the bridge band/);
  assert.match(withBri((p, i) => (i === 0 ? { ...p, source_check: 'api' } : p)).join('\n'), /source_check api is only for Codeforces/);
  assert.match(withBri((p, i) => (i === 0 ? { ...p, have_topics: ['5.2'] } : p)).join('\n'), /after Phase 4/);
  assert.match(withBri((p, i) => (i === 0 ? { ...p, new_idea: 'Count with a Fenwick tree over positions.' } : p)).join('\n'), /keywords of topics after Phase 4/);
  assert.match(withBri((p, i) => (i === 0 ? { ...p, new_idea: 'two\nlines' } : p)).join('\n'), /one line/);
});
test('schemas: a bridge problem needs have, have_topics and new_idea', () => {
  const p = real.sets['bridge-4-5'].problems[0];
  assert.equal(bridgeSetFile.safeParse({ ...real.sets['bridge-4-5'], problems: [p] }).success, true);
  const { new_idea: _n, ...noIdea } = p;
  assert.equal(bridgeSetFile.safeParse({ ...real.sets['bridge-4-5'], problems: [noIdea] }).success, false);
  const { topic: _t, ...noTopic } = real.sets['volume-0'].problems[0];
  assert.equal(volumeSetFile.safeParse({ ...real.sets['volume-0'], problems: [noTopic] }).success, false);
});
