#!/usr/bin/env node
// Proves his code is untouched: every fenced code block in the base version of a lesson must still appear
// verbatim (same text) in the new version. New blocks are allowed.
// Usage: node scripts/check_code_unchanged.mjs <base-ref> <file.mdx> ...
import { execSync } from 'node:child_process';
import { readFileSync } from 'node:fs';
function blocks(t) {
  const out = []; let cur = null;
  for (const l of t.split('\n')) {
    if (/^\s*(```|~~~)/.test(l)) { if (cur) { out.push(cur.join('\n').trim()); cur = null; } else cur = []; continue; }
    if (cur) cur.push(l.trimEnd());
  }
  return out;
}
const [ref, ...files] = process.argv.slice(2);
let bad = 0;
for (const f of files) {
  const before = blocks(execSync(`git show ${ref}:${f}`, { encoding: 'utf8', maxBuffer: 1 << 26 }));
  const after = new Set(blocks(readFileSync(f, 'utf8')));
  // A block that was only a sketch/diagram (no code) may be replaced by a figure: only cpp-like blocks are checked.
  const isCode = (b) => /[;{}]|#include|\bint\b|\bfor\s*\(|\breturn\b/.test(b);
  before.forEach((b, i) => { if (isCode(b) && !after.has(b)) { bad++; console.log(`${f}: code block #${i + 1} changed or missing: ${b.split('\n')[0].slice(0, 80)}`); } });
}
console.log(bad ? `${bad} code block(s) changed` : 'all original code blocks unchanged');
process.exit(bad ? 1 : 0);
