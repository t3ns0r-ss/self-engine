#!/usr/bin/env node
// Validates curriculum, pattern files, and bank files (PROBLEM_BANK_PLAN.md Section 10).
// Runs as the first step of `npm run build`; exits 1 with every error listed.
import { loadAll } from './lib/load.mjs';
import { validateAll } from '../src/lib/validate.mjs';

const data = loadAll();
const errors = [...data.errors, ...(data.errors.length ? [] : validateAll(data))];
if (errors.length) {
  console.error(`Validation failed with ${errors.length} error(s):`);
  for (const e of errors) console.error(`  - ${e}`);
  process.exit(1);
}
const counts = Object.values(data.banks).map((b) => b.problems.length);
console.log(
  `Validation passed: ${data.curriculum.length} topics, ${Object.keys(data.patterns).length} pattern files, ` +
    `${counts.length} bank files, ${counts.reduce((a, b) => a + b, 0)} bank problems.`,
);
