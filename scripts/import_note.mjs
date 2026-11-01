#!/usr/bin/env node
// Turns one of the owner's notebook notes (Markdown + figures) into a notes-format lesson (PLAN.md Section 6A).
// Usage: node scripts/import_note.mjs <note.md> <topic-id> [--part <slug>]
//   The note's figures are copied to src/assets/notes/<slug>/ and the image links are rewritten to relative paths.
//   The note's "# Title" line is dropped (the title comes from the frontmatter).
//   If the note has no "## Practice problems" section one is added. The problem ladder of the topic is always added
//   at the end of that section, under "### Problem ladder".
//   The topic data file gets `format: notes`.
import { readFileSync, writeFileSync, existsSync, mkdirSync, copyFileSync } from 'node:fs';
import { dirname, join, resolve, basename } from 'node:path';
import { parse } from 'yaml';

const [, , notePath, topic, ...rest] = process.argv;
if (!notePath || !topic) {
  console.error('usage: node scripts/import_note.mjs <note.md> <topic-id>');
  process.exit(1);
}
const curriculum = parse(readFileSync('src/data/curriculum.yaml', 'utf8'));
const t = curriculum.find((x) => x.id === topic && x.track === 'cp');
if (!t) {
  console.error(`topic ${topic} not found in src/data/curriculum.yaml`);
  process.exit(1);
}
const dash = topic.replace('.', '-');
const lessonPath = `src/content/docs/phase-${t.phase}/${dash}-${t.slug}.mdx`;
const oldFront = existsSync(lessonPath) ? /^---\n([\s\S]*?)\n---/.exec(readFileSync(lessonPath, 'utf8')) : null;
const title = (oldFront && /^title:\s*(.+)$/m.exec(oldFront[1])?.[1]) || JSON.stringify(`${topic} ${t.title}`);
const order = (oldFront && /order:\s*(\d+)/.exec(oldFront[1])?.[1]) || String(t.order);

let text = readFileSync(notePath, 'utf8');
const noteDir = dirname(resolve(notePath));
const imgSlug = `${dash}-${t.slug}`;
const outImgDir = `src/assets/notes/${imgSlug}`;
mkdirSync(outImgDir, { recursive: true });
let copied = 0;
text = text.replace(/!\[(.*?)\]\(([^)\s]+)\)/g, (m, alt, src) => {
  if (/^https?:/.test(src)) return m;
  const from = join(noteDir, src);
  if (!existsSync(from)) throw new Error(`missing image ${from}`);
  const name = basename(src);
  copyFileSync(from, join(outImgDir, name));
  copied++;
  return `![${alt}](../../../assets/notes/${imgSlug}/${name})`;
});
text = text.replace(/^# .*\n+/, '');
// Markdown reads `A[i](i-L+1)` as a link. Outside code fences and math, put a multiplication dot between the two.
let inFence = false;
let inMath = false;
text = text
  .split('\n')
  .map((line) => {
    if (/^\s*(```|~~~)/.test(line)) inFence = !inFence;
    if (inFence) return line;
    if (/^\s*\$\$\s*$/.test(line)) { inMath = !inMath; return line; }
    if (inMath) return line;
    line = line.replace(/\[([^\][]{1,16})\]\((?!https?:|#|\.\.\/|\/)([^)]*)\)/g, '[$1]·($2)');
    // MDX reads { } and a bare < as code. Escape them in prose; leave inline code and $math$ alone.
    return line
      .split(/(`[^`\n]*`|\$\$[^\n]*?\$\$|\$[^$\n]*\$)/)
      .map((part, i) => (i % 2 ? part : part.replace(/\{/g, '\\{').replace(/\}/g, '\\}').replace(/<(?![/a-zA-Z!])/g, '&lt;').replace(/<(?=[a-zA-Z])/g, '&lt;')))
      .join('');
  })
  .join('\n');
if (!/^## Practice problems/m.test(text)) text = `${text.trimEnd()}\n\n## Practice problems\n`;
text = `${text.trimEnd()}\n\n### Problem ladder\n\n<Ladder topic="${topic}" />\n`;

const front = `---\ntitle: ${title}\nsidebar:\n  order: ${order}\ntopic: "${topic}"\n---\nimport TopicHeader from '../../../components/TopicHeader.astro';\nimport Ladder from '../../../components/Ladder.astro';\n\n<TopicHeader topic="${topic}" />\n\n`;
writeFileSync(lessonPath, front + text);

const yamlPath = `src/data/topics/${dash}.yaml`;
let y = readFileSync(yamlPath, 'utf8');
if (/^format:/m.test(y)) y = y.replace(/^format:.*$/m, 'format: notes');
else y = y.replace(/^(id: .*\n)/m, `$1format: notes\n`);
writeFileSync(yamlPath, y);
console.log(`${lessonPath}: written, ${copied} figures copied to ${outImgDir}, ${yamlPath} set to format: notes`);
