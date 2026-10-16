#!/usr/bin/env node
// DESIGN_TRACKS_PLAN.md Section 18.2: checks src/data/exercises/INVENTORY.yaml (cards planned before use, quotas,
// a "no new structure" rung per ladder, no repeated scenario within a track). Run by `npm run build` through validate.mjs.
import { loadAll } from './lib/load.mjs';
import { validateInventory } from '../src/lib/inventory.mjs';

const d = loadAll();
if (!d.designData.inventory) { console.error('src/data/exercises/INVENTORY.yaml does not exist yet'); process.exit(1); }
const errs = [...d.errors, ...validateInventory(d.designData.inventory, d.designCurriculum)];
if (errs.length) { console.error(errs.map((e) => `  - ${e}`).join('\n')); process.exit(1); }
console.log(`Inventory is consistent for ${d.designCurriculum.length} topics.`);
