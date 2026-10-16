import { test } from 'node:test';
import assert from 'node:assert/strict';
import { mkdtempSync, mkdirSync, writeFileSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { validateDesignFiles, validateCodeHygiene, validateDesignLesson, DESIGN_HEADINGS, realFs } from '../src/lib/validate-design-files.mjs';
import { designTopicFile, designExerciseFile } from '../src/lib/schemas.mjs';

const has = (errs, re) => assert.ok(errs.some((e) => re.test(e)), errs.join('\n') || '(no errors)');
const put = (root, p, s) => { mkdirSync(join(root, p, '..'), { recursive: true }); writeFileSync(join(root, p), s); };

const rows = [
  { track: 'hld', order: 1, id: 'H0.1', phase: 'H0', slug: 'a', kind: 'standard', title: 'A', requires: [], lab: 'Build a', infra: [], keywords: ['alpha'] },
  { track: 'hld', order: 2, id: 'H0.2', phase: 'H0', slug: 'b', kind: 'standard', title: 'B', requires: ['H0.1'], lab: 'Build b', infra: [], keywords: ['beta'] },
];
const card = (id, o = {}) => ({
  id, name: id, need: 'n', decisive_property: 'p', from_claim: 'H0.1.1', how_to_test: 't', constraint_shapes: ['s'],
  weak_signals: [{ form: 'f', shape: 's' }, { form: 'f2', shape: 's2' }], kill_signals: ['at 5 requests a day it is overkill', 'x'],
  in_action: { statement: 's', constraints: 'c', budget: 'b', candidates: [{ tool: 'a', verdict: 'rejected', because: 'x' }, { tool: 'b', verdict: 'chosen', because: 'y' }], property_check: 'p', decision: 'd' },
  examples: { positive: [{ inline: { input: 'i', answer: 'a', why: 'w' } }, { inline: { input: 'i', answer: 'a', why: 'w' } }], negative: [{ inline: { input: 'i', answer: 'a', why: 'w' }, correct_tool: { simplest: 'x' } }, { inline: { input: 'i', answer: 'a', why: 'w' }, correct_tool: { simplest: 'y' } }] },
  lookalikes: [], cost: 'c', lab: { unit: 'H0.1/lab-a', holds_test: 'TestHolds', breaks_test: 'TestBreaks' }, ...o,
});
function world() {
  const root = mkdtempSync(join(tmpdir(), 'dv-'));
  put(root, 'code/H0.1/claim-1/main.go', 'package main\n');
  put(root, 'code/H0.1/claim-1/expected.txt', 'x = 1 items\n');
  put(root, 'code/H0.1/lab-a/run.md', 'run\n');
  put(root, 'code/H0.1/lab-a/a_test.go', 'package a\nfunc TestHolds(t *testing.T) {}\nfunc TestBreaks(t *testing.T) {}\n');
  put(root, 'exercises/H0.1/lab/rung-1/test.sh', 'true\n');
  put(root, 'reference/H0.1/lab/rung-1/a.go', 'package a\n');
  const topics = {
    'H0.1': designTopicFile.parse({
      id: 'H0.1', track: 'hld', uses: [], claims: [{ id: 'H0.1.1', kind: 'computed', title: 't', plain_words: 'p', evidence: ['H0.1/claim-1'], source: null }],
      cards: [card('c1')], lookalike_pairs: [], self_test: [], decision_map: [], glossary_added: [],
    }),
  };
  const ex = (o) => ({ id: 'rung-1', role: 'ladder', type: 'lab', title: 't', prompt: 'p', card: 'c1', rung: 1, new_force: 'f', needs_new_structure: false,
    clarifying: [1, 2, 3, 4].map((i) => ({ q: `q${i}`, a: 'a', critical: i < 3 })), checkers: [{ kind: 'kit', path: 'H0.1/lab/rung-1' }], hints: ['a', 'b', 'c'], ...o });
  const exercises = { 'H0.1': designExerciseFile.parse({ topic: 'H0.1', exercises: [ex({})] }) };
  const d = {
    topics, exercises, rubrics: [{ id: 'rubric-hld-mock-v1' }], constants: [], units: {}, experiments: {},
    labs: { 'H0.1/lab-a': { title: 't', holds: ['TestHolds'], breaks: ['TestBreaks'], run: 'run.md', experiments: [], stacks: [] } },
  };
  return { root, d, ex };
}
const run = (w, o = {}) => validateDesignFiles(w.d, realFs(w.root), { rows, products: ['Kafka'], ...o });

test('a consistent small world has no errors', () => assert.deepEqual(run(world()), []));

test('cards: from_claim, lab tests, product names, kill signal numbers, look-alikes', () => {
  let w = world();
  w.d.topics['H0.1'].cards[0].from_claim = 'H0.1.9';
  has(run(w), /from_claim H0\.1\.9/);
  w = world(); w.d.topics['H0.1'].cards[0].lab.breaks_test = 'TestNope';
  has(run(w), /breaks_test TestNope is not in/);
  w = world(); w.d.topics['H0.1'].cards[0].need = 'use Kafka for it';
  has(run(w), /names the product "Kafka"/);
  w = world(); w.d.topics['H0.1'].cards[0].kill_signals = ['none', 'none either'];
  has(run(w), /kill signal needs numbers/);
  w = world(); w.d.topics['H0.1'].cards[0].lookalikes = [{ description: 'd', tool: { topic: 'H0.2', card: 'x' }, flipping_difference: 'f' }];
  has(run(w), /look-alike H0\.2\/x/);
});

test('claims: evidence must exist; measured needs two domains; experimented needs PASS results', () => {
  let w = world(); w.d.topics['H0.1'].claims[0].evidence = ['H0.1/nope'];
  has(run(w), /evidence unit code\/H0\.1\/nope does not exist/);
  w = world(); w.d.topics['H0.1'].claims[0].kind = 'measured';
  has(run(w), /pattern units from at least 2 domains/);
  w = world(); w.d.topics['H0.1'].claims[0].kind = 'experimented'; w.d.topics['H0.1'].claims[0].evidence = ['H0.1/sweep'];
  w.d.experiments['H0.1/sweep'] = { program: 'code/H0.1/lab-a/experiments/sweep', results_file: 'results/2026-10-21-labserver.txt' };
  has(run(w), /results file .* does not exist/);
  put(w.root, 'code/H0.1/lab-a/experiments/sweep/results/2026-10-21-labserver.txt', 'FAIL shape: p99\n');
  has(run(w), /every shape check as PASS/);
  put(w.root, 'code/H0.1/lab-a/experiments/sweep/results/2026-10-21-labserver.txt', 'PASS shape: p99\n');
  assert.deepEqual(run(w), []);
});

test('exercises: checker combinations, kits, ladders, clarifying questions, drill quotas', () => {
  let w = world(); w.d.exercises['H0.1'].exercises[0].checkers = [{ kind: 'rubric', id: 'rubric-hld-mock-v1' }];
  has(run(w), /checkers \[rubric\] are not allowed for hld lab/);
  w = world(); w.d.exercises['H0.1'].exercises[0].checkers[0].path = 'H0.1/lab/rung-9';
  has(run(w), /kit exercises\/H0\.1\/lab\/rung-9 does not exist/);
  w = world(); w.d.exercises['H0.1'].exercises[0].needs_new_structure = true;
  has(run(w), /needs_new_structure: false/);
  w = world(); w.d.exercises['H0.1'].exercises[0].hints = ['a'];
  has(run(w), /exactly 3 hints/);
  w = world(); w.d.exercises['H0.1'].exercises[0].clarifying = [{ q: 'q', a: 'a', critical: true }];
  has(run(w), /clarifying needs at least 4/);
  w = world();
  const dr = (i, answer) => designExerciseFile.parse({ topic: 'H0.1', exercises: [{ id: `r-${i}`, role: 'drill', type: 'recognise', title: 't', prompt: 'p', answer, checkers: [] }] }).exercises[0];
  const own = { kind: 'card', card: { topic: 'H0.1', card: 'c1' }, property: 'p', why_others_fail: 'w' };
  w.d.exercises['H0.1'].exercises.push(...[1, 2, 3, 4, 5, 6].map((i) => dr(i, own)));
  has(run(w), /drill has 0 "none" items of 6; at least 20%/);
  w.d.exercises['H0.1'].exercises.push(dr(7, { kind: 'none', simplest: 's', why: 'w' }), dr(8, { kind: 'none', simplest: 's', why: 'w' }));
  assert.deepEqual(run(w), []);
});

test('numeric checkers need a calc program that prints the key', () => {
  const w = world();
  w.d.exercises['H0.1'].exercises.push(designExerciseFile.parse({ topic: 'H0.1', exercises: [{ id: 'est-1', role: 'drill', type: 'estimate', title: 't', prompt: 'p', checkers: [{ kind: 'numeric', calc: 'H0.1/claim-1', key: 'x', unit: 'items' }] }] }).exercises[0]);
  assert.deepEqual(run(w), []);
  w.d.exercises['H0.1'].exercises.at(-1).checkers[0].key = 'y';
  has(run(w), /does not print key y/);
});

test('D18: TODO markers and unfilled templates are rejected', () => {
  const w = world();
  put(w.root, 'reference/H0.1/lab/rung-1/SOLUTION.md', 'TODO write this\n');
  has(run(w), /contains TODO/);
});

test('D16/D17: folder names, sanitizer files and direct compiler flags', () => {
  const root = mkdtempSync(join(tmpdir(), 'dh-'));
  put(root, 'code/_shared/x_test.go', 'package x\n');
  put(root, 'code/L2.1/u/sanitizer', 'thread\n');
  put(root, 'code/L6.1/u/sanitizer', 'thread\n');
  put(root, 'code/L2.1/u/test.sh', 'g++ -std=c++23 a.cpp\n');
  put(root, 'code/L2.2/u/test.sh', 'g++ $(bash cxxflags.sh .) a.cpp\n');
  const errs = validateCodeHygiene(realFs(root));
  has(errs, /code\/_shared: folder name starts with _/);
  has(errs, /code\/L2\.1\/u\/sanitizer.*only for L6/);
  has(errs, /code\/L2\.1\/u\/test\.sh.*cxxflags\.sh/);
  assert.equal(errs.some((e) => /L6\.1/.test(e) || /L2\.2/.test(e)), false);
});

test('D13/D8: lesson headings must match Section 8; long quotes are rejected', () => {
  const ok = DESIGN_HEADINGS.join('\ntext\n') + '\ntext\n';
  assert.deepEqual(validateDesignLesson(ok, 'x.mdx'), []);
  assert.deepEqual(validateDesignLesson(ok + '## See also\nlinks\n', 'x.mdx'), []);
  has(validateDesignLesson(ok.replace('## 9. Exercise ladder', '## 9. Ladder'), 'x.mdx'), /headings differ/);
  has(validateDesignLesson(ok + '## See also\nl\n## Extra\n', 'x.mdx'), /See also.*last/);
  has(validateDesignLesson(ok + '> ' + 'word '.repeat(16) + '\n', 'x.mdx'), /longer than 15 words/);
});
