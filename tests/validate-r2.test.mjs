// Tests for the Revision 2 checks (src/lib/validate-r2.mjs) on the real topic 1.6, the reference topic.
import { test } from 'node:test';
import assert from 'node:assert/strict';
import { loadAll } from '../scripts/lib/load.mjs';
import { validateTopics } from '../src/lib/validate-topics.mjs';
import { theoremBlocks, parseCardUnit, topicMentions } from '../src/lib/validate-r2.mjs';

const base = loadAll();
assert.deepEqual(base.errors, []);
const run = (mutate, fsx) => {
  const d = structuredClone(base);
  d.topics = { ...d.topics };
  mutate?.(d, d.topics['1.6']);
  return validateTopics(d, fsx);
};
const expectError = (errors, re) => assert.ok(errors.some((e) => re.test(e)), `expected ${re}, got:\n${errors.join('\n')}`);
const lesson = (d, f) => { d.lessons['1.6'] = { ...d.lessons['1.6'], text: f(d.lessons['1.6'].text) }; };

test('topic 1.6 in the Revision 2 format is valid', () => assert.deepEqual(run(), []));

test('uses must contain every requires id', () => expectError(run((d, t) => { t.uses = t.uses.filter((u) => u.topic !== '0.6'); }), /uses is missing 0.6/));
test('uses must cover techniques of the topic problems', () => expectError(run((d, t) => { t.uses = t.uses.filter((u) => u.topic !== '1.4'); }), /uses is missing 1.4/));
test('uses must be earlier topics', () => expectError(run((d, t) => { t.uses.push({ topic: '1.7', what: 'x' }); }), /uses: 1.7 is not earlier than 1.6/));
test('uses must cover lesson links and theorem citations', () => expectError(run((d) => lesson(d, (s) => s.replace('(Theorem 0.2.4)', '(Theorem 2.1.1)'))), /uses is missing 2.1/));
test('"What you need" cannot be a hand-written list', () => expectError(run((d) => lesson(d, (s) => s.replace('<WhatYouNeed topic="1.6" />', '- [Topic 0.2](../../phase-0/0-2-complexity/): x'))), /must be rendered by <WhatYouNeed/));

test('every theorem needs plain words, a preconditions box and a demo', () => {
  expectError(run((d) => lesson(d, (s) => s.replace(':::tip[In plain words]', ':::tip[Plain]'))), /missing ":::tip\[In plain words\]"/);
  expectError(run((d) => lesson(d, (s) => s.replace('<TheoremDemo unit="1.6/thm-2" />', ''))), /Theorem 1.6.2: missing <TheoremDemo/);
  expectError(run((d, t) => { t.theorems = t.theorems.filter((e) => e.id !== '1.6.3'); }), /Theorem 1.6.3 has no entry under theorems/);
});
test('a proof has at most 8 numbered steps', () => expectError(run((d) => lesson(d, (s) => s.replace('**Proof.** The proof uses positions', '**Proof.** 9. extra\n1. a\n2. b\nThe proof uses positions'))), /proof has \d+ numbered steps; at most 8/));
test('the demo program is at most 30 lines and has an expected output', () => {
  const fsx = { exists: () => true, read: (p) => (p.endsWith('solution.cpp') ? 'x\n'.repeat(31) : '') };
  expectError(run(null, fsx), /demo solution.cpp has 31 lines; at most 30/);
  expectError(run(null, { exists: (p) => !p.includes('thm-1/tests'), read: (p) => (p.endsWith('solution.cpp') ? 'x\n' : '') }), /demo unit 1.6\/thm-1 has no tests\/1.out/);
});

test('inline example numbers must match the card example unit', () => {
  expectError(run((d, t) => { t.cards[1].examples.negative[0].inline.method_gives = '19'; }), /N1 method_gives "19" differs from printed method=9/);
  expectError(run((d, t) => { t.cards[1].examples.positive[0].inline.answer = '18'; }), /P1 answer "18" does not contain brute=17/);
});
test('a card needs one chosen candidate and inline examples', () => {
  expectError(run((d, t) => { t.cards[0].in_action.candidates.forEach((c) => { c.verdict = 'rejected'; }); }), /in_action needs exactly one chosen candidate/);
  expectError(run((d, t) => { t.cards[0].examples.negative = t.cards[0].examples.negative.map((n) => ({ problem: 'lc-daily-temperatures', why: 'x', correct_tool: n.correct_tool })); }), /needs an inline negative example/);
});

test('references must resolve and respect topic order', () => {
  expectError(run((d, t) => { t.cards[0].examples.negative[0].correct_tool = { topic: '1.7', card: 'xor-identities' }; }), /belongs to a later topic than 1.6/);
  expectError(run((d, t) => { t.lookalike_pairs[0].a_tool = { topic: '0.5', card: 'no-such-card' }; }), /no-such-card is not a card of topic 0.5/);
  expectError(run((d, t) => { t.lookalike_pairs[0].a_tool = 'brute force (0.5)'; }), /a_tool must be a \{topic, card\} reference/);
  expectError(run((d, t) => { t.drill[0].answer = { topic: '2.1', card: 'trial-division' }; }), /belongs to a later topic than 1.6/);
});
test('free text may not name a later topic or its keywords', () => {
  expectError(run((d, t) => { t.lookalike_pairs[0].flipping_difference += ' See topic 5.1.'; }), /later topic 5.1 named/);
  expectError(run((d, t) => { t.cards[0].kill_signals.push('Needs a segment tree'); }), /later-topic keywords .*segment tree/);
});
test('examples must not spoil later exercises', () => {
  expectError(run((d, t) => { t.cards[0].examples.positive[1] = { worked_example: 'lc-daily-temperatures', why: 'x' }; }), /positive example lc-daily-temperatures must be a worked example/);
  expectError(run((d, t) => { t.cards[0].examples.negative[1] = { problem: 'cses-1645', why: 'x', correct_tool: { topic: '0.5', card: 'nested-loops' } }; }), /negative example cses-1645 must be a worked example/);
});

test('helpers', () => {
  assert.deepEqual(parseCardUnit('P1 brute=3 method=3\nN1 brute=2,4 method=5,5\njunk'), { P1: { brute: '3', method: '3' }, N1: { brute: '2,4', method: '5,5' } });
  assert.deepEqual([...topicMentions('see topic 3.2 and (1.4) but 0.5 probability')].sort(), ['1.4', '3.2']);
  assert.equal(theoremBlocks('## A\n**Theorem 1.2.3 (x).** s\nmore\n\n### B\n**Theorem 1.2.4 (y).** t').length, 2);
});
