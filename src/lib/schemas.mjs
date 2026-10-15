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
export const DESIGN_TOPIC_ID = /^(L[0-7]\.[1-8]|H[0-8]\.([1-9]|10))$/;
export const designTopicId = z.string().regex(DESIGN_TOPIC_ID, 'topic id like "L2.1" or "H4.2"');
export const KINDS = ['measured', 'standard', 'light', 'capstone'];
export const designCurriculumRow = z.strictObject({
  track: z.enum(['lld', 'hld']),
  order: z.number().int().min(1),
  id: designTopicId,
  phase: z.string().regex(/^[LH][0-8]$/),
  slug,
  kind: z.enum(KINDS),
  title: z.string().min(1),
  requires: z.array(designTopicId),
  keywords: z.array(z.string().min(1)),
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
  lld_language: z.string().min(1),
  lld_standard: z.string().regex(/^c\+\+(14|17|20|23)$/),
  hld_language: z.string().min(1),
  hld_python_min: z.string().regex(/^3\.\d+$/),
});

export const rubricCriterion = z.strictObject({
  id: slug,
  name: z.string().min(1),
  weight: z.number().int().min(1).max(100),
  critical: z.boolean(),
  critical_when: z.string().min(1).optional(), // LLD concurrency: critical only when the prompt involves it
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
