#!/usr/bin/env node
// Proves his code is untouched: every fenced code block in the base version of a lesson must still appear
// verbatim (same text) in the new version. New blocks are allowed. Lines that mention maang.in are ignored on both sides.
// Usage: node scripts/check_code_unchanged.mjs <base-ref> <file.mdx> ...
import { execSync } from 'node:child_process';
import { readFileSync } from 'node:fs';
// Import-script escapes inside fences (&lt; &gt; &amp; \{ \}) render literally; the fix unescapes them, so compare unescaped text.
const unesc = (x) => x.replace(/&lt;/g, '<').replace(/&gt;/g, '>').replace(/&amp;/g, '&').replace(/\\([{}])/g, '$1');
function blocks(t) {
  const out = []; let cur = null;
  for (const l of t.split('\n')) {
    const m = /^\s*(```|~~~)\s*(\w*)/.exec(l);
    if (m) { if (cur) { out.push({ lang: cur.lang, text: unesc(cur.lines.join('\n').trim()) }); cur = null; } else cur = { lang: m[2], lines: [] }; continue; }
    // Decision 3 of LESSON_RESTORE_PLAN.md: a removed line that holds a maang.in link is allowed (paid site).
    // (a blank line right after such a line goes with it)
    if (cur) {
      if (/maang\.in/.test(l)) { cur.skipBlank = true; continue; }
      if (cur.skipBlank && l.trim() === '') { cur.skipBlank = false; continue; }
      cur.skipBlank = false;
      cur.lines.push(l.trimEnd());
    }
  }
  return out;
}
const [ref, ...files] = process.argv.slice(2);
let bad = 0;
for (const f of files) {
  const before = blocks(execSync(`git show ${ref}:${f}`, { encoding: 'utf8', maxBuffer: 1 << 26 }));
  const after = new Set(blocks(readFileSync(f, 'utf8')).map((b) => b.text));
  // A block that was only a sketch/diagram (no code) may be replaced by a figure: only cpp-like blocks are checked.
  // Labelled c++/cpp blocks always count; unlabelled blocks count only when they look like real statements.
  const isCode = (b) => /^(cpp|c\+\+|c)$/i.test(b.lang) || /;\s*$|#include|\bint\s+\w+\s*[=(;]|\bfor\s*\(.*\)|\breturn\b/m.test(b.text);
  before.forEach((blk, i) => { const b = blk.text; if (isCode(blk) && !after.has(b)) { bad++; console.log(`${f}: code block #${i + 1} changed or missing: ${b.split('\n')[0].slice(0, 80)}`); } });
}
console.log(bad ? `${bad} code block(s) changed` : 'all original code blocks unchanged');
process.exit(bad ? 1 : 0);
