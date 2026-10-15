#!/usr/bin/env node
// Exports src/data/constants.yaml to code/_shared/constants.json (DESIGN_TRACKS_PLAN.md Section 9.6).
// Usage: node scripts/constants_export.mjs          write the file
//        node scripts/constants_export.mjs --check  exit 1 if the committed file differs from a fresh export
import { readFileSync, writeFileSync, mkdirSync, existsSync } from 'node:fs';
import { join, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';
import { parse } from 'yaml';
import { constantsFile } from '../src/lib/schemas.mjs';

const ROOT = join(dirname(fileURLToPath(import.meta.url)), '..');
const SRC = join(ROOT, 'src', 'data', 'constants.yaml');
const OUT = join(ROOT, 'code', '_shared', 'constants.json');

/** Calculators read { id: { value, unit } } only; the rest (source, caveat) stays in the YAML. */
export function exportConstants(yamlText) {
  const r = constantsFile.safeParse(parse(yamlText) ?? []);
  if (!r.success) throw new Error(r.error.issues.map((i) => `${i.path.join('.')}: ${i.message}`).join('; '));
  const out = {};
  for (const c of [...r.data].sort((a, b) => a.id.localeCompare(b.id))) out[c.id] = { value: c.value, unit: c.unit };
  return JSON.stringify(out, null, 2) + '\n';
}

if (process.argv[1] === fileURLToPath(import.meta.url)) {
  const fresh = exportConstants(readFileSync(SRC, 'utf8'));
  if (process.argv.includes('--check')) {
    if (!existsSync(OUT) || readFileSync(OUT, 'utf8') !== fresh) {
      console.error('code/_shared/constants.json is out of date: run node scripts/constants_export.mjs and commit it');
      process.exit(1);
    }
    console.log('constants.json is current');
  } else {
    mkdirSync(dirname(OUT), { recursive: true });
    writeFileSync(OUT, fresh);
    console.log(`wrote ${OUT}`);
  }
}
