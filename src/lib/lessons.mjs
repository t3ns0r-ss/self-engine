// Finds lesson MDX files (those whose frontmatter declares `topic:`) under src/content/docs.
import { readFileSync, readdirSync, existsSync } from 'node:fs';
import { join, relative } from 'node:path';

export function findLessons(root) {
  const dir = join(root, 'src', 'content', 'docs');
  const out = {};
  const dupes = [];
  if (!existsSync(dir)) return { lessons: out, errors: dupes };
  for (const f of readdirSync(dir, { recursive: true }).map(String).sort()) {
    if (!/\.mdx?$/.test(f)) continue;
    const text = readFileSync(join(dir, f), 'utf8');
    const fm = /^---\n([\s\S]*?)\n---/.exec(text);
    const m = fm && /^topic:\s*["']?([0-9.]+)["']?\s*$/m.exec(fm[1]);
    if (!m) continue;
    const path = relative(root, join(dir, f));
    if (out[m[1]]) dupes.push(`${path}: topic ${m[1]} already has lesson ${out[m[1]].path}`);
    else out[m[1]] = { path, text };
  }
  return { lessons: out, errors: dupes };
}
