#!/usr/bin/env node
// Checks the idea inventories in docs/restore/<topic-id>.md (LESSON_RESTORE_PLAN.md Phase 1).
// Each table row must have a status; a row with a heading anchor ("Heading" in the last cell, or `#anchor`) must point at a
// heading that exists in the lesson. Rows that say "present" or "added" must name where. With --strict (from Phase 2) no row may be
// missing or partial.
// Usage: node scripts/check_ideas.mjs [--strict] [topic ids]
import { readFileSync, readdirSync, existsSync } from 'node:fs';
import { parse } from 'yaml';

const STATUS = new Set(['present', 'partial', 'missing', 'duplicate', 'added', 'struck', 'contradiction']);
const strict = process.argv.includes('--strict');
const want = process.argv.slice(2).filter((a) => !a.startsWith('--'));
const curriculum = parse(readFileSync('src/data/curriculum.yaml', 'utf8'));
const dir = 'docs/restore';
const files = existsSync(dir) ? readdirSync(dir).filter((f) => /^\d-\d\.md$/.test(f)) : [];
let bad = 0, rows = 0;
const slug = (h) => h.toLowerCase().replace(/[^a-z0-9 -]/g, '').trim().replace(/\s+/g, '-');
for (const f of files) {
  const id = f.replace('.md', '').replace('-', '.');
  if (want.length && !want.includes(id)) continue;
  const t = curriculum.find((x) => x.id === id);
  const lessonPath = `src/content/docs/phase-${t.phase}/${f.replace('.md', '')}-${t.slug}.mdx`;
  const lesson = readFileSync(lessonPath, 'utf8');
  const headings = lesson.split('\n').filter((l) => /^#{2,4}\s/.test(l)).map((l) => l.replace(/^#+\s*/, '').trim());
  const hs = new Set(headings.map(slug));
  const counts = {};
  for (const line of readFileSync(`${dir}/${f}`, 'utf8').split('\n')) {
    if (!line.startsWith('|')) continue;
    const c = line.split('|').slice(1, -1).map((x) => x.trim());
    if (c.length < 6 || !/^\d+$/.test(c[0])) continue;
    rows++;
    const status = c[4].toLowerCase().split(/[\s(]/)[0];
    counts[status] = (counts[status] ?? 0) + 1;
    if (!STATUS.has(status)) { bad++; console.log(`${f}: row ${c[0]} has no valid status ("${c[4]}")`); continue; }
    if (strict && (status === 'missing' || status === 'partial')) { bad++; console.log(`${f}: row ${c[0]} is still ${status}`); }
    const anchors = [...c[5].matchAll(/"([^"]+)"/g)].map((m) => m[1]);
    if ((status === 'added' || status === 'present') && !anchors.length && !/line ~?\d+/.test(c[5])) { bad++; console.log(`${f}: row ${c[0]} (${status}) names no place in the lesson`); }
    if (status === 'added') for (const a of anchors) if (!hs.has(slug(a))) { bad++; console.log(`${f}: row ${c[0]} points to heading "${a}", which is not in ${lessonPath}`); }
  }
  console.log(`${id}: ${Object.entries(counts).map(([k, v]) => `${k} ${v}`).join(', ') || 'no rows'}`);
}
console.log(bad ? `${bad} problem(s) in ${rows} rows` : `inventory ok (${rows} rows in ${files.length} file(s))`);
process.exit(bad ? 1 : 0);
