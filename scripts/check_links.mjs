#!/usr/bin/env node
// Checks the built site in dist/: every internal link and asset path starts with the base path
// (BASE_PATH, e.g. /self-engine/ on GitHub Pages) and points at a file that exists.
//   BASE_PATH=/self-engine/ npm run build && BASE_PATH=/self-engine/ node scripts/check_links.mjs
import { readFileSync, readdirSync, existsSync, statSync } from 'node:fs';
import { join } from 'node:path';

const base = process.env.BASE_PATH || '/';
const dist = 'dist';
const files = readdirSync(dist, { recursive: true }).map(String).filter((f) => f.endsWith('.html'));
const problems = [];
const exists = (path) => {
  const p = join(dist, decodeURI(path.slice(base.length)));
  return (existsSync(p) && statSync(p).isFile()) || existsSync(join(p, 'index.html')) || existsSync(`${p}.html`);
};
for (const f of files) {
  const html = readFileSync(join(dist, f), 'utf8');
  for (const m of html.matchAll(/\s(?:href|src)="(\/[^"#?]*)/g)) {
    const path = m[1];
    if (path.startsWith('//')) continue; // protocol-relative external URL
    if (!path.startsWith(base)) problems.push(`${f}: ${path} does not start with ${base}`);
    else if (!exists(path)) problems.push(`${f}: ${path} does not exist`);
  }
}
const unique = [...new Set(problems)];
if (unique.length) {
  console.error(`${unique.length} broken internal link(s):`);
  for (const p of unique.slice(0, 50)) console.error(`  - ${p}`);
  process.exit(1);
}
console.log(`Links OK: ${files.length} pages checked with base ${base}`);
