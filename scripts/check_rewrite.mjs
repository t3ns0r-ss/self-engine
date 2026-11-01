#!/usr/bin/env node
// Safety check for a prose rewrite of a notes-format lesson: compares <file> with its version in git (default HEAD).
// Every fenced code block, image link and external link of the old file must still be in the new one, and the
// new file must still compile as MDX (with math). Usage: node scripts/check_rewrite.mjs <file.mdx> [git-ref]
import { readFileSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { compile } from '@mdx-js/mdx';
import remarkMath from 'remark-math';

const [, , file, ref = 'HEAD'] = process.argv;
const oldText = execFileSync('git', ['show', `${ref}:${file}`], { encoding: 'utf8', maxBuffer: 1 << 26 });
const newText = readFileSync(file, 'utf8');

function blocks(text) {
  const out = [];
  let cur = null;
  for (const line of text.split('\n')) {
    const m = /^\s*(`{3,}|~{3,})/.exec(line);
    if (m && !cur) cur = { fence: m[1], lines: [] };
    else if (m && cur && m[1][0] === cur.fence[0] && m[1].length >= cur.fence.length && /^\s*[`~]+\s*$/.test(line)) { out.push(cur.lines.join('\n')); cur = null; }
    else if (cur) cur.lines.push(line);
  }
  return out;
}
const errors = [];
const newBlocks = new Set(blocks(newText).map((b) => b.trim()));
// Comments inside a code block may be reworded (they may hold the voice), so compare code with comments removed.
const strip = (b) => b.replace(/\/\*[\s\S]*?\*\//g, '').split('\n').map((l) => l.replace(/\s*\/\/.*$/, '').trimEnd()).filter((l) => l.trim() !== '').join('\n');
const newStripped = new Set([...newBlocks].map(strip));
blocks(oldText).forEach((b, i) => { if (!newStripped.has(strip(b.trim()))) errors.push(`code block #${i + 1} changed or missing:\n${b.split('\n').slice(0, 4).join('\n')}\n...`); });
for (const m of oldText.matchAll(/!\[[^\]]*\]\(([^)\s]+)\)/g)) if (!newText.includes(`](${m[1]})`)) errors.push(`image link missing: ${m[1]}`);
for (const m of oldText.matchAll(/\]\((https?:[^)\s]+)\)/g)) if (!newText.includes(m[1])) errors.push(`link missing: ${m[1]}`);
const heads = (t) => t.split('\n').filter((l) => /^## /.test(l));
for (const h of ['## Quick revision', '## Practice problems']) if (!heads(newText).includes(h)) errors.push(`missing heading ${h}`);
if (heads(newText).at(-1) !== '## Practice problems') errors.push('"## Practice problems" is not the last ## heading');
if (!newText.includes('<Ladder topic=')) errors.push('<Ladder /> missing');
try { await compile(newText, { remarkPlugins: [remarkMath] }); } catch (e) { errors.push(`MDX does not compile: ${e.message.split('\n')[0]} (line ${e.line ?? '?'})`); }
if (errors.length) { console.log(`${file}: ${errors.length} problem(s)\n- ${errors.join('\n- ')}`); process.exit(1); }
console.log(`${file}: rewrite checks passed`);
