#!/usr/bin/env node
// Checks that every C++ block that starts with a `// Fabricator/<folder>/<File>.cpp` comment matches that source file word for word
// (functions only: main, #include and `using namespace` lines may be absent; lines mentioning maang.in may be absent).
// Each block line must appear in the source file, in order, ignoring trailing whitespace.
// Usage: node scripts/check_fabricator.mjs <dir-with-the-cpp-files> <lesson.mdx>
import { readFileSync, existsSync } from 'node:fs';
import { join, basename } from 'node:path';
const [dir, lesson] = process.argv.slice(2);
const unesc = (x) => x.replace(/&lt;/g, '<').replace(/&gt;/g, '>').replace(/&amp;/g, '&').replace(/\\([{}])/g, '$1');
const lines = readFileSync(lesson, 'utf8').split('\n');
let bad = 0, n = 0, cur = null;
const norm = (l) => l.replace(/\s+$/, '');
function verify(b) {
  // A problem statement comment block may come first; the source comment follows it.
  const at = b.lines.findIndex((l) => /^\/\/ Fabricator\/[^/]+\/.+\.cpp\s*$/.test(l));
  if (at < 0) return;
  const m = /^\/\/ Fabricator\/[^/]+\/(.+\.cpp)\s*$/.exec(b.lines[at]);
  b = { start: b.start + at, lines: b.lines.slice(at) };
  n++;
  const f = join(dir, basename(m[1]));
  if (!existsSync(f)) { bad++; console.log(`${lesson}:${b.start}: no source file ${f}`); return; }
  const src = readFileSync(f, 'utf8').split('\n').map(norm);
  let pos = 0;
  b.lines.slice(1).forEach((raw, k) => {
    const l = norm(unesc(raw));
    if (l.trim() === '') return;
    let j = pos;
    while (j < src.length && src[j] !== l) j++;
    if (j >= src.length) { bad++; console.log(`${lesson}:${b.start + 1 + k}: line not in ${m[1]} (after line ${pos}): ${l.trim().slice(0, 90)}`); }
    else pos = j + 1;
  });
}
lines.forEach((l, i) => {
  if (/^\s*```/.test(l)) {
    if (cur) { verify(cur); cur = null; } else cur = { start: i + 2, lines: [] };
  } else if (cur) cur.lines.push(l);
});
console.log(bad ? `${bad} line(s) differ from the Fabricator files (${n} blocks checked)` : `all ${n} Fabricator blocks match their source files`);
process.exit(bad ? 1 : 0);
