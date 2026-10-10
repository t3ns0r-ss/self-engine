#!/usr/bin/env node
// Checks on the built site (PLAN.md Section 12, item 9): the rendered text of a Revision 2 lesson must not
// show any internal card id. Run after `astro build`; the build script does this.
import { existsSync, readFileSync, readdirSync } from 'node:fs';
import { parse } from 'yaml';

const curriculum = parse(readFileSync('src/data/curriculum.yaml', 'utf8'));
const errors = [];
let checked = 0;
for (const f of readdirSync('src/data/topics').filter((x) => x.endsWith('.yaml'))) {
  const tf = parse(readFileSync(`src/data/topics/${f}`, 'utf8'));
  if (!Array.isArray(tf.uses)) continue;
  const t = curriculum.find((x) => x.id === tf.id);
  const page = `dist/phase-${t.phase}/${t.id.replace('.', '-')}-${t.slug}/index.html`;
  if (!existsSync(page)) {
    errors.push(`${page}: not built`);
    continue;
  }
  checked++;
  const html = readFileSync(page, 'utf8');
  // Visible text only: drop scripts, styles, and every tag with its attributes (ids live in attributes).
  const text = html
    .replace(/<script[\s\S]*?<\/script>/g, ' ')
    .replace(/<style[\s\S]*?<\/style>/g, ' ')
    .replace(/<[^>]+>/g, ' ');
  for (const c of tf.cards) {
    if (!c.id.includes('-')) continue; // a one-word id such as "parity" is an ordinary word of the lesson
    const re = new RegExp(`(^|[^A-Za-z0-9-])${c.id}([^A-Za-z0-9-]|$)`);
    if (re.test(text)) errors.push(`${page}: the internal card id "${c.id}" is visible in the page text`);
  }
}
if (errors.length) {
  console.error(`Built-site check failed:\n${errors.map((e) => `  - ${e}`).join('\n')}`);
  process.exit(1);
}
console.log(`Built-site check passed: ${checked} Revision 2 lessons.`);
