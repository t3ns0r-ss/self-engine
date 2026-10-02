// Tests for src/lib/validate.mjs with synthetic fixtures (ids like cf-9…A are not real problems
// and never enter the bank). Run with: npm test
import { test } from 'node:test';
import assert from 'node:assert/strict';
import { loadAll } from '../scripts/lib/load.mjs';
import { validateAll, laterKeywordHits, practiceByTier } from '../src/lib/validate.mjs';

const real = loadAll();
assert.deepEqual(real.errors, []);
const base = () => ({ curriculum: real.curriculum, patterns: structuredClone(real.patterns), banks: {}, notes: {} });

let n = 0;
const cf = (rating, extra) => {
  const id = `cf-9${String(++n).padStart(3, '0')}A`;
  return { id, source: 'codeforces', title: `Fixture ${id}`, url: `https://codeforces.com/problemset/problem/9${String(n).padStart(3, '0')}/A`,
    difficulty: String(rating), tier_basis: 'rating', set: 'practice', reserved_for: null, lookalike_of: null,
    techniques: ['1.3'], checked_on: '2026-10-02', ...extra };
};
const cses = (extra) => {
  const id = `cses-9${String(++n).padStart(3, '0')}`;
  return { id, source: 'cses', title: `Fixture ${id}`, url: `https://cses.fi/problemset/task/9${String(n).padStart(3, '0')}`,
    difficulty: '—', tier_basis: 'judgement', set: 'practice', reserved_for: null, lookalike_of: null,
    techniques: ['1.3'], checked_on: '2026-10-02', ...extra };
};
const RATING = { 1: 800, 2: 900, 3: 1200, 4: 1500, 5: 1700 };

/** A complete, valid bank for topic 1.3 (phase 1, band 1000–1400). */
function completeBank() {
  const pats = real.patterns['1.3'].patterns.map((p) => p.id);
  const problems = [];
  for (const pat of pats)
    for (const tier of [1, 2, 3, 4, 5])
      problems.push(tier <= 2 ? cses({ tier, pattern: pat }) : cf(RATING[tier], { tier, pattern: pat }));
  const res = (purpose, tier, k, extra = {}) => {
    for (let i = 0; i < k; i++)
      problems.push(cf(RATING[tier], { tier, pattern: pats[i % pats.length], set: 'reserved', reserved_for: purpose, ...extra }));
  };
  res('drill', 3, 8);
  res('later_drill', 2, 4, { techniques: ['1.2'] });
  res('checkpoint', 3, 3);
  res('review', 3, 6);
  res('review', 4, 4);
  res('exam', 4, 2);
  const la = [cf(1200, { tier: 3 }), cf(1200, { tier: 3, techniques: ['1.2'] }), cf(1300, { tier: 3 }), cf(1300, { tier: 3, techniques: ['1.2'] })];
  la.forEach((p, i) => Object.assign(p, { pattern: pats[0], set: 'reserved', reserved_for: 'lookalike', lookalike_of: la[i ^ 1].id }));
  problems.push(...la);
  return { topic: '1.3', status: 'complete', problems };
}
const notesFor = (bank) => bank.problems.map((p) => `## ${p.id} ${p.title} (tier ${p.tier})\n- Idea: …\n`).join('\n');

function run(mutate) {
  const d = base();
  const bank = completeBank();
  d.banks['1.3'] = bank;
  d.notes['1.3'] = notesFor(bank);
  mutate?.(d, bank);
  return validateAll(d);
}
const expectError = (errors, re) => assert.ok(errors.some((e) => re.test(e)), `expected an error matching ${re}, got:\n${errors.join('\n')}`);

test('the committed data is valid', () => assert.deepEqual(validateAll(real), []));
test('a complete fixture bank passes', () => assert.deepEqual(run(), []));

test('unknown pattern', () => expectError(run((d, b) => { b.problems[0].pattern = 'nope'; }), /pattern "nope" is not in/));
test('duplicate id across topics', () =>
  expectError(run((d, b) => { d.banks['1.4'] = { topic: '1.4', status: 'in_progress', problems: [{ ...b.problems[0], pattern: 'sorted-search', techniques: ['1.4'] }] }; d.notes['1.4'] = notesFor(d.banks['1.4']); }), /already appears in topic/));
test('URL must match the id', () => expectError(run((d, b) => { b.problems.find((p) => p.source === 'codeforces').url = 'https://codeforces.com/problemset/problem/1/A'; }), /does not match the codeforces URL format/));
test('bad id format', () => expectError(run((d, b) => { b.problems.find((p) => p.source === 'codeforces').id = 'cf-12a'; }), /id does not match/));
test('LeetCode difficulty words', () => {
  const errs = run((d, b) => { Object.assign(b.problems[0], { id: 'lc-two-sum', source: 'leetcode', url: 'https://leetcode.com/problems/two-sum/', difficulty: 'easy' }); d.notes['1.3'] = notesFor(b); });
  expectError(errs, /difficulty "easy" is not valid/);
});
test('AtCoder URL shape', () => {
  const ok = run((d, b) => { Object.assign(b.problems[0], { id: 'ac-abc999_c', source: 'atcoder', url: 'https://atcoder.jp/contests/abc999/tasks/abc999_c', difficulty: '500', tier_basis: 'contest_letter' }); d.notes['1.3'] = notesFor(b); });
  assert.deepEqual(ok, []);
  expectError(run((d, b) => { Object.assign(b.problems[0], { id: 'ac-abc999_c', source: 'atcoder', url: 'https://atcoder.jp/contests/abc999/tasks/abc999_d', difficulty: '500', tier_basis: 'contest_letter' }); d.notes['1.3'] = notesFor(b); }), /atcoder URL format/);
});
test('tier_basis must fit the platform', () => expectError(run((d, b) => { b.problems[0].tier_basis = 'rating'; }), /tier_basis rating not allowed for cses/));
test('later technique is rejected', () => expectError(run((d, b) => { b.problems[3].techniques = ['1.3', '1.4']; }), /technique 1.4 is later than topic 1.3/));
test('own topic must be among techniques', () => expectError(run((d, b) => { b.problems[3].techniques = ['1.2']; }), /techniques must include 1.3/));
test('later_drill may use only an earlier topic', () => assert.deepEqual(run((d, b) => { b.problems.find((p) => p.reserved_for === 'later_drill').techniques = ['0.6']; }), []));
test('lookalike_of must be mutual', () => expectError(run((d, b) => { b.problems.find((p) => p.lookalike_of).lookalike_of = b.problems[0].id; }), /does not point back/));
test('Codeforces tier must match rating', () => expectError(run((d, b) => { b.problems.find((p) => p.tier === 3 && p.set === 'practice').difficulty = '1900'; }), /rating 1900 is outside tier 3 \(1000–1400\)/));
test('reserved purpose tier range', () => expectError(run((d, b) => { const p = b.problems.find((q) => q.reserved_for === 'checkpoint'); p.tier = 2; p.difficulty = '900'; }), /checkpoint needs tier 3–4/));
test('every problem needs a note', () => expectError(run((d, b) => { d.notes['1.3'] = d.notes['1.3'].replace(`## ${b.problems[7].id} `, '## '); }), /no "## cf-\d+A …" section/));
test('missing notes file', () => expectError(run((d) => { d.notes['1.3'] = null; }), /notes\/bank\/1.3.md: missing/));
test('practice minimum', () => expectError(run((d, b) => { b.problems = b.problems.filter((p, i) => !(p.set === 'practice' && i < 6)); }), /practice set has 19/));
test('pattern spread over tiers', () => expectError(run((d, b) => { for (const p of b.problems) if (p.set === 'practice' && p.pattern === 'merge-walk' && p.tier >= 3) p.set = 'drop'; b.problems = b.problems.filter((p) => p.set !== 'drop'); }), /pattern merge-walk: 2 practice problems over 2 tiers/));
test('platform share at most 60%', () => expectError(run((d, b) => { b.problems = b.problems.filter((p) => !(p.source === 'cses' && p.tier === 2)); }), /% codeforces; at most 60%/));
test('reserved allocation', () => expectError(run((d, b) => { b.problems = b.problems.filter((p) => p.reserved_for !== 'exam'); }), /reserved_for exam: 0 problems/));
test('patterns covered by checkpoint or review', () => expectError(run((d, b) => { for (const p of b.problems) if ((p.reserved_for === 'review' || p.reserved_for === 'checkpoint') && p.pattern === 'merge-walk') p.pattern = 'fixed-window'; }), /pattern merge-walk appears in no checkpoint/));
test('in_progress topics skip count rules but not per-problem rules', () => {
  assert.deepEqual(run((d, b) => { b.status = 'in_progress'; b.problems = b.problems.slice(0, 3); }), []);
  expectError(run((d, b) => { b.status = 'in_progress'; b.problems[0].pattern = 'nope'; }), /nope/);
});
test('keyword scan finds later-topic words only', () => {
  assert.deepEqual(laterKeywordHits('use a sliding window', 9, real.curriculum), []);
  assert.match(laterKeywordHits('then binary search the answer', 9, real.curriculum).join(), /binary search/);
  assert.deepEqual(laterKeywordHits('minimum of the window', 1, real.curriculum), [], '"nim" must not match inside "minimum"');
});
test('pattern files reject later-topic keywords', () => {
  const d = base();
  d.patterns['1.1'].patterns[0].description += ' Then use two pointers.';
  expectError(validateAll(d), /pattern sort-then-scan uses later-topic keywords: "two pointers" \(topic 1.3\)/);
});
test('7.8 patterns name another topic', () => {
  const d = base();
  const p = cf(2200, { tier: 3, pattern: '1.3:count-windows', set: 'reserved', reserved_for: 'exam', techniques: ['1.3'] });
  d.banks['7.8'] = { topic: '7.8', status: 'in_progress', problems: [p] };
  d.notes['7.8'] = notesFor(d.banks['7.8']);
  assert.deepEqual(validateAll(d), []);
  p.pattern = '1.3:nope';
  expectError(validateAll(d), /pattern 1.3:nope does not exist/);
});
test('practiceByTier orders by pattern, then difficulty, then id', () => {
  const b = completeBank();
  const tiers = practiceByTier(b, real.patterns['1.3']);
  assert.equal(tiers.length, 5);
  assert.deepEqual(tiers.map((t) => t.problems.length), [5, 5, 5, 5, 5]);
  assert.deepEqual(tiers[2].problems.map((p) => p.pattern), real.patterns['1.3'].patterns.map((p) => p.id));
});
