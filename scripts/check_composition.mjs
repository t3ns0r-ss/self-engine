#!/usr/bin/env node
// Composition lint for notes-format lessons (docs/LESSON_COMPOSITION_RULES.md).
// It finds the faults of a lesson that was copied from a notebook instead of composed from it:
// theorems out of order, "his note" talk, repeated statements, uneven headings, two ways of counting the forms.
//
//   node scripts/check_composition.mjs [--json] [--v1 <dir>] <lesson.mdx> ...
//
// Rule ids (C1..C14) match the numbers in the rules document. Findings have a severity:
//   error = must be fixed before merge, warn = a person must look at it.
// Exit code 1 if any error is found. --json prints every finding as JSON (used by the audit report).
import { readFileSync, existsSync, readdirSync } from 'node:fs';
import { basename, join } from 'node:path';

const args = process.argv.slice(2);
const JSON_OUT = args.includes('--json');
const v1i = args.indexOf('--v1');
const V1_DIR = v1i >= 0 ? args[v1i + 1] : null;
const files = args.filter((a, i) => !a.startsWith('--') && !(v1i >= 0 && i === v1i + 1));

// lesson file stem -> the first improved version of the notebook it came from (file name in the v1 folder)
const V1_FILE = {
  '0-1-cpp-for-cp': 'Debugging Strategies.md',
  '0-2-complexity': 'Time and Memory Complexity Analysis.md',
  '0-4-elementary-math': 'maths_0.4.md',
  '0-6-stl-toolbox': 'C++ Standard Template Library Reference Notes.md',
  '1-2-prefix-sums': 'Prefix Sum and Partial Sum.md',
  '1-3-two-pointers': 'Two Pointers and Sliding Window Algorithms.md',
  '1-4-binary-search': 'Mastering Binary Search Algorithms.md',
  '1-5-greedy-1': 'Greedy Algorithms and Sweepline.md',
  '1-6-monotonic-stack': 'Monotonic Stack Algorithms.md',
  '1-7-bits': 'Bit Manipulation Fundamentals.md',
  '2-1-number-theory': 'maths_2.1.md',
  '2-2-modular-arithmetic': 'maths_2.2.md',
  '2-3-combinatorics': 'maths_2.3.md',
  '2-4-expected-value': 'The Contribution Technique in Algorithm Optimization.md',
  '3-1-backtracking': 'Recursion and Backtracking.md',
};

const STOP = new Set(`a an the of to in on at for and or is are was were be been it its this that these those with as by from we you
your our their can may will would should not no if then so than but also into onto over under each every any all both one two when where while what
which who how why there here only just more most less least very same other another such like use used using uses get gets got make makes made`.split(/\s+/));

const strip = (s) =>
  s.replace(/!\[[^\]]*\]\([^)]*\)/g, ' ').replace(/\[([^\]]*)\]\([^)]*\)/g, '$1').replace(/\$\$[\s\S]*?\$\$|\$[^$\n]*\$/g, ' M ')
    .replace(/`[^`\n]*`/g, ' C ').replace(/<[^>]+>/g, ' ').replace(/[*_>#|~]/g, ' ').replace(/&lt;|&gt;|&amp;/g, ' ');
const norm = (s) => strip(s).toLowerCase().replace(/[^a-z0-9 ]+/g, ' ').replace(/\s+/g, ' ').trim();
const tokens = (s) => norm(s).split(' ').filter(Boolean);
const sig = (s) => new Set(tokens(s).filter((w) => w.length >= 3 && !STOP.has(w) && w !== 'c' && w !== 'm'));
const jaccard = (a, b) => { let i = 0; for (const x of a) if (b.has(x)) i++; return i / (a.size + b.size - i || 1); };
const overlap = (a, b) => { let i = 0; for (const x of a) if (b.has(x)) i++; return i / (Math.min(a.size, b.size) || 1); };

function parse(text) {
  const raw = text.split('\n');
  let i = 0;
  if (raw[0] === '---') { i = raw.indexOf('---', 1) + 1; }
  const out = [];
  let fence = null, h2 = '', h3 = '';
  for (let n = i; n < raw.length; n++) {
    const line = raw[n];
    const m = /^\s*(`{3,}|~{3,})/.exec(line);
    if (m) {
      if (!fence) fence = m[1];
      else if (m[1][0] === fence[0] && m[1].length >= fence.length && /^\s*[`~]+\s*$/.test(line)) fence = null;
      out.push({ n: n + 1, t: line, kind: 'code', h2, h3 });
      continue;
    }
    if (fence) { out.push({ n: n + 1, t: line, kind: 'code', h2, h3 }); continue; }
    const h = /^(#{1,6})\s+(.*)$/.exec(line);
    if (h) {
      if (h[1].length === 2) { h2 = h[2].trim(); h3 = ''; }
      if (h[1].length === 3) h3 = h[2].trim();
      out.push({ n: n + 1, t: line, kind: 'heading', level: h[1].length, title: h[2].trim(), h2, h3 });
      continue;
    }
    let kind = 'prose';
    if (/^\s*$/.test(line)) kind = 'blank';
    else if (/^\s*import\s/.test(line) || /^\s*<[A-Z][A-Za-z]*[^>]*\/?>\s*$/.test(line)) kind = 'jsx';
    else if (/^\s*!\[/.test(line)) kind = 'image';
    else if (/^\*[^*].*\*\s*$/.test(line) && !/^\*\*/.test(line)) kind = 'caption';
    else if (/^\s*\|.*\|\s*$/.test(line)) kind = 'table';
    out.push({ n: n + 1, t: line, kind, h2, h3 });
  }
  return out;
}

const TAIL = /^(quick revision|check yourself|practice problems|recognition cards)/i; // sections where repeating is fine

function check(file) {
  const text = readFileSync(file, 'utf8');
  const L = parse(text);
  const F = [];
  const add = (rule, sev, n, msg) => F.push({ file, rule, sev, line: n, msg });
  const body = L.filter((x) => !TAIL.test(x.h2) && !TAIL.test(x.title ?? ''));
  const prose = body.filter((x) => x.kind === 'prose' || x.kind === 'table');
  const stem = basename(file).replace(/\.mdx?$/, '');

  // C1 theorem numbers go up in page order, start at 1, have no gaps, and are cited only after they are stated
  {
    const defs = [];
    const seen = new Set();
    for (const x of L) {
      const m = x.kind === 'heading' ? /Theorem (\d+\.\d+\.\d+)/.exec(x.title) : /^\*\*Theorem (\d+\.\d+\.\d+)/.exec(x.t);
      if (m && !seen.has(m[1])) { seen.add(m[1]); defs.push({ id: m[1], n: x.n }); }
    }
    if (defs.length) {
      const k = defs.map((d) => +d.id.split('.')[2]);
      const first = defs[0];
      if (k[0] !== 1) add('C1', 'error', first.n, `the first theorem on the page is ${first.id}; numbering must start at 1`);
      for (let j = 1; j < defs.length; j++) {
        if (k[j] < k[j - 1]) add('C1', 'error', defs[j].n, `Theorem ${defs[j].id} comes after Theorem ${defs[j - 1].id}: numbers must increase down the page`);
        else if (k[j] !== k[j - 1] + 1) add('C1', 'error', defs[j].n, `Theorem ${defs[j].id} follows ${defs[j - 1].id}: a number is skipped`);
      }
      const levels = new Set(L.filter((x) => x.kind === 'heading' && /Theorem \d+\.\d+\.\d+/.test(x.title)).map((x) => x.level));
      if (levels.size > 1) add('C1', 'warn', defs[0].n, `theorem headings use different levels (${[...levels].sort().join(', ')})`);
      const at = new Map(defs.map((d) => [d.id, d.n]));
      for (const x of L) {
        if (x.kind === 'code') continue;
        for (const m of x.t.matchAll(/Theorem (\d+\.\d+\.\d+)/g)) if (at.has(m[1]) && x.n < at.get(m[1])) { add('C1', 'warn', x.n, `Theorem ${m[1]} is cited before it is stated (line ${at.get(m[1])})`); break; }
      }
    }
  }

  // C2 no talk about the notebook, the repository or how the text was checked
  {
    const META = [
      [/\b(his|the author'?s?) (note|notes|notebook|pseudo ?code|drawing|page)\b/i, 'talks about "his note"'],
      [/\bthe notebook\b|\bin the notebook\b|\bnotebook\b/i, 'mentions the notebook'],
      [/\b(in|of|from) the (repository|repo)\b|\bin the repository\b|"0-form"|'0-form'/i, 'mentions the repository'],
      [/\bFabricator\b/, 'mentions Fabricator in prose'],
      [/\b(checked|verified|tested) (by running|against a brute|on \d)/i, 'tells how it was checked'],
      [/\b(run|ran) on the (five|four|three|two|\d+) sample cases\b|\bwritten in that file\b|\bthe file `/i, 'refers to a file the reader cannot open'],
      [/\bform 0\b|\b0-form\b/i, 'calls the fixed window "form 0"'],
      [/\b(Saurabh|my mentor|his mentor)\b/i, 'names the author or mentor'],
    ];
    for (const x of L.filter((y) => y.kind === 'prose' || y.kind === 'table' || y.kind === 'caption' || y.kind === 'image')) {
      const t = x.t.replace(/`[^`\n]*`/g, ' ');
      for (const [re, what] of META) if (re.test(t)) add('C2', 'error', x.n, `${what}  | ${x.t.trim().slice(0, 90)}`);
    }
    for (const x of L.filter((y) => y.kind === 'code')) {
      if (/\/\/\s*new function \(not in Fabricator\)/i.test(x.t)) add('C2', 'warn', x.n, 'code comment "new function (not in Fabricator)" shows the repository to the reader');
    }
  }

  // C3 a statement made twice: exact copies, near copies, and a caption that repeats the line above it
  {
    const paras = [];
    let cur = null;
    for (const x of body) {
      if (x.kind === 'prose' && !/^\s*([-*]|\d+\.)\s/.test(x.t)) {
        if (!cur) cur = { n: x.n, t: '' }; cur.t += ' ' + x.t;
      } else { if (cur) paras.push(cur); cur = null; }
    }
    if (cur) paras.push(cur);
    const P = paras.map((p) => ({ n: p.n, text: p.t.trim(), set: sig(p.t), len: tokens(p.t).length })).filter((p) => p.len >= 8);
    for (let a = 0; a < P.length; a++) for (let b = a + 1; b < P.length; b++) {
      if (P[a].set.size < 5 || P[b].set.size < 5) continue;
      const j = jaccard(P[a].set, P[b].set);
      if (norm(P[a].text) === norm(P[b].text)) add('C3', 'error', P[b].n, `same text as line ${P[a].n}  | ${P[b].text.slice(0, 80)}`);
      else if (j >= 0.8) add('C3', 'warn', P[b].n, `near copy of line ${P[a].n} (${Math.round(j * 100)}% same words)  | ${P[b].text.slice(0, 80)}`);
    }
    for (let i = 0; i < body.length; i++) {
      if (body[i].kind !== 'caption') continue;
      const cap = sig(body[i].t);
      if (cap.size < 4) continue;
      for (let k = Math.max(0, i - 8); k < i; k++) {
        if (body[k].kind !== 'prose' && body[k].kind !== 'table') continue;
        if (overlap(cap, sig(body[k].t)) >= 0.8) { add('C3', 'warn', body[i].n, `caption repeats the text of line ${body[k].n}  | ${body[i].t.trim().slice(0, 80)}`); break; }
      }
    }
  }

  // C4 a claim that comes back three or more times in the body (repeated 6-word phrases, merged)
  {
    const paras = [];
    let cur = '', start = 0;
    for (const x of body.filter((y) => ['prose', 'caption', 'blank', 'table'].includes(y.kind))) {
      if (x.kind === 'prose' || x.kind === 'caption') { if (!cur) start = x.n; cur += ' ' + x.t; if (x.kind === 'caption' || /^\s*[-*]\s/.test(x.t)) { paras.push({ n: start, w: tokens(cur) }); cur = ''; } }
      else if (cur) { paras.push({ n: start, w: tokens(cur) }); cur = ''; }
    }
    if (cur) paras.push({ n: start, w: tokens(cur) });
    const K = 4, map = new Map();
    paras.forEach((p, pi) => {
      const seenHere = new Set();
      for (let i = 0; i + K <= p.w.length; i++) {
        const g = p.w.slice(i, i + K);
        const content = g.filter((w) => !STOP.has(w) && w !== 'c' && w !== 'm').length;
        if (content < 4 || g.some((w) => /^\d+$/.test(w))) continue;
        const key = g.join(' ');
        if (seenHere.has(key)) continue; seenHere.add(key);
        if (!map.has(key)) map.set(key, []);
        map.get(key).push({ pi, i });
      }
    });
    const hot = [...map.entries()].filter(([, v]) => v.length >= 3);
    // merge shingles that overlap in the same paragraphs into one phrase
    const used = new Set();
    const groups = [];
    for (const [key, v] of hot.sort((a, b) => b[1].length - a[1].length)) {
      const id = v.map((x) => x.pi).join(',');
      if (used.has(key)) continue;
      const words = key.split(' ');
      let phrase = words, hits = v;
      // extend to the right while the extended phrase still appears in the same paragraphs
      for (;;) {
        const nxt = hits.map((h) => paras[h.pi].w[h.i + phrase.length]);
        if (nxt.some((w) => w === undefined) || new Set(nxt).size !== 1) break;
        phrase = [...phrase, nxt[0]];
      }
      for (let i = 0; i + K <= phrase.length; i++) used.add(phrase.slice(i, i + K).join(' '));
      groups.push({ phrase: phrase.join(' '), count: new Set(hits.map((h) => h.pi)).size, lines: [...new Set(hits.map((h) => paras[h.pi].n))] });
    }
    for (const g of groups.filter((g) => g.count >= 4).sort((a, b) => b.count - a.count).slice(0, 8))
      add('C4', 'warn', g.lines[0], `"${g.phrase.slice(0, 80)}" appears in ${g.count} places (lines ${g.lines.slice(0, 6).join(', ')})`);
  }

  // C5 headings: no trailing colon, no skipped level, no empty-looking name, no duplicate title at one level
  {
    const hs = L.filter((x) => x.kind === 'heading' && x.level >= 2);
    let prev = 1;
    const seenT = new Map();
    for (const h of hs) {
      if (/:\s*$/.test(h.title)) add('C5', 'error', h.n, `heading ends with a colon: "${h.title}"`);
      if (h.level > prev + 1) add('C5', 'warn', h.n, `heading level jumps from ${prev} to ${h.level}: "${h.title}"`);
      prev = h.level;
      const key = h.level + ':' + h.title.toLowerCase();
      if (seenT.has(key)) add('C5', 'warn', h.n, `heading "${h.title}" also on line ${seenT.get(key)}`); else seenT.set(key, h.n);
      if (/^form \d\b[:\s]*$/i.test(h.title)) add('C5', 'error', h.n, `a form heading must say what the form is: "${h.title}"`);
    }
    const h2s = hs.filter((h) => h.level === 2).map((h) => h.title);
    const need = ['What this note covers'];
    for (const nm of need) if (!h2s.some((t) => new RegExp('^' + nm, 'i').test(t))) add('C5', 'warn', 1, `missing "## ${nm}"`);
  }

  // C6 one list of terms, one table of contents, and it must match the headings
  {
    const gl = L.filter((x) => (x.kind === 'prose' || x.kind === 'heading') && /^\s*(#+\s*)?(words|terms) used in this (note|lesson)/i.test(x.t));
    if (gl.length > 1) add('C6', 'error', gl[1].n, `two lists of terms (lines ${gl.map((g) => g.n).join(', ')}): keep one`);
    const tocLines = L.filter((x) => (x.kind === 'prose' || x.kind === 'heading') && /(sections of this (note|lesson)|table of contents)/i.test(x.t));
    if (tocLines.length > 1) add('C6', 'warn', tocLines[1].n, `two tables of contents (lines ${tocLines.map((g) => g.n).join(', ')})`);
    for (const toc of tocLines) {
      const idx = L.indexOf(toc);
      const items = [];
      for (let k = idx + 1; k < L.length && items.length < 60; k++) {
        const x = L[k];
        if (x.kind === 'blank') { if (items.length) continue; else continue; }
        const li = /^(\s*)[-*]\s+(.*)$/.exec(x.t);
        if (!li) { if (items.length) break; else continue; }
        items.push({ n: x.n, t: li[2] });
      }
      const heads = L.filter((x) => x.kind === 'heading').map((x) => sig(x.title));
      const miss = items.filter((it) => { const s = sig(it.t); return s.size && !heads.some((h) => overlap(s, h) >= 0.5); });
      if (items.length >= 4 && miss.length / items.length > 0.4) add('C6', 'warn', toc.n, `${miss.length} of ${items.length} items of this contents list match no heading, e.g. "${miss[0].t.slice(0, 50)}"`);
    }
  }

  // C7 the sections of the notebook appear in the same order (needs --v1)
  if (V1_DIR && V1_FILE[stem] && existsSync(join(V1_DIR, V1_FILE[stem]))) {
    const v1 = readFileSync(join(V1_DIR, V1_FILE[stem]), 'utf8').split('\n');
    let fence = false; const v1h = [];
    v1.forEach((l) => { if (/^\s*```/.test(l)) fence = !fence; const m = !fence && /^##\s+(.*)$/.exec(l); if (m && !/^(what this note covers|quick revision|practice problems|table of contents)/i.test(m[1])) v1h.push(m[1]); });
    const heads = L.filter((x) => x.kind === 'heading' && x.level >= 2).map((x) => ({ n: x.n, set: sig(x.title.replace(/theorem[^:]*:?/i, '')), title: x.title }));
    let last = 0;
    for (const t of v1h) {
      const s = sig(t);
      if (!s.size) continue;
      let best = null, bs = 0;
      for (const h of heads) { const o = overlap(s, h.set); if (o > bs) { bs = o; best = h; } }
      if (!best || bs < 0.5) { add('C7', 'warn', 1, `notebook section "${t}" has no matching heading in the lesson`); continue; }
      if (best.n < last) add('C7', 'warn', best.n, `notebook section "${t}" is placed before an earlier notebook section (order changed)`);
      last = Math.max(last, best.n);
    }
  }

  // C8 the same family is not counted two ways ("two patterns" and "three forms") and no "form 0"
  {
    const NUM = { two: 2, three: 3, four: 4, five: 5, 2: 2, 3: 3, 4: 4, 5: 5 };
    const found = [];
    for (const x of prose) {
      const t = x.t.replace(/`[^`\n]*`/g, ' ');
      for (const m of t.matchAll(/\b(two|three|four|five|[2-5])\s+(forms|patterns|kinds of (?:tp|two pointers|window)|types of (?:tp|two pointers))\b/gi))
        found.push({ n: x.n, count: NUM[m[1].toLowerCase()], word: m[2].toLowerCase().split(' ')[0], t: m[0] });
    }
    const counts = new Set(found.filter((f) => /^(forms|patterns)$/.test(f.word)).map((f) => f.count));
    if (counts.size > 1) add('C8', 'error', found[0].n, `the family is counted two ways: ${found.map((f) => `"${f.t}" (line ${f.n})`).join(', ')}`);
    const formHeads = L.filter((x) => x.kind === 'heading' && /^form \d+/i.test(x.title));
    if (formHeads.length) {
      const nums = formHeads.map((h) => +/^form (\d+)/i.exec(h.title)[1]);
      const said = found.filter((f) => f.word === 'forms').map((f) => f.count);
      if (said.length && Math.max(...nums) !== said[0]) add('C8', 'warn', formHeads[0].n, `says ${said[0]} forms but has headings for forms ${nums.join(', ')}`);
    }
  }

  // C9 the same small input used in many separate paragraphs (one worked example per idea)
  {
    const lit = new Map();
    let para = 0;
    const seenPara = new Map();
    for (const x of body) {
      if (x.kind === 'blank' || x.kind === 'heading') { para++; continue; }
      if (x.kind === 'code' || x.kind === 'jsx') continue;
      for (const m of x.t.matchAll(/`((?:-?\d+[ ,]+){4,}-?\d+)`|\[((?:-?\d+,\s*){4,}-?\d+)\]/g)) {
        const key = (m[1] ?? m[2]).replace(/[,\s]+/g, ' ').trim();
        if (!seenPara.has(key)) seenPara.set(key, new Set());
        if (!seenPara.get(key).has(para)) { seenPara.get(key).add(para); if (!lit.has(key)) lit.set(key, []); lit.get(key).push(x.n); }
      }
    }
    for (const [k, v] of lit) if (v.length >= 6) add('C9', 'warn', v[0], `input "${k}" is used in ${v.length} separate paragraphs (lines ${v.slice(0, 6).join(', ')}${v.length > 6 ? ', …' : ''}): one worked trace per idea`);
  }

  // C10 side paths ("Another way", "Variant", alternatives) should not outnumber the main line of a section
  {
    const per = new Map();
    for (const x of prose) if (/^(another way|an alternative|alternative|variant|a variant)\b/i.test(x.t.trim())) per.set(x.h2, (per.get(x.h2) ?? 0) + 1);
    for (const [h, c] of per) if (c >= 4) add('C10', 'warn', 1, `${c} side paths ("Another way", "Variant") in section "${h}": group them under one "Going further" heading`);
  }

  // C11 shown code that the text itself calls wrong
  {
    for (const x of prose) if (/^(note|important)\b[: ]/i.test(x.t.trim()) && /\b(bug|wrong|incorrect|never prints|debug|does not (work|print|read)|but the correct answer|gives \d+ .* but)\b/i.test(x.t))
      add('C11', 'warn', x.n, `the text says the listing above is wrong: show the corrected function first, or drop the wrong one  | ${x.t.trim().slice(0, 80)}`);
  }

  // C12 one fixed home for the answers to "what is the cost": a Quick revision that is longer than the lessons' habit
  {
    const qi = L.findIndex((x) => x.kind === 'heading' && /^quick revision/i.test(x.title));
    if (qi >= 0) {
      let c = 0; for (let k = qi + 1; k < L.length; k++) { if (L[k].kind === 'heading' && L[k].level <= 2) break; if (/^\s*[-*]\s/.test(L[k].t)) c++; }
      if (c > 22) add('C12', 'warn', L[qi].n, `Quick revision has ${c} bullets; keep it to one line per idea, in the order of the lesson (about 22 at most)`);
    }
  }

  // C13 several introductions: more than one "key idea"/"second example" before the first technique heading
  {
    const first = L.findIndex((x, i) => x.kind === 'heading' && x.level === 2 && i > 0 && !/^what this note covers|^table of contents/i.test(x.title));
    const intro = L.slice(0, first < 0 ? L.length : first).filter((x) => x.kind === 'prose');
    const words = intro.reduce((s, x) => s + tokens(x.t).length, 0);
    if (words > 650) add('C13', 'warn', 1, `the opening "What this note covers" is ${words} words: say what, why (one example), terms, and stop`);
    const ex = intro.filter((x) => /^(a second example|another example|second example)\b/i.test(x.t.trim()));
    if (ex.length) add('C13', 'warn', ex[0].n, 'a second example inside the opening: move it to the section it belongs to');
  }

  // C14 figures: an image with no alt text or no caption
  {
    for (let i = 0; i < L.length; i++) {
      if (L[i].kind !== 'image') continue;
      const alt = /!\[([^\]]*)\]/.exec(L[i].t)?.[1] ?? '';
      if (!alt.trim()) add('C14', 'error', L[i].n, 'figure without alt text');
      let k = i + 1; while (k < L.length && L[k].kind === 'blank') k++;
      if (!L[k] || L[k].kind !== 'caption') add('C14', 'warn', L[i].n, 'figure without a one-line caption');
    }
  }

  return F;
}

const all = files.flatMap(check);
if (JSON_OUT) console.log(JSON.stringify(all, null, 1));
else {
  for (const f of all) console.log(`${f.file}:${f.line}: ${f.sev} ${f.rule}: ${f.msg}`);
  const e = all.filter((f) => f.sev === 'error').length, w = all.length - e;
  console.log(`${files.length} file(s): ${e} error(s), ${w} warning(s)`);
}
process.exit(all.some((f) => f.sev === 'error') ? 1 : 0);
