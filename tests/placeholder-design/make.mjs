// Creates (or removes, with --remove) placeholder LLD and HLD topics that exercise every design component
// (DESIGN_TRACKS_PLAN.md Section 11.7: "build each component with a small placeholder topic in D0, then delete it").
// Everything is fake and removed again by tests/e2e-design.sh; the files are listed in FILES so a cleanup cannot touch real ones.
import { writeFileSync, rmSync, mkdirSync, existsSync } from 'node:fs';
import { dirname } from 'node:path';

const ACTIVE = 'tests/placeholder-design/.active';
const w = (p, s) => { mkdirSync(dirname(p), { recursive: true }); writeFileSync(p, s); };
const FILES = [
  'src/data/topics/L2-1.yaml', 'src/data/exercises/L2-1.yaml', 'src/content/docs/lld/phase-2/L2-1-strategy.mdx',
  'src/data/topics/H4-2.yaml', 'src/data/exercises/H4-2.yaml', 'src/content/docs/hld/phase-4/H4-2-quorums.mdx',
];
const DIRS = ['code/L2.1', 'code/H4.2', 'exercises/L2.1', 'exercises/H4.2', 'reference/L2.1', 'reference/H4.2', 'src/content/docs/lld', 'src/content/docs/hld'];

if (process.argv.includes('--remove')) {
  if (!existsSync(ACTIVE)) { console.log('no design placeholder to remove'); process.exit(0); }
  for (const f of FILES) rmSync(f, { force: true });
  for (const d of DIRS) rmSync(d, { recursive: true, force: true });
  rmSync(ACTIVE);
  console.log('design placeholder removed');
  process.exit(0);
}
for (const d of DIRS) if (existsSync(d)) { console.error(`refusing: ${d} already exists`); process.exit(1); }
for (const f of FILES) if (existsSync(f)) { console.error(`refusing: ${f} already exists`); process.exit(1); }
writeFileSync(ACTIVE, 'present\n');

const USES = { 'L2.1': ['L0.5', 'L0.6', 'L1.2'], 'H4.2': ['H2.3', 'H3.2', 'H4.1'] };
const card = (id, name, extra) => `  - id: ${id}
    name: "${name}"
${extra.lead}
    decisive_property: "All variants fit one signature."
    from_claim: "${extra.claim}"
    how_to_test: "Write the one signature all variants could share."
${extra.table}    constraint_shapes: ["4 plans, 2 new plans a year: 2 edits a year"]
    weak_signals:
      - {form: "plans differ only in how a fee is computed", shape: "4 variants, 2 more expected"}
      - {form: "a new rule every quarter", shape: "4 changes a year"}
    kill_signals: ["two fixed plans for the life of the product", "fewer than 3 variants and none expected: a conditional costs 4 lines"]
    in_action: {statement: "Add plans.", constraints: "4 plans", budget: "2 edits a year", candidates: [{tool: "conditional", verdict: rejected, because: "branches grow"}, {tool: "${name}", verdict: chosen, because: "one class per plan"}], property_check: "one signature", decision: "${name}"}
    examples:
      positive:
        - {inline: {input: "hourly, daily, weekly", answer: "${name}", why: "same signature"}}
        - {inline: {input: "four plans", answer: "${name}", why: "same signature"}}
      negative:
        - {inline: {input: "two fixed plans", answer: "plain conditional", why: "no change expected"}, correct_tool: {simplest: "plain conditional"}}
        - {inline: {input: "one plan", answer: "nothing", why: "nothing varies"}, correct_tool: {simplest: "one function"}}
    lookalikes: []
    cost: "One extra file per variant."
`;
const topic = (id, track, claim, cardBlock) => `id: "${id}"
track: ${track}
uses:
${(USES[id]).map((u) => `  - {topic: "${u}", what: "Needed first"}`).join('\n')}
claims:
${claim}
cards:
${cardBlock}lookalike_pairs: []
self_test:
  - {q: "What does the pattern cost?", a: "One file per variant."}
decision_map:
  - {weak_signal: "a new variant every quarter", choose: "${track === 'lld' ? 'strategy' : 'quorum-replication'}", when: "variants share a signature", over: []}
glossary_added: []
`;
const mdx = (id, track, phase, slug, extra) => `---
title: "${id} Placeholder"
sidebar:
  order: 1
topic: "${id}"
---
import { Code } from '@astrojs/starlight/components';
import TopicHeader from '../../../../components/TopicHeader.astro';
import WhatYouNeed from '../../../../components/WhatYouNeed.astro';
import ClaimEvidence from '../../../../components/design/ClaimEvidence.astro';
import TradeOffTable from '../../../../components/design/TradeOffTable.astro';
import LabRunner from '../../../../components/design/LabRunner.astro';
import ExperimentResult from '../../../../components/design/ExperimentResult.astro';
import Cards from '../../../../components/Cards.astro';
import Exercises from '../../../../components/design/Exercises.tsx';
import Drill from '../../../../components/Drill.tsx';
import LookalikePairs from '../../../../components/LookalikePairs.astro';
import SelfTest from '../../../../components/SelfTest.astro';
import Checkpoint from '../../../../components/Checkpoint.tsx';
import DecisionMapUpdate from '../../../../components/DecisionMapUpdate.astro';

<TopicHeader topic="${id}" />

## 1. Why this topic exists
A placeholder.

## 2. Prerequisites and scope
### What you need
<WhatYouNeed topic="${id}" />
### What this topic does not cover
Nothing.

## 3. Definitions
A definition.

## 4. Principles and claims
${extra}

## 5. Recognition Cards
<Cards topic="${id}" />

## 6. Reference designs
${track === 'hld' ? '<LabRunner unit="H4.2/lab-quorumkv" />' : '<TradeOffTable unit="L2.1/strategy-fee" />'}

## 7. Mistake catalogue
### Mistake: none
Nothing.

## 8. Worked examples
### Example 1: Placeholder
#### Step 1: Numbers
n
#### Step 2: Wording → candidate structures
c
#### Step 3: Property check → decision
p
#### Step 4: Design
d
#### Step 5: Code or calculation
c
#### Step 6: Decision record
r

## 9. Exercise ladder
<Exercises topic="${id}" client:load />

## 10. Recognition drill
<Drill topic="${id}" client:load />

## 11. Look-alike pairs
<LookalikePairs topic="${id}" />

## 12. Self-test questions
<SelfTest topic="${id}" />

## 13. Checkpoint
<Checkpoint topic="${id}" client:load />

## 14. Decision map update
<DecisionMapUpdate topic="${id}" />
`;

// ---------------- LLD L2.1 ----------------
w('code/L2.1/caller-unchanged/unit.yaml', 'kind: solution\nclaims: ["L2.1.1"]\n');
w('code/L2.1/caller-unchanged/fee.hpp', '#pragma once\nstruct Fee { virtual ~Fee() = default; virtual int fee(int minutes) const = 0; };\n');
w('code/L2.1/caller-unchanged/test.sh', '#!/usr/bin/env bash\ntrue\n');
for (const [name, domain] of [['strategy-fee', 'parking-fees'], ['strategy-notify', 'notifications']]) {
  const d = `code/L2.1/${name}`;
  w(`${d}/unit.yaml`, `kind: pattern
domain: ${domain}
variants: [naive, patterned]
claims: ["L2.1.2"]
scenarios:
  - name: 01-weekend
    request: "Add a weekend plan."
    blast_radius:
      naive: {count: 2, behaviours: ["HOURLY", "DAILY"], where: "fee"}
      patterned: {count: 0, behaviours: [], where: "wiring only"}
`);
  for (const v of ['naive', 'patterned']) {
    w(`${d}/measured-${v}.tsv`, `base\tfiles=2\tnonblank_lines=${v === 'naive' ? 20 : 31}\nscenario\tfiles_modified\tfiles_added\tfiles_deleted\tlines_added_in_modified\tlines_removed_in_modified\tlines_in_new_files\n01-weekend\t${v === 'naive' ? '1\t0\t0\t4\t0\t0' : '1\t1\t0\t1\t0\t7'}\n`);
  }
}
w('src/data/topics/L2-1.yaml', topic('L2.1', 'lld', `  - {id: "L2.1.1", kind: proved, title: "Callers that depend on the signature never change", plain_words: "A new class needs no edit in callers.", evidence: ["L2.1/caller-unchanged"], source: null}
  - {id: "L2.1.2", kind: measured, title: "A new plan edits no existing plan", plain_words: "One new class and one line of wiring.", evidence: ["L2.1/strategy-fee", "L2.1/strategy-notify"], source: null}`,
  card('strategy', 'Strategy', { claim: 'L2.1.1', lead: '    force: "Behaviour varies independently of its callers."', table: '    trade_off_table: {units: ["L2.1/strategy-fee", "L2.1/strategy-notify"], overhead: "11 more lines", per_change: "1 file vs 1 file", blast_radius: "0 vs 2", verdict: "pays from the third plan"}\n' })));
w('src/data/exercises/L2-1.yaml', `topic: "L2.1"
exercises:
  - {id: rung-1, role: ladder, type: change_ladder, title: "Hourly plan", prompt: "Implement the hourly plan.", card: strategy, rung: 1, new_force: "One plan", needs_new_structure: false, checkers: [{kind: kit, path: "L2.1/ladder/rung-1"}], reference: "reference/L2.1/ladder/rung-1", hints: ["a", "b", "c"], techniques: ["L2.1"], checked_on: "2026-10-16"}
  - {id: r-1, role: drill, type: recognise, title: "Fees", prompt: "Four parking plans, two more expected: which structure?", answer: {kind: card, card: {topic: "L2.1", card: strategy}, property: "one signature", why_others_fail: "a conditional grows"}, checkers: []}
  - {id: r-2, role: drill, type: recognise, title: "Two plans", prompt: "Two fixed plans forever.", answer: {kind: none, simplest: "a conditional", why: "nothing varies"}, checkers: []}
  - {id: cp-1, role: checkpoint, type: build, title: "Build a fee calculator", prompt: "Build it.", clarifying: [{q: a, a: a, critical: true}, {q: b, a: b, critical: true}, {q: c, a: c, critical: false}, {q: d, a: d, critical: false}], checkers: [{kind: kit, path: "L2.1/ladder/rung-1"}, {kind: rubric, id: rubric-lld-build-v1}], time_limit_minutes: 60}
`);
w('exercises/L2.1/ladder/rung-1/test.sh', '#!/usr/bin/env bash\ntrue\n');
w('exercises/L2.1/ladder/rung-1/starter/fee.hpp', '#pragma once\n');
w('reference/L2.1/ladder/rung-1/fee.hpp', '#pragma once\n');
w('reference/L2.1/ladder/rung-1/SOLUTION.md', 'The design in a few lines.\n');
w('src/content/docs/lld/phase-2/L2-1-strategy.mdx', mdx('L2.1', 'lld', 2, 'strategy', '**Claim L2.1.1.** Callers never change.\n\n<ClaimEvidence claim="L2.1.1" />'));

// ---------------- HLD H4.2 ----------------
w('code/H4.2/calc-x/main.go', 'package main\n\nimport "fmt"\n\nfunc main() { fmt.Println("peak_reads = 4200 requests/s") }\n');
w('code/H4.2/calc-x/expected.txt', 'peak_reads = 4200 requests/s\n');
w('code/H4.2/lab-quorumkv/lab.yaml', 'title: "Quorum key-value store"\nholds: ["TestHolds"]\nbreaks: ["TestBreaks"]\nrun: "run.md"\nexperiments: []\nstacks: []\n');
w('code/H4.2/lab-quorumkv/run.md', '# Run it\n\n    bash scripts/labserver.sh up postgres\n    go run ./H4.2/lab-quorumkv/cmd/node -id a\n');
w('code/H4.2/lab-quorumkv/quorumkv_test.go', 'package quorumkv\n\nimport "testing"\n\nfunc TestHolds(t *testing.T) {}\nfunc TestBreaks(t *testing.T) {}\n');
w('code/H4.2/lab-quorumkv/quorumkv.go', 'package quorumkv\n');
w('src/data/topics/H4-2.yaml', topic('H4.2', 'hld', `  - {id: "H4.2.1", kind: computed, title: "Peak reads", plain_words: "Peak is 4200 reads a second.", evidence: ["H4.2/calc-x"], source: null}`,
  card('quorum-replication', 'Quorum replication', { claim: 'H4.2.1', lead: '    need: "Survive one replica down at 4200 reads a second."', table: '    capacity_table: {units: ["H4.2/calc-x"], threshold: "above 1 machine", price: "3x storage"}\n    lab: {unit: "H4.2/lab-quorumkv", holds_test: TestHolds, breaks_test: TestBreaks}\n' })));
w('src/data/exercises/H4-2.yaml', `topic: "H4.2"
exercises:
  - {id: rung-1, role: ladder, type: lab, title: "Put and Get", prompt: "Implement Put and Get over 3 replicas.", card: quorum-replication, rung: 1, new_force: "Basic Put and Get", needs_new_structure: false, clarifying: [{q: a, a: a, critical: true}, {q: b, a: b, critical: true}, {q: c, a: c, critical: false}, {q: d, a: d, critical: false}], checkers: [{kind: kit, path: "H4.2/lab/rung-1"}], run: "Start 3 nodes, cut one with faultproxy.", reference: "reference/H4.2/lab/rung-1", hints: ["a", "b", "c"], techniques: ["H4.2"], checked_on: "2026-10-16"}
  - {id: est-1, role: worked_example, type: estimate, title: "Peak reads", prompt: "10 million users, 3 reads each a day, peak factor 3.", checkers: [{kind: numeric, calc: "H4.2/calc-x", key: peak_reads, unit: "requests/s", factor: 2}]}
  - {id: r-1, role: drill, type: recognise, title: "Session store", prompt: "Session store across 3 zones, 99.999% for single keys.", answer: {kind: card, card: {topic: "H4.2", card: quorum-replication}, property: "W+R>N", why_others_fail: "async replication loses writes"}, checkers: []}
  - {id: r-2, role: drill, type: recognise, title: "Admin tool", prompt: "A single-region admin tool, 50 requests a day.", answer: {kind: none, simplest: "one database", why: "no scale"}, checkers: []}
  - {id: cp-1, role: checkpoint, type: lab, title: "Read repair", prompt: "Add read repair.", checkers: [{kind: kit, path: "H4.2/lab/rung-1"}], time_limit_minutes: 45}
`);
w('exercises/H4.2/lab/rung-1/test.sh', '#!/usr/bin/env bash\ntrue\n');
w('exercises/H4.2/lab/rung-1/starter/kv.go', 'package kv\n');
w('reference/H4.2/lab/rung-1/kv.go', 'package kv\n');
w('reference/H4.2/lab/rung-1/SOLUTION.md', 'Quorum of 2 of 3.\n');
w('src/content/docs/hld/phase-4/H4-2-quorums.mdx', mdx('H4.2', 'hld', 4, 'quorums', '**Claim H4.2.1.** Peak reads are 4200 a second.\n\n<ClaimEvidence claim="H4.2.1" />'));
console.log('design placeholder created');
