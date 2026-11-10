#!/usr/bin/env node
// Flags maths-like text that is not inside $...$ , a code fence or inline code (LESSON_RESTORE_PLAN.md Section 4.3).
// Usage: node scripts/check_math.mjs <file.mdx> ...            lesson prose
//        node scripts/check_math.mjs --yaml <topic id> ...      text fields of src/data/topics/<id>.yaml (ids like 1.4 or 1-4)
// Headings, image alt text and figure captions are allowed to hold plain maths words (they cannot render KaTeX).
import { readFileSync } from 'node:fs';
import { parse } from 'yaml';

export const RULES = [
  [/O\(/, 'O(...) needs $O(...)$'],
  [/\^/, '^ needs maths'],
  [/[⌈⌉⌊⌋Σ∑√≤≥≠·×∈∞≈→]/u, 'maths symbol outside $...$'],
  [/\blog2\b|\blog\s?\(/i, 'log needs $\\log$'],
  [/\bn[CP]r\b/, 'nCr / nPr needs $\\binom{n}{r}$'],
  [/\bsqrt\(/, 'sqrt( needs $\\sqrt{}$'],
  [/(?<![\w.])\d+(\.\d+)?e\d+\b/, '1e9-style number in prose needs $10^9$'],
  [/\\[{}]/, 'import escape \\{ or \\}'],
];
// arrows are allowed in prose as a plain "implies" only where the style guide says so; keep the list short: drop '→' from the default check.
RULES[2][0] = /[⌈⌉⌊⌋Σ∑√≤≥≠·×∈∞≈]/u;

export function stripMaths(line) {
  return line
    .replace(/\\\$/g, '\u0000')
    .replace(/\$\$[\s\S]*?\$\$/g, ' ')
    .replace(/\$[^$\n]+\$/g, ' ')
    .replace(/`[^`\n]*`/g, ' ')
    .replace(/\u0000/g, '$');
}

export function checkMdx(text) {
  const out = [];
  const lines = text.split('\n');
  let fence = null, display = false, fm = false;
  lines.forEach((raw, i) => {
    const n = i + 1;
    if (i === 0 && raw.trim() === '---') { fm = true; return; }
    if (fm) { if (raw.trim() === '---') fm = false; return; }
    const f = /^\s*(```|~~~)/.exec(raw);
    if (f) { fence = fence ? null : f[1]; return; }
    if (fence) return;
    if (/^import /.test(raw)) return;
    if (/^\s*\$\$\s*$/.test(raw)) { display = !display; return; }
    if (display) return;
    if (/^#{1,6}\s/.test(raw)) return; // headings
    let t = raw
      .replace(/!\[[^\]]*\]\([^)]*\)/g, ' ') // image alt text
      .replace(/<img[^>]*>/g, ' ')
      .replace(/\]\([^)]*\)/g, ']'); // link targets
    if (/^\s*(<figcaption|\*Figure|_Figure|Figure \d)/i.test(t) || /^\s*<[A-Z]\w*[^>]*\/>\s*$/.test(t)) return; // captions, components
    t = stripMaths(t);
    for (const [re, msg] of RULES) {
      const m = re.exec(t);
      if (m) out.push({ line: n, msg, text: raw.trim().slice(0, 100) });
    }
  });
  return out;
}

function walk(v, path, fn) {
  if (typeof v === 'string') fn(v, path);
  else if (Array.isArray(v)) v.forEach((x, i) => walk(x, `${path}[${i}]`, fn));
  else if (v && typeof v === 'object') for (const [k, x] of Object.entries(v)) walk(x, `${path}.${k}`, fn);
}
const SKIP_KEYS = /\.(id|card|url|topic|problem|a|b|answer_topic|answer_card|source|difficulty|tool|role|unit|code_unit|format|pattern)(\[|$)/;

export function checkYaml(text) {
  const out = [];
  walk(parse(text), '', (s, path) => {
    if (SKIP_KEYS.test(path) || /^\w[\w-]*$/.test(s)) return;
    const t = stripMaths(s);
    for (const [re, msg] of RULES) if (re.test(t)) out.push({ line: path.replace(/^\./, ''), msg, text: s.slice(0, 100) });
  });
  return out;
}

if (import.meta.url === `file://${process.argv[1]}`) {
  const args = process.argv.slice(2);
  const yamlMode = args[0] === '--yaml';
  const files = yamlMode ? args.slice(1).map((id) => `src/data/topics/${id.replace('.', '-')}.yaml`) : args;
  let total = 0;
  for (const f of files) {
    const r = (yamlMode ? checkYaml : checkMdx)(readFileSync(f, 'utf8'));
    for (const x of r) console.log(`${f}:${x.line}: ${x.msg}: ${x.text}`);
    total += r.length;
  }
  console.log(`${total} unformatted maths finding(s)`);
  process.exit(total ? 1 : 0);
}
