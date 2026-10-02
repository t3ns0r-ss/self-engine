// Tests for src/lib/validate-topics.mjs on the placeholder topic (created and removed here).
import { test, before, after } from 'node:test';
import assert from 'node:assert/strict';
import { execFileSync } from 'node:child_process';
import { loadAll } from '../scripts/lib/load.mjs';
import { validateTopics, headingsOf, textForKeywordScan } from '../src/lib/validate-topics.mjs';

let base;
before(() => {
  execFileSync('node', ['tests/placeholder/make.mjs']);
  base = loadAll();
  assert.deepEqual(base.errors, []);
});
after(() => execFileSync('node', ['tests/placeholder/make.mjs', '--remove']));

const run = (mutate) => {
  const d = structuredClone(base);
  mutate?.(d, d.topics['1.3']);
  return validateTopics(d);
};
const expectError = (errors, re) => assert.ok(errors.some((e) => re.test(e)), `expected ${re}, got:\n${errors.join('\n')}`);

test('placeholder topic is valid', () => assert.deepEqual(run(), []));
test('problem must exist in the bank', () => expectError(run((d, t) => { t.problems[0].id = 'cf-1A'; }), /cf-1A is not in the problem bank/));
test('ladder must come from practice', () => expectError(run((d, t) => { const r = t.problems.find((p) => p.role === 'review'); Object.assign(t.problems[0], { id: r.id }); t.problems.splice(t.problems.indexOf(r), 1); }), /role ladder must come from the practice set/));
test('ladder card must belong to the topic', () => expectError(run((d, t) => { t.problems[0].card = 'nope'; }), /card nope is not a card of topic 1.3/));
test('at least 3 ladder problems per card', () => expectError(run((d, t) => { t.problems = t.problems.filter((p) => !(p.role === 'ladder' && p.card === 'fixed-window' && p.rung === 4)); t.problems.find((p) => p.role === 'ladder' && p.card === 'fixed-window' && p.rung === 3).rung = 3; t.problems = t.problems.filter((p) => !(p.role === 'ladder' && p.card === 'fixed-window' && p.rung === 3)); }), /card fixed-window has 2 ladder problems/));
test('rungs without gaps', () => expectError(run((d, t) => { t.problems.find((p) => p.rung === 2).rung = 5; }), /rungs must be 1\.\.4 without gaps/));
test('difficulty non-decreasing along rungs', () => expectError(run((d, t) => {
  const r2 = t.problems.find((p) => p.card === 'shrinkable-window' && p.rung === 3);
  d.banks['1.3'].problems.find((p) => p.id === r2.id).difficulty = '900';
  d.banks['1.3'].problems.find((p) => p.id === r2.id).tier = 2;
}), /is easier than earlier rung/));
test('drill needs 3 earlier-topic answers', () => expectError(run((d, t) => { t.drill.forEach((x) => { x.answer_topic = '1.3'; x.answer_card = 'shrinkable-window'; }); }), /0 earlier-topic answers/));
test('drill answer must be a known card or pattern', () => expectError(run((d, t) => { t.drill[0].answer_card = 'nope'; }), /nope is not a card or pattern of topic 1.3/));
test('drill answer cannot be a later topic', () => expectError(run((d, t) => { t.drill[0].answer_topic = '1.4'; t.drill[0].answer_card = 'answer-search'; }), /answer_topic 1.4 must be this or an earlier topic/));
test('checkpoint time limit by phase', () => expectError(run((d, t) => { t.checkpoint.time_limit_minutes = 120; }), /must be 90 minutes for phase 1/));
test('checkpoint lists checkpoint problems', () => expectError(run((d, t) => { t.checkpoint.problems[0] = t.problems[0].id; }), /not a problem with role checkpoint/));
test('review sets of 3–4', () => expectError(run((d, t) => { t.problems.find((p) => p.review_set === 2).review_set = 1; }), /review set 2 has 2 problems/));
test('glossary term must exist with the topic', () => {
  expectError(run((d, t) => { t.glossary_added.push('pointer'); }), /"pointer" is not in glossary.yaml/);
  expectError(run((d) => { d.glossary[0].topic = '1.2'; }), /has topic 1.2 in glossary.yaml/);
});
test('decision map choices', () => expectError(run((d, t) => { t.decision_map[0].choose = 'prefix-count-lookup'; }), /not a card of 1.3/));
test('lesson headings in order', () => expectError(run((d) => { d.lessons['1.3'].text = d.lessons['1.3'].text.replace('## 7. Bug catalogue', '## 7. Bugs'); }), /missing or out-of-order heading "## 7. Bug catalogue"/));
test('worked example steps', () => expectError(run((d) => { d.lessons['1.3'].text = d.lessons['1.3'].text.replace('#### Step 4: Proof for this problem\n', ''); }), /Example 1 must have exactly the six step headings/));
test('later keywords allowed only in the "does not cover" subsection', () => {
  assert.deepEqual(run(), [], 'the placeholder mentions binary search only in that subsection');
  expectError(run((d) => { d.lessons['1.3'].text = d.lessons['1.3'].text.replace('A **window** is', 'Use binary search. A **window** is'); }), /later-topic keywords .*"binary search" \(topic 1.4\)/);
});
test('headingsOf ignores fenced code', () => assert.deepEqual(headingsOf('## A\n```\n## not\n```\n### B'), ['## A', '### B']));
test('keyword scan skips frontmatter and imports', () => assert.equal(textForKeywordScan('---\ntitle: x\n---\nimport a from "b";\nhello').trim(), 'hello'));
