#!/usr/bin/env node
// Usage: node scripts/new_kit.mjs <kit-path> --lang go|cpp --package <name> [--title "…"] [--prompt "…"]
//   e.g. node scripts/new_kit.mjs H5.6/lab/rung-1 --lang go --package ratelimit
// Creates exercises/<kit-path>/ from templates/kit-<lang>/, plus empty reference/<kit-path>/ and
// reference-mutants/<kit-path>/. For a ladder rung k > 1 (path ending in rung-k), the starter is a copy of
// reference/…/rung-(k-1), which must already exist, and min_mutants is 2.
import fs from 'node:fs';
import path from 'node:path';

const root = path.resolve(path.dirname(new URL(import.meta.url).pathname), '..');
const args = process.argv.slice(2);
const kit = args[0];
const opt = (name, def) => { const i = args.indexOf(`--${name}`); return i >= 0 ? args[i + 1] : def; };
const lang = opt('lang');
const pkg = opt('package');
if (!kit || !['go', 'cpp'].includes(lang) || !/^[a-z][a-z0-9_]*$/.test(pkg ?? '')) {
  console.error('usage: new_kit.mjs <kit-path> --lang go|cpp --package <lowercase_name> [--title …] [--prompt …]');
  process.exit(2);
}
const dst = path.join(root, 'exercises', kit);
if (fs.existsSync(dst)) { console.error(`already exists: exercises/${kit}`); process.exit(1); }
const vars = { KIT_PATH: kit, PACKAGE: pkg, TITLE: opt('title', 'TODO'), PROMPT: opt('prompt', 'TODO') };
const fill = (s) => s.replace(/\{\{(\w+)\}\}/g, (m, k) => (k in vars ? vars[k] : m));

function copyTemplate(src, out) {          // copies a folder, filling {{…}} in file names and contents
  fs.mkdirSync(out, { recursive: true });
  for (const name of fs.readdirSync(src)) {
    const from = path.join(src, name);
    const to = path.join(out, fill(name));
    if (fs.statSync(from).isDirectory()) copyTemplate(from, to);
    else { fs.writeFileSync(to, fill(fs.readFileSync(from, 'utf8'))); fs.chmodSync(to, fs.statSync(from).mode); }
  }
}
copyTemplate(path.join(root, 'templates', `kit-${lang}`), dst);

const rung = /(.*)\/rung-(\d+)$/.exec(kit);
if (rung && Number(rung[2]) > 1) {
  const prev = path.join(root, 'reference', `${rung[1]}/rung-${Number(rung[2]) - 1}`);
  if (!fs.existsSync(prev) || fs.readdirSync(prev).length === 0) { console.error(`previous rung's reference is missing or empty: ${path.relative(root, prev)}`); fs.rmSync(dst, { recursive: true }); process.exit(1); }
  fs.rmSync(path.join(dst, 'starter'), { recursive: true });
  fs.cpSync(prev, path.join(dst, 'starter'), { recursive: true });
}
if (rung) fs.writeFileSync(path.join(dst, 'min_mutants'), '2\n');
fs.mkdirSync(path.join(root, 'reference', kit), { recursive: true });
fs.mkdirSync(path.join(root, 'reference-mutants', kit), { recursive: true });
console.log(`created exercises/${kit}/ (${lang}), reference/${kit}/, reference-mutants/${kit}/`);
