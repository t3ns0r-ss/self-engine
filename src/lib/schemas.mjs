// Zod schemas shared by src/content.config.ts (Astro collections) and the Node scripts in scripts/.
// PLAN.md Sections 4 and 9.1; PROBLEM_BANK_PLAN.md Sections 3 and 5.
import { z } from 'zod';

export const TOPIC_ID = /^[0-7]\.[1-8]$/;
const topicId = z.string().regex(TOPIC_ID, 'topic id like "1.3"');
const slug = z.string().regex(/^[a-z0-9]+(-[a-z0-9]+)*$/, 'kebab-case id');

export const curriculumRow = z.strictObject({
  order: z.number().int().min(1),
  id: topicId,
  phase: z.number().int().min(0).max(7),
  slug,
  title: z.string().min(1),
  requires: z.array(topicId),
  keywords: z.array(z.string().min(1)),
  target_rating: z.tuple([z.number().int(), z.number().int()]),
});
export const curriculumFile = z.array(curriculumRow);

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
    checked_on: z.string().regex(/^\d{4}-\d{2}-\d{2}$/, 'date YYYY-MM-DD'),
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
