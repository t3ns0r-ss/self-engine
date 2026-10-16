// Zod schemas shared by src/content.config.ts (Astro collections) and the Node scripts in scripts/.
// PLAN.md Sections 4 and 9.1; PROBLEM_BANK_PLAN.md Sections 3 and 5.
import { z } from 'zod';

export const TOPIC_ID = /^[0-7]\.[1-8]$/;
const topicId = z.string().regex(TOPIC_ID, 'topic id like "1.3"');
const slug = z.string().regex(/^[a-z0-9]+(-[a-z0-9]+)*$/, 'kebab-case id');

// YAML 1.1 parsers (Astro's) read an unquoted 2026-10-02 as a Date; YAML 1.2 (scripts) as a string.
const isoDate = z.preprocess(
  (v) => (v instanceof Date ? v.toISOString().slice(0, 10) : v),
  z.string().regex(/^\d{4}-\d{2}-\d{2}$/, 'date YYYY-MM-DD'),
);

export const curriculumRow = z.strictObject({
  track: z.literal('cp').default('cp'),
  order: z.number().int().min(1),
  id: topicId,
  phase: z.number().int().min(0).max(7),
  slug,
  title: z.string().min(1),
  requires: z.array(topicId),
  keywords: z.array(z.string().min(1)),
  target_rating: z.tuple([z.number().int(), z.number().int()]),
});

// Design tracks (DESIGN_TRACKS_PLAN.md Sections 5-7). Ids: L{phase}.{n} and H{phase}.{n}; `order` is per track.
export const DESIGN_TOPIC_ID = /^(L[0-7]\.[0-8]|H[0-8]\.([1-9]|10))$/;
export const designTopicId = z.string().regex(DESIGN_TOPIC_ID, 'topic id like "L2.1" or "H4.2"');
export const KINDS = ['measured', 'standard', 'light', 'capstone'];
export const LAB_STACKS = ['postgres', 'mysql', 'redis', 'kafka'];
export const designCurriculumRow = z.strictObject({
  track: z.enum(['lld', 'hld']),
  order: z.number().int().min(1),
  id: designTopicId,
  phase: z.string().regex(/^[LH][0-8]$/),
  slug,
  kind: z.enum(KINDS),
  title: z.string().min(1),
  requires: z.array(designTopicId),
  lab: z.string().min(1).optional(),                 // HLD only: one line, what is built (Section 6)
  infra: z.array(z.enum(LAB_STACKS)).optional(),     // HLD only: stacks the lab needs on the lab server, [] for none
  keywords: z.array(z.string().min(1)),
}).superRefine((r, ctx) => {
  const hld = r.track === 'hld';
  if (hld && (r.lab === undefined || r.infra === undefined)) ctx.addIssue({ code: 'custom', message: `HLD topic ${r.id} needs lab and infra` });
  if (!hld && (r.lab !== undefined || r.infra !== undefined)) ctx.addIssue({ code: 'custom', message: `LLD topic ${r.id} must not have lab or infra` });
});
/** One row of curriculum.yaml: a CP row or a design-track row. */
export const anyCurriculumRow = z.union([curriculumRow, designCurriculumRow]);
export const curriculumFile = z.array(anyCurriculumRow);

export const pattern = z.strictObject({
  id: slug,
  name: z.string().min(1),
  description: z.string().min(1),
  precondition: z.string().min(1),
});
export const patternFile = z.strictObject({
  topic: topicId,
  patterns: z.array(pattern),
});

export const SOURCES = ['codeforces', 'atcoder', 'cses', 'leetcode'];
export const RESERVED_FOR = ['drill', 'later_drill', 'lookalike', 'checkpoint', 'review', 'exam'];

export const bankProblem = z
  .strictObject({
    id: z.string().min(1),
    source: z.enum(SOURCES),
    title: z.string().min(1),
    url: z.string().url(),
    difficulty: z.string().min(1),
    tier: z.number().int().min(1).max(5),
    tier_basis: z.enum(['rating', 'contest_letter', 'judgement']),
    // For topic 7.8 the pattern is "{topic}:{pattern-id}".
    pattern: z.string().regex(/^([0-7]\.[1-8]:)?[a-z0-9]+(-[a-z0-9]+)*$/),
    set: z.enum(['practice', 'reserved']),
    reserved_for: z.enum(RESERVED_FOR).nullable(),
    lookalike_of: z.string().nullable().default(null),
    techniques: z.array(topicId).min(1),
    checked_on: isoDate,
    // page: the problem page was opened and the statement read. api: only the platform's official
    // API was reachable (title and difficulty confirmed, statement not read); Saurabh spot-checks.
    source_check: z.enum(['page', 'api']).default('page'),
  })
  .superRefine((p, ctx) => {
    if (p.set === 'practice' && p.reserved_for !== null)
      ctx.addIssue({ code: 'custom', message: `${p.id}: practice problems must have reserved_for: null` });
    if (p.set === 'reserved' && p.reserved_for === null)
      ctx.addIssue({ code: 'custom', message: `${p.id}: reserved problems need reserved_for` });
  });

export const bankFile = z.strictObject({
  topic: topicId,
  status: z.enum(['in_progress', 'complete', 'short']),
  problems: z.array(bankProblem),
});

// Topic data files: src/data/topics/{id-dash}.yaml (PLAN.md Section 5, with PROBLEM_BANK_PLAN.md
// Section 12 applied: problems reference bank ids; title, URL, difficulty, and checked_on live in
// the bank only).
export const ROLES = ['ladder', 'worked_example', 'drill', 'lookalike', 'checkpoint', 'review', 'exam'];

// A reference to a card of this or an earlier topic (PLAN.md Section 5, Revision 2).
export const cardRef = z.strictObject({ topic: topicId, card: slug });

// Pre-Revision-2 card shape. Topics that have no `uses` list still use it until the retrofit
// milestone R1 reaches them (PLAN.md Section 15); it is removed when R1 is finished.
export const legacyCard = z.strictObject({
  id: slug,
  name: z.string().min(1),
  decisive_property: z.string().min(1),
  from_theorem: z.string().regex(/^Theorem [0-7]\.[1-8]\.\d+$/, 'like "Theorem 1.3.1"'),
  how_to_test: z.string().min(1),
  weak_signals: z.array(z.string().min(1)).min(1),
  kill_signals: z.array(z.string().min(1)).min(1),
  lookalikes: z.array(z.strictObject({ description: z.string().min(1), needs: z.string().min(1), flipping_difference: z.string().min(1) })),
  complexity: z.string().min(1),
});

const nonEmpty = z.string().min(1);
const inlinePositive = z.strictObject({ inline: z.strictObject({ input: nonEmpty, answer: nonEmpty, why: nonEmpty }) });
const workedPositive = z.strictObject({ worked_example: nonEmpty, why: nonEmpty });
const inlineNegative = z.strictObject({
  inline: z.strictObject({ input: nonEmpty, answer: nonEmpty, method_gives: nonEmpty, why: nonEmpty }),
  correct_tool: cardRef,
});
const problemNegative = z.strictObject({ problem: nonEmpty, why: nonEmpty, correct_tool: cardRef });

export const card = z.strictObject({
  id: slug,
  name: nonEmpty,
  decisive_property: nonEmpty,
  from_theorem: z.string().regex(/^[0-7]\.[1-8]\.\d+$/, 'like "1.3.1"'),
  how_to_test: nonEmpty,
  constraint_shapes: z.array(nonEmpty).min(1).max(3),
  weak_signals: z.array(z.strictObject({ form: nonEmpty, shape: nonEmpty })).min(2).max(4),
  kill_signals: z.array(nonEmpty).min(1),
  in_action: z.strictObject({
    statement: nonEmpty,
    constraints: nonEmpty,
    budget: nonEmpty,
    candidates: z.array(z.strictObject({ tool: nonEmpty, verdict: z.enum(['chosen', 'rejected']), because: nonEmpty })).min(2),
    property_check: nonEmpty,
    decision: nonEmpty,
  }),
  examples: z.strictObject({
    positive: z.array(z.union([inlinePositive, workedPositive])).min(2),
    negative: z.array(z.union([inlineNegative, problemNegative])).min(2),
  }),
  lookalikes: z.array(z.strictObject({ description: nonEmpty, tool: cardRef, flipping_difference: nonEmpty })),
  complexity: nonEmpty,
});

export const topicProblem = z
  .strictObject({
    id: z.string().min(1),
    role: z.enum(ROLES),
    card: slug.nullable().default(null),
    rung: z.number().int().min(1).nullable().default(null),
    twist: z.string().min(1).nullable().default(null),
    summary: z.string().min(1),
    hints: z.array(z.string().min(1)).nullable().default(null),
    editorial_url: z.string().url().nullable().default(null),
    review_set: z.union([z.literal(1), z.literal(2), z.literal(3)]).nullable().default(null),
  })
  .superRefine((p, ctx) => {
    const need = (cond, msg) => cond || ctx.addIssue({ code: 'custom', message: `${p.id}: ${msg}` });
    if (p.role === 'ladder') {
      need(p.card, 'ladder problems need card');
      need(p.rung, 'ladder problems need rung');
      need(p.twist, 'ladder problems need twist');
      need(p.hints?.length === 3, 'ladder problems need exactly 3 hints');
    } else {
      need(p.rung === null && p.twist === null && p.hints === null, 'only ladder problems have rung, twist, and hints');
    }
    if (p.role === 'checkpoint' || p.role === 'review') need(p.card, `${p.role} problems need card`);
    need((p.role === 'review') === (p.review_set !== null), 'review_set is required for review problems and only for them');
  });

export const topicFile = z.strictObject({
  id: topicId,
  // true while the per-topic pipeline (PLAN.md Section 13) is under way: count rules are skipped
  // and the lesson shows a draft notice. Removed at step 10.
  draft: z.boolean().default(false),
  // Revision 2: every earlier topic this lesson relies on; rendered by TopicHeader and WhatYouNeed.
  uses: z.array(z.strictObject({ topic: topicId, what: z.string().min(1) })).optional(),
  theorems: z.array(z.strictObject({ id: z.string().regex(/^[0-7]\.[1-8]\.\d+$/), title: z.string().min(1), plain_words: z.string().min(1), code: z.string().min(1) })).optional(),
  cards: z.array(z.union([card, legacyCard])),
  problems: z.array(topicProblem),
  drill: z.array(
    z
      .strictObject({
        problem: z.string().min(1),
        // Revision 2 writes `answer`; the old pair is kept until R1 reaches the topic. Both forms
        // end up with answer_card and answer_topic filled in, which is what the code reads.
        answer: cardRef.optional(),
        answer_card: slug.optional(),
        answer_topic: topicId.optional(),
        property: z.string().min(1),
        why_others_fail: z.string().min(1),
      })
      .superRefine((d, ctx) => {
        if (!d.answer && !(d.answer_card && d.answer_topic)) ctx.addIssue({ code: 'custom', message: `${d.problem}: needs answer {topic, card}` });
      })
      .transform((d) => ({ ...d, answer_card: d.answer?.card ?? d.answer_card, answer_topic: d.answer?.topic ?? d.answer_topic })),
  ),
  lookalike_pairs: z.array(z.strictObject({
    a: z.string().min(1), b: z.string().min(1),
    a_tool: z.union([cardRef, z.string().min(1)]), b_tool: z.union([cardRef, z.string().min(1)]),
    shared_surface: z.string().min(1).optional(),
    flipping_difference: z.string().min(1),
    flipping_input: z.string().min(1).optional(),
  })),
  self_test: z.array(z.strictObject({ q: z.string().min(1), a: z.string().min(1) })),
  checkpoint: z.strictObject({ time_limit_minutes: z.number().int(), problems: z.array(z.string().min(1)) }),
  decision_map: z.array(z.strictObject({
    weak_signal: z.string().min(1),
    choose: slug,
    when: z.string().min(1),
    over: z.array(z.strictObject({ topic: topicId.optional(), card: slug, because: z.string().min(1) })),
  })),
  glossary_added: z.array(z.string().min(1)),
});

// src/data/glossary.yaml (PLAN.md Section 5.1).
export const glossaryEntry = z.strictObject({
  term: z.string().min(1),
  expansion: z.string().min(1).optional(),
  definition: z.string().min(1),
  topic: topicId,
});
export const glossaryFile = z.array(glossaryEntry);

// ---- Design-track data files (DESIGN_TRACKS_PLAN.md Sections 3, 7.4, 7.5, 10.7) ----
export const designConfig = z.strictObject({
  lld: z.strictObject({
    language: z.literal('cpp'),
    standard: z.string().regex(/^c\+\+(20|23|26)$/),
    compiler: z.string().min(1),
    flags: z.string().min(1),
    sanitizers_default: z.string().min(1),
    sanitizers_concurrency: z.string().min(1),
  }),
  hld: z.strictObject({
    language: z.literal('go'),
    go_version: z.string().regex(/^1\.\d+$/),
    module: z.string().min(1),
    allowed_modules: z.array(z.string().min(1)),   // third-party Go modules, each added through Section 9.5
    lab_server: z.boolean(),
  }),
});

export const rubricCriterion = z.strictObject({
  id: slug,
  name: z.string().min(1),
  weight: z.number().int().min(1).max(100),
  critical: z.boolean(),
  critical_when: z.string().min(1).optional(), // LLD ownership and concurrency: critical only when the prompt involves it
  anchors: z.strictObject({ 0: z.string().min(1), 1: z.string().min(1), 2: z.string().min(1) }),
});
export const rubric = z.strictObject({
  id: z.string().regex(/^rubric-(lld|hld)-[a-z-]+-v\d+$/),
  name: z.string().min(1),
  criteria: z.array(rubricCriterion).min(1),
});
export const rubricsFile = z.array(rubric);

const urlString = z.string().regex(/^https?:\/\/\S+$/, 'URL');
export const constant = z.strictObject({
  id: slug,
  quantity: z.string().min(1),
  value: z.number(),
  unit: z.enum(['s', 'bytes', 'bytes/s', 'requests/s', 'count', 'ratio']),
  display: z.string().min(1),
  source: z.strictObject({ title: z.string().min(1), url: urlString, accessed: isoDate, section: z.string().min(1) }),
  caveat: z.string().min(1),
});
export const constantsFile = z.array(constant);

export const productNamesFile = z.array(z.string().min(1));

// ---- Design-track topic, exercise, unit, lab and experiment files (DESIGN_TRACKS_PLAN.md Sections 7.2, 7.3, 7.6, 9) ----
const dText = z.string().min(1);
const dDate = z.union([isoDate, z.literal('TODO')]);          // scaffolding writes TODO; check D18 rejects it later
export const designCardRef = z.strictObject({ topic: designTopicId, card: slug });
export const CLAIM_KINDS = ['proved', 'computed', 'simulated', 'measured', 'experimented', 'cited'];
export const claimId = z.string().regex(/^[LH][0-7]\.\d+\.\d+$/, 'claim id like "L2.1.1" or "H4.2.1"');
export const designSource = z.strictObject({ title: dText, url: urlString, accessed: isoDate, section: dText });

export const designClaim = z.strictObject({
  id: claimId,
  kind: z.enum(CLAIM_KINDS),
  title: dText,
  plain_words: dText,
  evidence: z.array(dText),                  // units under code/ ("L2.1/strategy-fee") or experiment ids
  source: designSource.nullable(),           // cited claims only
}).superRefine((c, ctx) => {
  if ((c.kind === 'cited') !== (c.source !== null)) ctx.addIssue({ code: 'custom', message: `${c.id}: source is required for cited claims and only for them` });
});

const dInlinePositive = z.strictObject({ inline: z.strictObject({ input: dText, answer: dText, why: dText }) });
const dInlineNegative = z.strictObject({
  inline: z.strictObject({ input: dText, answer: dText, why: dText }),
  correct_tool: z.union([designCardRef, z.strictObject({ simplest: dText })]),
});
export const designCard = z.strictObject({
  id: slug,
  name: dText,
  force: dText.optional(),                   // LLD
  need: dText.optional(),                    // HLD
  decisive_property: dText,
  from_claim: claimId,
  how_to_test: dText,
  trade_off_table: z.strictObject({ units: z.array(dText).min(1), overhead: dText, per_change: dText, blast_radius: dText, verdict: dText }).optional(),
  capacity_table: z.strictObject({ units: z.array(dText).min(1), threshold: dText, price: dText }).optional(),
  lab: z.strictObject({ unit: dText, holds_test: dText, breaks_test: dText }).optional(),
  constraint_shapes: z.array(dText).min(1).max(3),
  weak_signals: z.array(z.strictObject({ form: dText, shape: dText })).min(2).max(4),
  kill_signals: z.array(dText).min(2),
  in_action: z.strictObject({
    statement: dText, constraints: dText, budget: dText,
    candidates: z.array(z.strictObject({ tool: dText, verdict: z.enum(['chosen', 'rejected']), because: dText })).min(2),
    property_check: dText, decision: dText,
  }),
  examples: z.strictObject({
    positive: z.array(dInlinePositive).min(2),
    negative: z.array(dInlineNegative).min(2),
  }),
  lookalikes: z.array(z.strictObject({ description: dText, tool: designCardRef, flipping_difference: dText })),
  cost: dText,
});

export const designTopicFile = z.strictObject({
  id: designTopicId,
  track: z.enum(['lld', 'hld']),
  uses: z.array(z.strictObject({ topic: designTopicId, what: dText })),
  claims: z.array(designClaim),
  cards: z.array(designCard),
  lookalike_pairs: z.array(z.strictObject({
    a: dText, b: dText,
    a_tool: z.union([designCardRef, dText]), b_tool: z.union([designCardRef, dText]),
    flipping_difference: dText,
    flipping_input: dText.optional(),
  })),
  self_test: z.array(z.strictObject({ q: dText, a: dText })),
  decision_map: z.array(z.strictObject({
    weak_signal: dText, choose: dText, when: dText,
    over: z.array(z.strictObject({ topic: designTopicId.optional(), card: dText, because: dText })),
  })),
  glossary_added: z.array(dText),
});

export const EXERCISE_ROLES = ['ladder', 'worked_example', 'drill', 'checkpoint', 'review', 'exam'];
export const LLD_TYPES = ['recognise', 'refactor', 'build', 'change_ladder', 'mock'];
export const HLD_TYPES = ['recognise', 'estimate', 'lab', 'deep_dive', 'scale_ladder', 'failure', 'mock'];
const kitChecker = z.strictObject({ kind: z.literal('kit'), path: dText });
const numericChecker = z.strictObject({
  kind: z.literal('numeric'), calc: dText, key: dText, unit: dText, factor: z.number().positive().optional(),
});
const rubricChecker = z.strictObject({ kind: z.literal('rubric'), id: z.string().regex(/^rubric-(lld|hld)-[a-z-]+-v\d+$/) });
export const checker = z.discriminatedUnion('kind', [kitChecker, numericChecker, rubricChecker]);
export const exerciseAnswer = z.union([
  z.strictObject({ kind: z.literal('card'), card: designCardRef, property: dText, why_others_fail: dText }),
  z.strictObject({ kind: z.literal('none'), simplest: dText, why: dText }),
]);
export const designExercise = z.strictObject({
  id: z.string().regex(/^(rung|ex|est|r|mock|cp|exam)-\d+$|^rev-\d+-\d+$/, 'local id like rung-2, ex-1, est-1, r-3, mock-1, cp-1, rev-1-2, exam-4'),
  role: z.enum(EXERCISE_ROLES),
  type: z.enum([...new Set([...LLD_TYPES, ...HLD_TYPES])]),
  title: dText,
  prompt: dText,
  inspired_by: dText.nullable().optional(),
  card: slug.nullable().optional(),
  rung: z.number().int().min(1).nullable().optional(),
  new_force: dText.nullable().optional(),
  needs_new_structure: z.boolean().optional(),
  review_set: z.number().int().min(1).nullable().optional(),
  answer: exerciseAnswer.nullable().optional(),
  clarifying: z.array(z.strictObject({ q: dText, a: dText, critical: z.boolean() })).optional(),
  checkers: z.array(checker),
  run: dText.optional(),
  reference: dText.optional(),
  alternatives: z.array(dText).optional(),
  hints: z.array(dText).optional(),
  time_limit_minutes: z.number().int().positive().nullable().optional(),
  techniques: z.array(dText).optional(),
  checked_on: dDate.optional(),
});
export const designExerciseFile = z.strictObject({
  topic: designTopicId,
  exercises: z.array(designExercise),
});

export const unitYaml = z.strictObject({
  kind: z.enum(['solution', 'pattern']),
  domain: dText.optional(),
  variants: z.array(dText).optional(),
  claims: z.array(claimId).optional(),
  scenarios: z.array(z.strictObject({
    name: dText,
    request: dText,
    blast_radius: z.record(z.string(), z.strictObject({ count: z.number().int().min(0), behaviours: z.array(dText), where: dText })),
  })).optional(),
});
export const labYaml = z.strictObject({
  title: dText,
  holds: z.array(dText).min(1),
  breaks: z.array(dText).min(1),
  run: dText,
  experiments: z.array(dText),
  stacks: z.array(z.enum(LAB_STACKS)),
});
export const experimentRecord = z.strictObject({
  experiment: z.string().regex(/^[LH]\d\.\d+\/[a-z0-9-]+$/),
  program: dText,
  machine: z.strictObject({ cpu: dText, cores: z.number().int().min(1), os: dText, go: dText }),
  run_on: isoDate,
  commit: z.string().regex(/^[0-9a-f]{7,40}$/),
  shape_checks: z.array(dText).min(1),
  results_file: z.string().regex(/-labserver\.txt$|\.tsv$/, 'a results file; full runs are *-labserver.txt (D19)'),
});
export const inventoryFile = z.strictObject({
  topics: z.record(designTopicId, z.strictObject({
    cards: z.array(z.strictObject({ id: slug, name: dText })),
    ladder: z.array(z.strictObject({
      rung: z.number().int().min(1), card: slug.nullable(), new_force: dText, needs_new_structure: z.boolean(), tests: dText,
    })),
    drill: z.array(z.strictObject({ stub: dText, answer: z.union([z.literal('none'), designCardRef]) })),
    checkpoint: z.strictObject({ title: dText, type: z.enum([...new Set([...LLD_TYPES, ...HLD_TYPES])]) }).nullable(),
    reviews: z.array(z.strictObject({ set: z.number().int().min(1), stubs: z.array(dText).min(1) })),
    estimates: z.array(dText).optional(),
  })),
});
