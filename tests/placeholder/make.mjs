// Creates (or removes, with --remove) a placeholder topic that exercises every component
// (PLAN.md milestone M0). All problems are fake (ids cf-9xxxA, titles "Placeholder …") and
// must never stay in the repository: tests/e2e.sh creates them, builds, tests, and removes them.
import { writeFileSync, rmSync, mkdirSync, readFileSync, existsSync, cpSync, readdirSync } from 'node:fs';
import { parse, stringify } from 'yaml';

const FILES = [
  'src/data/bank/1-2.yaml',
  'src/data/bank/1-3.yaml',
  'notes/bank/1.2.md',
  'notes/bank/1.3.md',
  'src/data/topics/1-3.yaml',
  'src/content/docs/phase-1/1-3-two-pointers.mdx',
];
const CODE = 'code/0.0-placeholder';
const GLOSSARY = 'src/data/glossary.yaml';
const GLOSSARY_BACKUP = 'tests/placeholder/.glossary.backup';
// Real files at these paths (for example the real 1.2 and 1.3 banks) are moved aside while the
// placeholder exists and put back by --remove.
const BACKUP = 'tests/placeholder/.backup';
const backupOf = (f) => `${BACKUP}/${f.replaceAll('/', '__')}`;

// Present only while the placeholder exists. --remove does nothing without it, so a cleanup that
// runs before the placeholder was made can never delete the real files at these paths.
const ACTIVE = 'tests/placeholder/.active';

if (process.argv.includes('--remove')) {
  if (!existsSync(ACTIVE)) {
    console.log('no placeholder to remove');
    process.exit(0);
  }
  for (const f of FILES) {
    rmSync(f, { force: true });
    if (existsSync(backupOf(f))) cpSync(backupOf(f), f);
  }
  rmSync(BACKUP, { recursive: true, force: true });
  // Only remove the folder if the placeholder lesson was the only thing in it.
  if (existsSync('src/content/docs/phase-1') && readdirSync('src/content/docs/phase-1').length === 0) rmSync('src/content/docs/phase-1', { recursive: true });
  rmSync(CODE, { recursive: true, force: true });
  if (existsSync(GLOSSARY_BACKUP)) {
    writeFileSync(GLOSSARY, readFileSync(GLOSSARY_BACKUP, 'utf8'));
    rmSync(GLOSSARY_BACKUP);
  }
  rmSync(ACTIVE);
  console.log('placeholder removed');
  process.exit(0);
}

mkdirSync(BACKUP, { recursive: true });
writeFileSync(ACTIVE, 'placeholder topic is present\n');
for (const f of FILES) if (existsSync(f) && !existsSync(backupOf(f))) cpSync(f, backupOf(f));

let n = 0;
const prob = (rating, tier, extra) => {
  const c = 9000 + ++n;
  return {
    id: `cf-${c}A`, source: 'codeforces', title: `Placeholder Problem ${n}`, url: `https://codeforces.com/problemset/problem/${c}/A`,
    difficulty: String(rating), tier, tier_basis: 'rating', pattern: 'shrinkable-window', set: 'practice', reserved_for: null,
    lookalike_of: null, techniques: ['1.3'], checked_on: '2026-10-02', ...extra,
  };
};
const cards = ['shrinkable-window', 'fixed-window', 'count-windows'];
const bank13 = [];
const topicProblems = [];
// Ladder: 4 per card, ratings rising.
for (const card of cards)
  for (let r = 1; r <= 4; r++) {
    const p = prob(800 + 200 * r, r === 1 ? 1 : r === 4 ? 4 : 3, { pattern: card });
    if (r === 1) p.difficulty = '800';
    bank13.push(p);
    topicProblems.push({
      id: p.id, role: 'ladder', card, rung: r, twist: r === 1 ? 'Base case of the card' : `Placeholder twist ${r}`,
      summary: `Placeholder summary for ${card} rung ${r}.`,
      hints: ['Placeholder hint one.', 'Placeholder hint two.', 'Placeholder hint three.'],
    });
  }
// Extra practice (not in the ladder): shows under "More practice".
bank13.push(prob(1100, 3, { pattern: 'opposite-ends' }), prob(1500, 4, { pattern: 'merge-walk' }));
// Reserved: 5 own drill items, 4 look-alikes, 3 checkpoint, 9 review.
const res = (purpose, tier, rating, extra = {}) => prob(rating, tier, { set: 'reserved', reserved_for: purpose, ...extra });
const drillOwn = [1, 2, 3, 4, 5].map(() => res('drill', 3, 1200));
const look = [res('lookalike', 3, 1200), res('lookalike', 3, 1200, { techniques: ['1.2'] }), res('lookalike', 3, 1300), res('lookalike', 3, 1300, { techniques: ['1.2'] })];
look.forEach((p, i) => (p.lookalike_of = look[i ^ 1].id));
const checkpoint = cards.map((c) => res('checkpoint', 3, 1300, { pattern: c }));
const review = [1, 2, 3].flatMap((s) => cards.map((c) => ({ p: res('review', s === 3 ? 4 : 3, s === 3 ? 1500 : 1300, { pattern: c }), s, c })));
bank13.push(...drillOwn, ...look, ...checkpoint, ...review.map((r) => r.p));
// Earlier-topic drill items live in 1.2's bank as later_drill.
const bank12 = [1, 2, 3].map(() => ({ ...prob(900, 2, { pattern: 'prefix-count-lookup', set: 'reserved', reserved_for: 'later_drill', techniques: ['1.2'] }) }));

for (const p of drillOwn) topicProblems.push({ id: p.id, role: 'drill', summary: 'Placeholder drill: n ≤ 2·10^5, positive values, longest segment with sum ≤ K.' });
for (const p of bank12) topicProblems.push({ id: p.id, role: 'drill', summary: 'Placeholder drill: n ≤ 2·10^5, values may be negative, count segments with sum exactly K.' });
for (const p of look) topicProblems.push({ id: p.id, role: 'lookalike', summary: 'Placeholder look-alike summary.' });
for (const p of checkpoint) topicProblems.push({ id: p.id, role: 'checkpoint', card: p.pattern, summary: 'Placeholder checkpoint summary.' });
for (const r of review) topicProblems.push({ id: r.p.id, role: 'review', card: r.c, review_set: r.s, summary: `Placeholder review summary (set ${r.s}).` });

const card = (id, name, k) => ({
  id, name, decisive_property: `Placeholder decisive property for ${name}.`, from_theorem: `Theorem 1.3.${k}`,
  how_to_test: 'Placeholder test.', weak_signals: ['Longest or shortest contiguous segment with a condition'],
  kill_signals: ['Values may be negative'], lookalikes: [{ description: 'Placeholder look-alike', needs: '1.2 prefix sums', flipping_difference: 'Negative values.' }],
  complexity: 'O(n): each pointer moves at most n times.',
});
const topic = {
  id: '1.3',
  cards: [card('shrinkable-window', 'Shrinkable window', 1), card('fixed-window', 'Fixed-size window', 2), card('count-windows', 'Count valid windows', 3)],
  problems: topicProblems,
  drill: [
    ...drillOwn.map((p) => ({ problem: p.id, answer_card: 'shrinkable-window', answer_topic: '1.3', property: 'Closed under shrinking.', why_others_fail: 'Placeholder.' })),
    ...bank12.map((p) => ({ problem: p.id, answer_card: 'prefix-count-lookup', answer_topic: '1.2', property: 'Exact sum: pairs of equal prefix values.', why_others_fail: 'Negative values break shrinking.' })),
  ],
  lookalike_pairs: [
    { a: look[0].id, b: look[1].id, a_tool: 'shrinkable-window (1.3)', b_tool: 'prefix-count-lookup (1.2)', flipping_difference: 'B allows negative values.' },
    { a: look[2].id, b: look[3].id, a_tool: 'count-windows (1.3)', b_tool: 'prefix-count-lookup (1.2)', flipping_difference: 'B asks for an exact sum.' },
  ],
  self_test: [1, 2, 3, 4, 5].map((i) => ({ q: `Placeholder question ${i}?`, a: `Placeholder answer ${i}.` })),
  checkpoint: { time_limit_minutes: 90, problems: checkpoint.map((p) => p.id) },
  decision_map: [
    { weak_signal: 'Longest/shortest contiguous segment with a condition', choose: 'shrinkable-window', when: 'Validity is closed under shrinking.',
      over: [{ card: 'prefix-count-lookup', because: 'Needed only for exact sums or negative values.' }] },
  ],
  glossary_added: ['window'],
};

const notes = (list) => list.map((p) => `## ${p.id} ${p.title} (tier ${p.tier}, pattern ${p.pattern}, set ${p.set})\n- Placeholder note.\n`).join('\n');
const header = '# PLACEHOLDER created by tests/placeholder/make.mjs. Must not be committed.\n';
// Later lessons draw drill items from the real 1.3 bank's later_drill problems, and the phase
// exam uses its exam problems, so those stay (with their notes) next to the placeholder's problems.
const real13 = existsSync(backupOf('src/data/bank/1-3.yaml')) ? parse(readFileSync(backupOf('src/data/bank/1-3.yaml'), 'utf8')).problems : [];
const keep13 = real13.filter((p) => ['later_drill', 'exam'].includes(p.reserved_for));
const realNotes13 = existsSync(backupOf('notes/bank/1.3.md')) ? readFileSync(backupOf('notes/bank/1.3.md'), 'utf8') : '';
const keepNotes13 = keep13.map((p) => (realNotes13.match(new RegExp(`^## ${p.id} .*\\n(?:(?!## ).*\\n)*`, 'm')) || [''])[0]).join('\n');
writeFileSync('src/data/bank/1-3.yaml', header + stringify({ topic: '1.3', status: 'in_progress', problems: [...bank13, ...keep13] }));
// The real 1.2 bank stays (the real 1.2 lesson uses it); the placeholder's later_drill items are
// appended to it, and the whole file is restored by --remove.
const real12 = parse(readFileSync(backupOf('src/data/bank/1-2.yaml'), 'utf8'));
writeFileSync('src/data/bank/1-2.yaml', header + stringify({ ...real12, problems: [...real12.problems, ...bank12] }));
writeFileSync('notes/bank/1.3.md', notes(bank13) + '\n' + keepNotes13);
writeFileSync('notes/bank/1.2.md', readFileSync(backupOf('notes/bank/1.2.md'), 'utf8') + '\n' + notes(bank12));
writeFileSync('src/data/topics/1-3.yaml', header + stringify(topic));
if (!existsSync(GLOSSARY_BACKUP)) writeFileSync(GLOSSARY_BACKUP, readFileSync(GLOSSARY, 'utf8'));
// Real lessons stay in place during the test, so their glossary terms stay too; the placeholder
// adds only the terms it needs that are not there yet.
const realGlossary = parse(readFileSync(GLOSSARY_BACKUP, 'utf8')) ?? [];
const have = new Set(realGlossary.map((g) => g.term.toLowerCase()));
writeFileSync(GLOSSARY, stringify([
  ...realGlossary,
  ...[
    { term: 'window', definition: 'A contiguous segment a[l..r] of an array.', topic: '1.3' },
    { term: 'GCD', expansion: 'greatest common divisor', definition: 'The largest positive integer dividing both numbers.', topic: '0.4' },
  ].filter((g) => !have.has(g.term.toLowerCase())),
]));
cpSync('tests/placeholder/window-sum', `${CODE}/window-sum`, { recursive: true });
mkdirSync('src/content/docs/phase-1', { recursive: true });
writeFileSync('src/content/docs/phase-1/1-3-two-pointers.mdx', `---
title: "1.3 Two pointers and sliding window"
sidebar:
  order: 9
topic: "1.3"
---
import { Code } from '@astrojs/starlight/components';
import TopicHeader from '../../../components/TopicHeader.astro';
import Cards from '../../../components/Cards.astro';
import Ladder from '../../../components/Ladder.astro';
import Drill from '../../../components/Drill.astro';
import LookalikePairs from '../../../components/LookalikePairs.astro';
import SelfTest from '../../../components/SelfTest.astro';
import Checkpoint from '../../../components/Checkpoint.astro';
import DecisionMapUpdate from '../../../components/DecisionMapUpdate.astro';
import windowSum from '../../../../code/0.0-placeholder/window-sum/solution.cpp?raw';

<TopicHeader topic="1.3" />

## 1. Why this topic exists
Placeholder. With $n = 2 \\cdot 10^5$, $O(n^2) \\approx 4 \\cdot 10^{10}$ operations.
## 2. Prerequisites and scope
### What you need
Placeholder.
### What this topic does not cover
Binary search on the answer is covered in topic 1.4.
## 3. Definitions
A **window** is a contiguous segment.
## 4. Theory and proofs
$$\\sum_{i=1}^{n} i = \\frac{n(n+1)}{2}$$

:::note[This proof needs]
1. Placeholder precondition.
:::
## 5. Recognition Cards
<Cards topic="1.3" />
## 6. Templates
<Code code={windowSum} lang="cpp" title="window-sum/solution.cpp" />
## 7. Bug catalogue
Placeholder.
## 8. Worked examples
### Example 1: Placeholder Problem
#### Step 1: Constraints → budget
#### Step 2: Question form → candidate tools
#### Step 3: Property check → decision
#### Step 4: Proof for this problem
#### Step 5: Code
#### Step 6: Alternative approach
## 9. Problem ladder
<Ladder topic="1.3" />
## 10. Identification drill
<Drill topic="1.3" />
## 11. Look-alike pairs
<LookalikePairs topic="1.3" />
## 12. Self-test questions
<SelfTest topic="1.3" />
## 13. Checkpoint
<Checkpoint topic="1.3" />
## 14. Decision map update
<DecisionMapUpdate topic="1.3" />
`);
console.log('placeholder created');
