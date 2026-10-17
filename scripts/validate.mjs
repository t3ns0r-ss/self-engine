#!/usr/bin/env node
// Validates curriculum, pattern files, and bank files (PROBLEM_BANK_PLAN.md Section 10).
// Runs as the first step of `npm run build`; exits 1 with every error listed.
import { loadAll } from './lib/load.mjs';
import { validateAll } from '../src/lib/validate.mjs';
import { validateTopics } from '../src/lib/validate-topics.mjs';
import { ROOT } from './lib/load.mjs';
import { validateDesignFiles, validateCodeHygiene, validateDesignLesson, realFs } from '../src/lib/validate-design-files.mjs';
import { validateDesignCurriculum, validateDesignCounts, validateRubrics, validateConstants } from '../src/lib/validate-design.mjs';

const data = loadAll();
function designFileErrors(d) {
  const fsx = realFs(ROOT);
  const out = [...validateDesignFiles(d.designData, fsx, { rows: d.designCurriculum, products: d.designData.productNames }), ...validateCodeHygiene(fsx)];
  for (const [id, l] of Object.entries(d.designLessons)) {
    out.push(...validateDesignLesson(l.text, l.path));
    if (!d.designCurriculum.some((r) => r.id === id)) out.push(`${l.path}: frontmatter topic ${id} is not in the curriculum`);
  }
  return out;
}
const errors = [...data.errors, ...(data.errors.length ? [] : [...validateAll(data), ...validateTopics(data), ...validateDesignCurriculum(data.designCurriculum), ...validateDesignCounts(data.designCurriculum), ...validateRubrics(data.designData.rubrics), ...validateConstants(data.designData.constants), ...designFileErrors(data)])];
if (errors.length) {
  console.error(`Validation failed with ${errors.length} error(s):`);
  for (const e of errors) console.error(`  - ${e}`);
  process.exit(1);
}
const counts = Object.values(data.banks).map((b) => b.problems.length);
console.log(
  `Validation passed: ${data.curriculum.length} topics (+${data.designCurriculum.length} design topics), ${Object.keys(data.patterns).length} pattern files, ` +
    `${counts.length} bank files, ${counts.reduce((a, b) => a + b, 0)} bank problems, ` +
    `${Object.keys(data.topics).length} topic files, ${Object.keys(data.lessons).length} lessons, ${data.glossary.length} glossary terms.`,
);
