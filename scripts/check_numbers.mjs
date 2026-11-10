#!/usr/bin/env node
// Checks that formatting kept the numbers. For every paragraph of the old version of a lesson (at <ref>), each number must
// still appear in the new version of the same lesson. LaTeX markup ($, \cdot, ^{}, braces) is removed before comparing, so
// `2·10^5` matches `$2 \cdot 10^5$`. Only paragraphs whose numbers all vanish are reported per number.
// Usage: node scripts/check_numbers.mjs <ref> <file.mdx> ...
import { execSync } from 'node:child_process';
import { readFileSync } from 'node:fs';

export function normalise(t) {
  return t
    .replace(/\\(cdot|times|,|;|!)/g, ' ')
    .replace(/\\(text|mathrm|operatorname)\{([^}]*)\}/g, '$2')
    .replace(/[$\\{}]/g, ' ')
    .replace(/[·×]/g, ' ')
    .replace(/\^/g, ' ')
    .replace(/(\d),(\d{3})\b/g, '$1$2');
}
const nums = (t) => (normalise(t).match(/\d+(?:\.\d+)?/g) ?? []);
function prose(t) {
  // drop code fences, frontmatter and import lines; keep paragraph structure
  return t.replace(/^---[\s\S]*?---/, '').replace(/```[\s\S]*?```/g, '').replace(/~~~[\s\S]*?~~~/g, '').replace(/^import .*$/gm, '');
}
function count(arr) { const m = new Map(); for (const x of arr) m.set(x, (m.get(x) ?? 0) + 1); return m; }

if (import.meta.url === `file://${process.argv[1]}`) {
  const [ref, ...files] = process.argv.slice(2);
  let bad = 0;
  for (const f of files) {
    const before = prose(execSync(`git show ${ref}:${f}`, { encoding: 'utf8', maxBuffer: 1 << 26 }));
    const after = count(nums(prose(readFileSync(f, 'utf8'))));
    for (const para of before.split(/\n\s*\n/)) {
      const lost = [...new Set(nums(para))].filter((n) => !after.has(n));
      if (lost.length) { bad++; console.log(`${f}: numbers ${lost.join(', ')} missing from the new version. Old paragraph: ${para.trim().replace(/\s+/g, ' ').slice(0, 110)}`); }
    }
  }
  console.log(bad ? `${bad} paragraph(s) lost a number` : 'all numbers of the old version are still present');
  process.exit(bad ? 1 : 0);
}
