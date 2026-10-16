#!/usr/bin/env node
// Usage: node scripts/new_topic.mjs <topic-id>        e.g. node scripts/new_topic.mjs H4.2
// Creates, from templates/topic/ and the curriculum row (and INVENTORY.yaml, if it lists the topic):
//   src/content/docs/{track}/phase-{n}/{id-dash}-{slug}.mdx   lesson skeleton with every required heading
//   src/data/topics/{id-dash}.yaml                            data file with `uses` prefilled from `requires`
//   src/data/exercises/{id-dash}.yaml                         exercise stubs from the inventory
//   code/{id}/  notes/design/{id}.md
// Never overwrites: stops if any of these already exists. Every TODO it writes must be replaced
// before the build passes (Section 12, D18).
import fs from 'node:fs';
import path from 'node:path';
import { parse } from 'yaml';

const root = path.resolve(path.dirname(new URL(import.meta.url).pathname), '..');
const id = process.argv[2];
if (!id || !/^[LH]\d\.\d+$/.test(id)) { console.error('usage: new_topic.mjs <topic-id like L2.1 or H4.2>'); process.exit(2); }

const rows = parse(fs.readFileSync(path.join(root, 'src/data/curriculum.yaml'), 'utf8'));
const row = rows.find((r) => r.id === id);
if (!row) { console.error(`topic ${id} is not in src/data/curriculum.yaml`); process.exit(1); }

const track = row.track;                       // 'lld' | 'hld'
const dash = id.replace('.', '-');
const lessonDir = path.join(root, 'src/content/docs', track, `phase-${row.phase}`);
const files = {
  lesson: path.join(lessonDir, `${dash}-${row.slug}.mdx`),
  topic: path.join(root, 'src/data/topics', `${dash}.yaml`),
  exercises: path.join(root, 'src/data/exercises', `${dash}.yaml`),
  notes: path.join(root, 'notes/design', `${id}.md`),
};
for (const f of Object.values(files)) {
  if (fs.existsSync(f)) { console.error(`already exists: ${path.relative(root, f)}`); process.exit(1); }
}

// Relative import prefix from the lesson folder to src/components/, ending in '/'.
const comp = path.relative(lessonDir, path.join(root, 'src/components')).split(path.sep).join('/') + '/';
const fill = (text, vars) => text.replace(/\{\{(\w+)\}\}/g, (m, k) => (k in vars ? vars[k] : m));
const tpl = (name) => fs.readFileSync(path.join(root, 'templates/topic', name), 'utf8');

const uses = (row.requires ?? []).map((t) => `  - {topic: "${t}", what: "TODO"}`).join('\n') || '  []';
const isLab = track === 'hld' && row.lab && row.lab !== 'none';

// Exercise stubs from the inventory, if present.
let stubs = '  []';
const invPath = path.join(root, 'src/data/exercises/INVENTORY.yaml');
if (fs.existsSync(invPath)) {
  const inv = parse(fs.readFileSync(invPath, 'utf8'))?.topics?.[id];
  if (inv) {
    const out = [];
    for (const r of inv.ladder ?? []) {
      const kit = track === 'hld' ? `${id}/lab/rung-${r.rung}` : `${id}/ladder/rung-${r.rung}`;
      out.push(`  - id: rung-${r.rung}
    role: ladder
    type: ${track === 'hld' ? 'lab' : 'change_ladder'}
    title: "TODO"
    prompt: "TODO"
    card: ${r.card ? r.card : 'null'}
    rung: ${r.rung}
    new_force: ${JSON.stringify(r.new_force)}
    needs_new_structure: ${r.needs_new_structure}
    checkers: [{kind: kit, path: "${kit}"}]
    reference: "reference/${kit}"
    hints: ["TODO", "TODO", "TODO"]
    techniques: ["${id}"]
    checked_on: "TODO"`);
    }
    (inv.drill ?? []).forEach((d, i) => {
      const answer = d.answer === 'none'
        ? '{kind: none, simplest: "TODO", why: "TODO"}'
        : `{kind: card, card: {topic: "${d.answer.topic}", card: ${d.answer.card}}, property: "TODO", why_others_fail: "TODO"}`;
      out.push(`  - id: r-${i + 1}
    role: drill
    type: recognise
    title: "TODO"
    prompt: "TODO (stub: ${String(d.stub).replace(/"/g, "'")})"
    answer: ${answer}
    checkers: []
    techniques: ["${id}"]
    checked_on: "TODO"`);
    });
    if (out.length) stubs = out.join('\n');
  }
}

const vars = {
  ID: id, TITLE: row.title, ORDER: String(row.order), TRACK: track, C: comp, USES: uses, STUBS: stubs,
  LAB_RUNNER: isLab ? `<LabRunner unit="${id}/lab-TODO" />\n` : '',
};
fs.mkdirSync(lessonDir, { recursive: true });
for (const d of ['src/data/topics', 'src/data/exercises', 'notes/design', `code/${id}`]) fs.mkdirSync(path.join(root, d), { recursive: true });
fs.writeFileSync(files.lesson, fill(tpl('lesson.mdx'), vars));
fs.writeFileSync(files.topic, fill(tpl('topic.yaml'), vars));
fs.writeFileSync(files.exercises, fill(tpl('exercises.yaml'), vars));
fs.writeFileSync(files.notes, `# ${id} ${row.title}: private notes\n\n## Sources checked\n\n## Calibration\n\n## Dropped ideas\n`);
for (const f of Object.values(files)) console.log('created', path.relative(root, f));
console.log('created', `code/${id}/`);
