#!/usr/bin/env node
// Depth lint for the notes lessons.
//  1. Word count: prose words must reach minProseRatio x the first improved version (scripts/lesson_targets.json).
//     Code words are reported only.
//  2. Sections: every ## / ### section that contains a code block must also say something about
//     how it runs or what it costs or where it goes wrong (trace, dry run, T.C./time complexity, S.C., O(...), Note:, mistake, pitfall, bug).
// Usage: node scripts/check_depth.mjs [--report] [file.mdx ...]   (no files = every lesson in targets; --report never fails)
import { readFileSync, readdirSync } from 'node:fs';
import { join, basename } from 'node:path';

const REPORT = process.argv.includes('--report');
const T = JSON.parse(readFileSync(new URL('./lesson_targets.json', import.meta.url), 'utf8'));
const root = new URL('../src/content/docs/', import.meta.url).pathname;
const all = {};
for (const ph of readdirSync(root)) {
  if (!ph.startsWith('phase-')) continue;
  for (const f of readdirSync(join(root, ph))) if (f.endsWith('.mdx')) all[f.replace(/\.mdx$/, '')] = join(root, ph, f);
}
const args = process.argv.slice(2).filter((a) => a !== '--report');
const wanted = args.length ? new Set(args.map((a) => basename(a).replace(/\.mdx$/, ''))) : null;

function split(text) {
  text = text.replace(/^---[\s\S]*?\n---\n/, '');
  let prose = 0, code = 0, fence = false;
  const sections = [];
  let cur = { title: '(top)', hasCode: false, text: '' };
  for (const line of text.split('\n')) {
    if (/^\s*(```|~~~)/.test(line)) {
      fence = !fence;
      if (fence) cur.hasCode = true;
      continue;
    }
    const n = (line.match(/\S+/g) || []).length;
    if (fence) { code += n; cur.text += line + '\n'; continue; }
    const h = /^(#{2,3})\s+(.*)/.exec(line);
    if (h) { sections.push(cur); cur = { title: h[2], hasCode: false, text: '' }; }
    prose += n;
    cur.text += line + '\n';
  }
  sections.push(cur);
  return { prose, code, sections };
}

const SIGNAL = /trace|dry run|dry-run|walk ?through|T\.?C\.?\b|S\.?C\.?\b|time complexity|space complexity|O\(|^Note:|\bmistake|pitfall|\bbug\b|careful|overflow|wrong/im;
const SKIP = /^(Quick revision|Practice problems|Problem ladder|What this note covers|Table of contents|Contents)/i;

let fail = 0;
const stats = {};
for (const [name, path] of Object.entries(all)) {
  if (wanted && !wanted.has(name)) continue;
  const lesson = T.lessons[name];
  const group = Object.entries(T.groups).find(([, g]) => g.files.includes(name));
  if (!lesson && !group) continue;
  const s = split(readFileSync(path, 'utf8'));
  if (lesson) {
    const need = Math.ceil(lesson.v1Prose * T.minProseRatio);
    const ok = s.prose >= need;
    console.log(`${ok ? 'ok  ' : 'LOW '} ${name}: prose ${s.prose} / target ${need} (v1 ${lesson.v1Prose}), code ${s.code} (v1 ${lesson.v1Code})`);
    if (!ok) fail++;
  } else {
    (stats[group[0]] ??= { prose: 0, code: 0, names: [] });
    stats[group[0]].prose += s.prose; stats[group[0]].code += s.code; stats[group[0]].names.push(name);
  }
  for (const sec of s.sections) {
    if (!sec.hasCode || SKIP.test(sec.title)) continue;
    if (!SIGNAL.test(sec.text.replace(/```[\s\S]*?```/g, ''))) {
      console.log(`  section without trace/cost/mistake line: ${name} > ${sec.title}`);
      fail++;
    }
  }
}
for (const [g, st] of Object.entries(stats)) {
  const need = Math.ceil(T.groups[g].v1Prose * T.minProseRatio);
  const ok = st.prose >= need;
  console.log(`${ok ? 'ok  ' : 'LOW '} group ${g} (${st.names.join(', ')}): prose ${st.prose} / target ${need}, code ${st.code} (v1 ${T.groups[g].v1Code})`);
  if (!ok) fail++;
}
console.log(fail ? `${fail} depth problem(s)` : 'depth check clean');
process.exit(fail && !REPORT ? 1 : 0);
