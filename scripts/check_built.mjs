#!/usr/bin/env node
// Checks on the built site (PLAN.md Section 12, item 9): the rendered text of a Revision 2 lesson must not
// show any internal card id. Run after `astro build`; the build script does this.
import { existsSync, readFileSync, readdirSync } from 'node:fs';
import { parse } from 'yaml';

const curriculum = parse(readFileSync('src/data/curriculum.yaml', 'utf8'));
const errors = [];
let checked = 0;
for (const f of readdirSync('src/data/topics').filter((x) => x.endsWith('.yaml') && /^\d/.test(x))) {
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
// ---- Design tracks: D14 (reserved items never in built HTML) and no visible internal card ids ----
const visibleText = (html) => html.replace(/<script[\s\S]*?<\/script>/g, ' ').replace(/<style[\s\S]*?<\/style>/g, ' ').replace(/<[^>]+>/g, ' ');
const htmlFiles = (dir) => (existsSync(dir) ? readdirSync(dir, { recursive: true }).map(String).filter((f) => f.endsWith('.html')).map((f) => `${dir}/${f}`) : []);
const designPages = [...htmlFiles('dist/lld'), ...htmlFiles('dist/hld')];
const pageTexts = new Map(designPages.map((p) => [p, readFileSync(p, 'utf8')]));
let reservedChecked = 0;
for (const f of existsSync('src/data/exercises') ? readdirSync('src/data/exercises').filter((x) => /^[LH].*\.yaml$/.test(x)) : []) {
  const ex = parse(readFileSync(`src/data/exercises/${f}`, 'utf8'));
  for (const e of ex.exercises) {
    if (e.role === 'ladder' || e.role === 'worked_example') continue;
    reservedChecked++;
    const needles = [`${ex.topic}/${e.id}`, e.prompt, ...(e.title.length > 12 ? [e.title] : [])];
    for (const [p, html] of pageTexts) for (const n of needles) if (html.includes(n)) errors.push(`${p}: contains reserved item ${ex.topic}/${e.id} ("${n.slice(0, 40)}") (D14)`);
  }
}
for (const f of existsSync('src/data/topics') ? readdirSync('src/data/topics').filter((x) => /^[LH].*\.yaml$/.test(x)) : []) {
  const tf = parse(readFileSync(`src/data/topics/${f}`, 'utf8'));
  const t = curriculum.find((x) => x.id === tf.id);
  const page = `dist/${t.track}/phase-${t.phase.slice(1)}/${tf.id.replace('.', '-').toLowerCase()}-${t.slug}/index.html`;
  if (!existsSync(page)) { errors.push(`${page}: not built`); continue; }
  const text = visibleText(readFileSync(page, 'utf8'));
  for (const c of tf.cards) {
    if (!c.id.includes('-')) continue;
    if (new RegExp(`(^|[^A-Za-z0-9-])${c.id}([^A-Za-z0-9-]|$)`).test(text)) errors.push(`${page}: the internal card id "${c.id}" is visible in the page text`);
  }
  checked++;
}
if (errors.length) {
  console.error(`Built-site check failed:\n${errors.map((e) => `  - ${e}`).join('\n')}`);
  process.exit(1);
}
// D10: every Mermaid block is rendered to an SVG image at build time; none left as source, none loaded from the network.
for (const [p, html] of pageTexts) {
  if (/language-mermaid|class="mermaid"/.test(html)) errors.push(`${p}: unrendered Mermaid block (D10)`);
  if (/<script[^>]+src="https?:/.test(html)) errors.push(`${p}: loads a script from the network (D10)`);
}
console.log(`Built-site check passed: ${checked} lessons, ${reservedChecked} reserved design items kept out of HTML.`);
