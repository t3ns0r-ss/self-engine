#!/usr/bin/env node
// DESIGN_TRACKS_PLAN.md Section 12, D11: fails if a keyword of a design-track topic appears inside a keyword of an
// earlier topic of the same track, or inside a required lesson heading. Also run by `npm run build` through validate.mjs.
import { loadAll } from './lib/load.mjs';
import { keywordCollisions } from '../src/lib/validate-design.mjs';

const { designCurriculum, errors } = loadAll();
const found = [...errors, ...keywordCollisions(designCurriculum)];
if (found.length) {
  console.error(found.map((e) => `  - ${e}`).join('\n'));
  process.exit(1);
}
console.log(`No keyword collisions in ${designCurriculum.length} design topics.`);
