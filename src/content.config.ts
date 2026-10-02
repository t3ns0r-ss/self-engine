import { defineCollection } from 'astro:content';
import { file, glob } from 'astro/loaders';
import { docsLoader } from '@astrojs/starlight/loaders';
import { docsSchema } from '@astrojs/starlight/schema';
import { z } from 'astro/zod';
import { parse } from 'yaml';
import { curriculumRow, patternFile, bankFile, topicFile, glossaryEntry } from './lib/schemas.mjs';

export const collections = {
  docs: defineCollection({
    loader: docsLoader(),
    // Lessons declare which topic they teach (PLAN.md Section 6).
    schema: docsSchema({ extend: z.object({ topic: z.string().optional() }) }),
  }),
  curriculum: defineCollection({ loader: file('src/data/curriculum.yaml'), schema: curriculumRow }),
  bankPatterns: defineCollection({ loader: glob({ pattern: '*.yaml', base: 'src/data/bank/patterns' }), schema: patternFile }),
  bank: defineCollection({ loader: glob({ pattern: '*.yaml', base: 'src/data/bank' }), schema: bankFile }),
  topics: defineCollection({ loader: glob({ pattern: '*.yaml', base: 'src/data/topics' }), schema: topicFile }),
  // Glossary entries have no id field; the term serves as one.
  glossary: defineCollection({
    loader: file('src/data/glossary.yaml', {
      parser: (text) => (parse(text) ?? []).map((g: { term: string }) => ({ id: g.term, ...g })),
    }),
    schema: glossaryEntry.extend({ id: z.string() }),
  }),
};
