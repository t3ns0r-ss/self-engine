#!/usr/bin/env node
// Checks Mermaid diagrams against C++ headers and call traces. Used by the L0.4 kits and units.
//   node uml_check.mjs classes  <diagram.mmd> <header.hpp>...   class diagram against the headers
//   node uml_check.mjs sequence <diagram.mmd> <trace.txt>       sequence diagram against a recorded trace
//   node uml_check.mjs lines    <answers.txt> <expected.txt>    "key: value" answers against the expected ones
//   node uml_check.mjs owners   <answers.txt> <header.hpp>...   "Part: Owner" answers (or "Part: none") against the headers
//   node uml_check.mjs extract  <header.hpp>...                 prints the relationships found in the headers
// Exit 0 when they agree, 1 with one line per difference otherwise, 2 for a usage or syntax problem.
//
// What the header reader understands (the course's style, not all of C++):
//   a member held by value, std::unique_ptr, std::vector, std::optional or std::map  -> composition   Whole *-- Part
//   a member held by pointer, reference, std::shared_ptr or std::weak_ptr           -> aggregation   Whole o-- Part
//   a base class: public Base                                                       -> inheritance   Base <|-- Derived
//   a base class with a pure virtual function (= 0)                                 -> realization   Base <|.. Derived
// A class derived from a std:: class (an exception type) is left out of the model.
// Dependencies (..>) and plain associations (-->) in a diagram are allowed and not compared.
import fs from 'node:fs';
import { fileURLToPath } from 'node:url';

const fail2 = (m) => { console.error(m); process.exit(2); };
const stripComments = (s) => s.replace(/\/\*[\s\S]*?\*\//g, ' ').replace(/\/\/[^\n]*/g, ' ');

// ---------- headers ----------
export function readHeaders(texts) {
  const classes = new Map();                         // name -> {bases:[], body:string}
  for (const raw of texts) {
    const t = stripComments(raw);
    const re = /\b(class|struct)\s+([A-Za-z_]\w*)\s*(?:final\s*)?(:[^{;]*)?\{/g;
    let m;
    while ((m = re.exec(t))) {
      let depth = 1, i = re.lastIndex;
      while (i < t.length && depth > 0) { if (t[i] === '{') depth++; else if (t[i] === '}') depth--; i++; }
      if (/\bstd::/.test(m[3] ?? '')) { re.lastIndex = i; continue; }   // a class derived from a standard class (an exception) is not part of the model
      const bases = [...(m[3] ?? '').matchAll(/(?:public|protected|private)?\s*([A-Za-z_]\w*)\s*(?:,|$)/g)].map((b) => b[1]).filter((b) => !['public', 'protected', 'private', 'virtual'].includes(b));
      classes.set(m[2], { bases, body: t.slice(re.lastIndex, i - 1) });
      re.lastIndex = i;                              // nested classes are not read
    }
  }
  return classes;
}

function statements(body) {
  const out = []; let cur = '', depth = 0, paren = 0;
  for (const ch of body) {
    if (ch === '(') paren++; else if (ch === ')') paren--;
    if (ch === '{') { if (depth === 0) cur += ' {} '; depth++; continue; }
    if (ch === '}') { depth--; if (depth === 0 && cur.includes('(')) { out.push(cur); cur = ''; } continue; }
    if (depth > 0) continue;
    if (ch === ';' && paren === 0) { out.push(cur); cur = ''; continue; }
    cur += ch;
  }
  return out.map((s) => s.replace(/\b(public|private|protected)\s*:/g, ' ').trim()).filter(Boolean);
}

export function relationsOf(classes) {
  const names = new Set(classes.keys()), rel = new Set();
  const pure = (c) => /=\s*0\s*;/.test(classes.get(c).body);
  for (const [name, c] of classes) {
    for (const b of c.bases) if (names.has(b)) rel.add(pure(b) ? `${b} <|.. ${name}` : `${b} <|-- ${name}`);
    for (let s of statements(c.body)) {
      if (s.includes('(') || /^(using|typedef|friend|static|enum|class|struct|template|virtual)\b/.test(s)) continue;
      s = s.replace(/\{\}/g, '').replace(/=.*$/, '').trim();
      const ref = /[*&]|shared_ptr|weak_ptr/.test(s);
      for (const w of s.match(/[A-Za-z_]\w*/g) ?? []) if (names.has(w) && w !== s.split(/\s+/).pop()) rel.add(`${name} ${ref ? 'o--' : '*--'} ${w}`);
    }
  }
  return rel;
}

// ---------- class diagram ----------
const ARROWS = [['<|--', 'L', '<|--'], ['--|>', 'R', '<|--'], ['<|..', 'L', '<|..'], ['..|>', 'R', '<|..'],
                ['*--', 'L', '*--'], ['--*', 'R', '*--'], ['o--', 'L', 'o--'], ['--o', 'R', 'o--']];
export function parseClassDiagram(text) {
  const lines = text.split('\n').map((l) => l.trim()).filter((l) => l && !l.startsWith('%%'));
  if (lines[0] !== 'classDiagram') fail2('the diagram must start with the line: classDiagram');
  const classes = new Set(), rel = new Set();
  for (const l of lines.slice(1)) {
    const mc = /^class\s+([A-Za-z_]\w*)\s*(\{.*)?$/.exec(l);
    if (mc) { classes.add(mc[1]); continue; }
    if (/^[}<]|^<<|^\w+\s*:\s|^direction\b|^note\b|^\+|^-|^#|^~/.test(l) && !/[.\-]{2}/.test(l)) continue;
    const m = /^([A-Za-z_]\w*)\s*(?:"[^"]*"\s*)?(<\|--|--\|>|<\|\.\.|\.\.\|>|\*--|--\*|o--|--o|\.\.>|<\.\.|-->|<--|--|\.\.)\s*(?:"[^"]*"\s*)?([A-Za-z_]\w*)\s*(?::.*)?$/.exec(l);
    if (!m) fail2(`cannot read this line of the class diagram: ${l}`);
    classes.add(m[1]); classes.add(m[3]);
    const a = ARROWS.find((x) => x[0] === m[2]);
    if (a) rel.add(a[1] === 'L' ? `${m[1]} ${a[2]} ${m[3]}` : `${m[3]} ${a[2]} ${m[1]}`);
  }
  return { classes, rel };
}

export function checkClasses(diagramText, headerTexts) {
  const code = readHeaders(headerTexts), want = relationsOf(code), d = parseClassDiagram(diagramText), errs = [];
  for (const c of code.keys()) if (!d.classes.has(c)) errs.push(`class ${c} is in the headers but not in the diagram`);
  for (const c of d.classes) if (!code.has(c)) errs.push(`class ${c} is in the diagram but not in the headers`);
  for (const r of want) if (!d.rel.has(r)) {
    const [a, k, b] = r.split(' ');
    const other = [...d.rel].find((x) => { const p = x.split(' '); return (p[0] === a && p[2] === b) || (p[0] === b && p[2] === a); });
    errs.push(other ? `${a} and ${b}: the headers say "${r}" but the diagram says "${other}"` : `missing from the diagram: ${r}`);
  }
  for (const r of d.rel) if (!want.has(r)) {
    const [a, , b] = r.split(' ');
    if (![...want].some((x) => { const p = x.split(' '); return (p[0] === a && p[2] === b) || (p[0] === b && p[2] === a); })) errs.push(`not in the headers: ${r}`);
  }
  return errs;
}

// ---------- sequence diagram ----------
export function parseSequence(text) {
  const lines = text.split('\n').map((l) => l.trim()).filter((l) => l && !l.startsWith('%%'));
  if (lines[0] !== 'sequenceDiagram') fail2('the diagram must start with the line: sequenceDiagram');
  // tree: block = list of items; item = {msg:"A->B: f"} | {alt:[block,...]}
  const stack = [{ kind: 'top', branches: [[]] }];
  const cur = () => stack[stack.length - 1].branches[stack[stack.length - 1].branches.length - 1];
  for (const l of lines.slice(1)) {
    if (/^(participant|actor|autonumber|title|Note|activate|deactivate|box|end box)\b/.test(l)) continue;
    const blk = /^(alt|opt|loop|par|critical|break|rect)\b/.exec(l);
    if (blk) { stack.push({ kind: blk[1], branches: [[]] }); continue; }
    if (/^(else|and|option)\b/.test(l)) { stack[stack.length - 1].branches.push([]); continue; }
    if (l === 'end') { const b = stack.pop(); if (!stack.length) fail2('"end" without a block'); cur().push({ block: b.kind, branches: b.branches }); continue; }
    const m = /^([A-Za-z_]\w*)\s*(-->>|--x|--\)|->>|-x|-\)|->|-->)\s*[+-]?([A-Za-z_]\w*)\s*:\s*(.*)$/.exec(l);
    if (!m) fail2(`cannot read this line of the sequence diagram: ${l}`);
    if (m[2].startsWith('--')) continue;            // a dashed arrow is a return, not a call
    cur().push({ msg: `${m[1]}->${m[3]}: ${m[4].replace(/\(.*\)\s*$/, '').replace(/\s+/g, ' ').trim()}` });
  }
  if (stack.length !== 1) fail2('a block (alt, opt, loop) is not closed with "end"');
  return stack[0].branches[0];
}
function expand(block) {                              // every message list the diagram allows
  let acc = [[]];
  for (const it of block) {
    let opts;
    if (it.msg) opts = [[it.msg]];
    else {
      const bs = it.branches.flatMap(expand);
      opts = ['opt', 'loop', 'break'].includes(it.block) ? [[], ...bs] : bs;
    }
    acc = acc.flatMap((a) => opts.map((o) => [...a, ...o]));
  }
  return acc;
}
export function checkSequence(diagramText, traceText) {
  const trace = traceText.split('\n').map((l) => l.trim()).filter(Boolean);
  const allowed = expand(parseSequence(diagramText));
  if (allowed.some((a) => a.length === trace.length && a.every((x, i) => x === trace[i]))) return [];
  // report the first difference against the closest allowed list
  let best = allowed[0] ?? [], score = -1;
  for (const a of allowed) { let k = 0; while (k < a.length && k < trace.length && a[k] === trace[k]) k++; if (k > score) { score = k; best = a; } }
  const errs = [];
  if (score < trace.length) errs.push(`call ${score + 1} of the run is "${trace[score]}" but the diagram ${best[score] ? `shows "${best[score]}"` : 'ends before it'}`);
  else errs.push(`the diagram has ${best.length - trace.length} more call(s) than the run, starting with "${best[trace.length]}"`);
  return errs;
}

// ---------- answers ----------
export function checkLines(answers, expected) {
  const parse = (t) => new Map(t.split('\n').map((l) => l.trim()).filter((l) => l && !l.startsWith('#')).map((l) => { const i = l.indexOf(':'); return i < 0 ? [l.toLowerCase(), ''] : [l.slice(0, i).trim().toLowerCase(), l.slice(i + 1).trim().toLowerCase()]; }));
  const a = parse(answers), e = parse(expected), errs = [];
  for (const [k, v] of e) { if (!a.has(k)) errs.push(`no answer for "${k}"`); else if (a.get(k) !== v) errs.push(`"${k}": answered "${a.get(k)}"`); }
  return errs;
}

export function ownersExpected(classes) {
  const owner = new Map([...classes.keys()].map((c) => [c, 'none']));
  for (const r of relationsOf(classes)) { const [a, k, b] = r.split(' '); if (k === '*--') owner.set(b, a); }
  return [...owner].map(([c, o]) => `${c}: ${o}`).join('\n');
}

// ---------- command line ----------
if (process.argv[1] && fs.realpathSync(process.argv[1]) === fileURLToPath(import.meta.url)) {   // run as a program, also through a symlink
  const [mode, a, ...rest] = process.argv.slice(2);
  const rd = (p) => { try { return fs.readFileSync(p, 'utf8'); } catch { fail2(`cannot read ${p}`); } };
  let errs;
  if (mode === 'classes' && a && rest.length) errs = checkClasses(rd(a), rest.map(rd));
  else if (mode === 'sequence' && a && rest.length === 1) errs = checkSequence(rd(a), rd(rest[0]));
  else if (mode === 'lines' && a && rest.length === 1) errs = checkLines(rd(a), rd(rest[0]));
  else if (mode === 'owners' && a && rest.length) errs = checkLines(rd(a), ownersExpected(readHeaders(rest.map(rd))));
  else if (mode === 'extract' && a) { console.log([...relationsOf(readHeaders([a, ...rest].map(rd)))].sort().join('\n')); process.exit(0); }
  else fail2('usage: uml_check.mjs classes|sequence|lines|owners|extract …  (see the top of the file)');
  if (errs.length) { console.error(errs.join('\n')); process.exit(1); }
  console.log('ok');
}
