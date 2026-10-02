#!/usr/bin/env node
// Link checking for the problem bank (PLAN.md 9.3, PROBLEM_BANK_PLAN.md 7.3). For each id it opens the
// platform's own source, prints the exact title, the platform difficulty, and the statement text
// to the terminal for reading. Nothing is written into the repository: statements must never be
// copied there.
//
//   node scripts/fetch_problem.mjs ac-abc300_c cses-1068 lc-two-sum cf-4A
//   node scripts/fetch_problem.mjs --brief ...   (title and difficulty only)
//
// Sources: AtCoder and CSES problem pages; AtCoder difficulty from AtCoder Problems
// (kenkoooo problem-models.json, cached for the day outside the repository); LeetCode's own
// question data (the same data its page shows); Codeforces' official API for title, rating, and
// tags. Codeforces problem pages are behind a bot check from automated clients, so Codeforces
// statements are NOT read by this script (source_check: api in the bank).
import { execFileSync } from 'node:child_process';
import { existsSync, mkdirSync, readFileSync, statSync, writeFileSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join } from 'node:path';

const CACHE = join(tmpdir(), 'cp-bank-cache');
mkdirSync(CACHE, { recursive: true });
const UA = 'Mozilla/5.0 (X11; Linux x86_64) cp-training-bank-check';

function curl(url, args = []) {
  for (let attempt = 1; attempt <= 3; attempt++) {
    try {
      return execFileSync('curl', ['-sS', '-f', '-L', '-m', '60', '-A', UA, ...args, url], { maxBuffer: 64 << 20 }).toString('utf8');
    } catch (e) {
      if (attempt === 3) throw new Error(`could not open ${url}: ${String(e.stderr || e.message).trim().slice(0, 200)}`);
      execFileSync('sleep', [String(5 * attempt)]);
    }
  }
}

/** JSON from `url`, cached outside the repository for 24 hours. */
function cachedJson(name, url) {
  const p = join(CACHE, name);
  if (!existsSync(p) || Date.now() - statSync(p).mtimeMs > 864e5) writeFileSync(p, curl(url));
  return JSON.parse(readFileSync(p, 'utf8'));
}

const decode = (s) =>
  s.replace(/&lt;/g, '<').replace(/&gt;/g, '>').replace(/&quot;/g, '"').replace(/&#39;|&#x27;/g, "'").replace(/&nbsp;/g, ' ').replace(/&amp;/g, '&');
const text = (html) =>
  decode(
    html
      .replace(/<script[\s\S]*?<\/script>/g, '')
      .replace(/<style[\s\S]*?<\/style>/g, '')
      .replace(/<sup>([\s\S]*?)<\/sup>/g, '^$1')
      .replace(/<(br|\/p|\/li|\/h\d|\/pre|\/div|\/section)[^>]*>/g, '\n')
      .replace(/<li[^>]*>/g, '- ')
      .replace(/<[^>]+>/g, ''),
  )
    .replace(/[ \t]+/g, ' ')
    .replace(/\n\s*\n\s*\n+/g, '\n\n')
    .trim();

const today = () => new Date().toISOString().slice(0, 10);

function atcoder(task) {
  const contest = task.replace(/_[^_]+$/, '');
  const url = `https://atcoder.jp/contests/${contest}/tasks/${task}`;
  const html = curl(url);
  const head = /<span class="h2">\s*([\s\S]*?)\s*(?:<a|<\/span>)/.exec(html);
  if (!head) throw new Error(`${url}: no task title on the page`);
  const full = decode(head[1].trim()); // e.g. "C - Title"
  const title = full.replace(/^[A-Za-z0-9]+ - /, '');
  const en = /<span class="lang-en">([\s\S]*?)<\/span>\s*<\/div>\s*<\/div>|<span class="lang-en">([\s\S]*)<\/span>/.exec(html);
  const statement = text(en ? en[1] ?? en[2] : /<div id="task-statement">([\s\S]*?)<\/div>\s*<\/div>/.exec(html)?.[1] ?? '');
  const models = cachedJson('problem-models.json', 'https://kenkoooo.com/atcoder/resources/problem-models.json');
  const d = models[task]?.difficulty;
  // AtCoder Problems clips low difficulties for display: below 400 it shows 400 / exp(1 - d/400).
  const shown = d === undefined ? '—' : String(Math.round(d >= 400 ? d : 400 / Math.exp(1 - d / 400)));
  return { id: `ac-${task}`, source: 'atcoder', url, title, page_heading: full, difficulty: shown, statement };
}

function cses(n) {
  const url = `https://cses.fi/problemset/task/${n}`;
  const html = curl(url);
  const title = decode(/<title>CSES - ([^<]*)<\/title>/.exec(html)?.[1] ?? '');
  if (!title) throw new Error(`${url}: no title on the page`);
  const limits = text(/<ul class="task-constraints">([\s\S]*?)<\/ul>/.exec(html)?.[1] ?? '');
  const statement = text(/<div class="md">([\s\S]*?)<\/div>\s*<\/div>/.exec(html)?.[1] ?? '');
  return { id: `cses-${n}`, source: 'cses', url, title, difficulty: '—', statement: `${limits}\n\n${statement}` };
}

// LeetCode lists constraints after the examples: keep the task and the constraints, drop examples.
const lcStatement = (t) => {
  const [task] = t.split(/\nExample 1:/);
  const c = t.indexOf('Constraints:');
  return c >= 0 ? `${task.trim()}\n\n${t.slice(c)}` : t;
};

function leetcode(slug) {
  const url = `https://leetcode.com/problems/${slug}/`;
  const body = JSON.stringify({
    query: 'query q($s: String!) { question(titleSlug: $s) { title difficulty isPaidOnly content } }',
    variables: { s: slug },
  });
  const res = JSON.parse(curl('https://leetcode.com/graphql', ['-X', 'POST', '-H', 'Content-Type: application/json', '-H', `Referer: ${url}`, '--data', body]));
  const q = res.data?.question;
  if (!q) throw new Error(`${url}: no such question`);
  return { id: `lc-${slug}`, source: 'leetcode', url, title: q.title, difficulty: q.difficulty, premium: q.isPaidOnly, statement: q.isPaidOnly ? '(premium: do not use)' : lcStatement(text(q.content ?? '')) };
}

function codeforces(contest, index) {
  const url = `https://codeforces.com/problemset/problem/${contest}/${index}`;
  const api = cachedJson('cf-problemset.json', 'https://codeforces.com/api/problemset.problems');
  const i = api.result.problems.findIndex((p) => String(p.contestId) === contest && p.index === index);
  if (i < 0) throw new Error(`${url}: not in the Codeforces problemset API`);
  const p = api.result.problems[i];
  const solved = api.result.problemStatistics[i]?.solvedCount;
  return {
    id: `cf-${contest}${index}`, source: 'codeforces', url, title: p.name, difficulty: p.rating ? String(p.rating) : 'UNRATED',
    tags: p.tags, solved, statement: '(statement not read: Codeforces pages are not reachable by automated clients; title and rating are from the official API)',
  };
}

export function fetchProblem(id) {
  let m;
  if ((m = /^ac-([a-z0-9_]+)$/.exec(id))) return atcoder(m[1]);
  if ((m = /^cses-(\d+)$/.exec(id))) return cses(m[1]);
  if ((m = /^lc-([a-z0-9-]+)$/.exec(id))) return leetcode(m[1]);
  if ((m = /^cf-(\d+)([A-Z]\d?)$/.exec(id))) return codeforces(m[1], m[2]);
  throw new Error(`unknown id format: ${id}`);
}

if (import.meta.url === `file://${process.argv[1]}`) {
  const brief = process.argv.includes('--brief');
  for (const id of process.argv.slice(2).filter((a) => !a.startsWith('--'))) {
    try {
      const p = fetchProblem(id);
      console.log(`=== ${p.id} | ${p.title} | ${p.source} ${p.difficulty}${p.tags ? ` | tags: ${p.tags.join(', ')} | solved ${p.solved}` : ''}${p.premium ? ' | PREMIUM' : ''} | checked ${today()}`);
      // Samples are left out: the task, input format, and constraints come before them.
      if (!brief) console.log(`${p.statement.split(/\n(?:Sample Input 1|Example 1:|Example\n)/)[0].trim()}\n`);
    } catch (e) {
      console.log(`=== ${id} | ERROR ${e.message}`);
    }
  }
}
