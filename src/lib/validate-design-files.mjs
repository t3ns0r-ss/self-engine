// Cross-file checks for the LLD and HLD data files (DESIGN_TRACKS_PLAN.md Section 12: D2-D9, D12-D19).
// Pure over parsed data plus read-only file lookups through `fsx` (so tests can use a temporary tree).
import { existsSync, readFileSync, readdirSync, statSync } from 'node:fs';
import { join } from 'node:path';

export const DESIGN_HEADINGS = [
  '## 1. Why this topic exists', '## 2. Prerequisites and scope', '### What you need', '### What this topic does not cover',
  '## 3. Definitions', '## 4. Principles and claims', '## 5. Recognition Cards', '## 6. Reference designs',
  '## 7. Mistake catalogue', '## 8. Worked examples', '## 9. Exercise ladder', '## 10. Recognition drill',
  '## 11. Look-alike pairs', '## 12. Self-test questions', '## 13. Checkpoint', '## 14. Decision map update',
];
export const DESIGN_STEPS = [
  '#### Step 1: Numbers', '#### Step 2: Wording → candidate structures', '#### Step 3: Property check → decision',
  '#### Step 4: Design', '#### Step 5: Code or calculation', '#### Step 6: Decision record',
];

/** Allowed `checkers` kinds per track and exercise type (Section 10.1). Each entry: required kinds in order, then optional repeats. */
const CHECKER_RULES = {
  lld: { recognise: [[]], refactor: [['kit']], build: [['kit'], ['kit', 'rubric']], change_ladder: [['kit']], mock: [['kit', 'rubric']] },
  hld: {
    recognise: [[]], estimate: [['numeric+']], lab: [['kit'], ['kit', 'numeric+']], deep_dive: [['rubric'], ['numeric+', 'rubric']],
    scale_ladder: [['numeric+'], ['numeric+', 'rubric']], failure: [['rubric']], mock: [['rubric'], ['numeric+', 'rubric']],
  },
};
function checkerShape(kinds) {          // collapse runs of numeric into "numeric+"
  const out = [];
  for (const k of kinds) if (!(k === 'numeric' && out[out.length - 1] === 'numeric+')) out.push(k === 'numeric' ? 'numeric+' : k);
  return out.join(',');
}

const hasTodo = (s) => /\bTODO\b|\{\{\w+\}\}/.test(s);
const words = (s) => s.trim().split(/\s+/).filter(Boolean).length;

/** Real filesystem access, rooted at the repository. */
export const realFs = (root) => ({
  root,
  exists: (p) => existsSync(join(root, p)),
  read: (p) => readFileSync(join(root, p), 'utf8'),
  isDir: (p) => existsSync(join(root, p)) && statSync(join(root, p)).isDirectory(),
  list: (p) => (existsSync(join(root, p)) ? readdirSync(join(root, p), { recursive: true }).map(String) : []),
});

/**
 * @param {object} d  designData from loadAll(), plus `curriculum` rows as `rows`
 * @param {object} fsx file access (see realFs)
 * @param {{products?: string[], rows: Array}} opts
 */
export function validateDesignFiles(d, fsx, { rows, products = [] }) {
  const errors = [];
  const err = (f, m) => errors.push(`${f}: ${m}`);
  const rowById = new Map(rows.map((r) => [r.id, r]));
  const rubricIds = new Set((d.rubrics ?? []).map((r) => r.id));
  const constants = new Set((d.constants ?? []).map((c) => c.id));
  const cardsByTopic = {};
  for (const [id, t] of Object.entries(d.topics ?? {})) cardsByTopic[id] = new Set(t.cards.map((c) => c.id));

  const earlierOrSame = (from, to) => {
    const a = rowById.get(from), b = rowById.get(to);
    return a && b && a.track === b.track && b.order <= a.order;
  };

  for (const [id, t] of Object.entries(d.topics ?? {})) {
    const F = `src/data/topics/${id.replace('.', '-')}.yaml`;
    const row = rowById.get(id);
    if (!row) { err(F, `topic ${id} is not in curriculum.yaml`); continue; }
    if (t.track !== row.track) err(F, `track ${t.track} does not match curriculum track ${row.track}`);
    const claimIds = new Set(t.claims.map((c) => c.id));

    // D3/D4: references resolve inside the track, never forward; uses covers requires
    for (const u of t.uses) if (!earlierOrSame(id, u.topic) || u.topic === id) err(F, `uses ${u.topic}: not an earlier topic of track ${row.track}`);
    for (const q of row.requires) if (!t.uses.some((u) => u.topic === q)) err(F, `requires ${q} but uses does not list it`);

    // claims
    t.claims.forEach((c) => {
      if (!c.id.startsWith(`${id}.`)) err(F, `claim ${c.id} does not belong to topic ${id}`);
      const unitOf = (u) => d.units?.[u];
      if (c.kind === 'measured') {
        const domains = new Set(c.evidence.map((u) => unitOf(u)).filter((u) => u?.kind === 'pattern').map((u) => u.domain));
        if (domains.size < 2) err(F, `claim ${c.id} is measured and needs pattern units from at least 2 domains`);
      } else if (c.kind === 'experimented') {
        for (const e of c.evidence) {
          const rec = d.experiments?.[e];
          if (!rec) { err(F, `claim ${c.id}: experiment ${e} has no record in src/data/experiments/`); continue; }
          const rf = `${rec.program}/${rec.results_file}`;
          if (!rec.results_file.endsWith('-labserver.txt')) err(F, `experiment ${e}: results file must be a *-labserver.txt full run (D19)`);
          else if (!fsx.exists(rf)) err(F, `experiment ${e}: results file ${rf} does not exist`);
          else { const t2 = fsx.read(rf); if (/FAIL shape/.test(t2) || !/PASS shape/.test(t2)) err(F, `experiment ${e}: ${rf} must show every shape check as PASS`); }
        }
      } else if (c.kind !== 'cited') {
        for (const u of c.evidence) {
          const p = `code/${u}`;
          if (!fsx.isDir(p)) { err(F, `claim ${c.id}: evidence unit code/${u} does not exist`); continue; }
          if (c.kind === 'computed' && !(fsx.exists(`${p}/main.go`) && fsx.exists(`${p}/expected.txt`))) err(F, `claim ${c.id}: computed evidence ${u} must be a Go calc program with expected.txt`);
        }
        if (!c.evidence.length) err(F, `claim ${c.id}: ${c.kind} claims need evidence`);
      }
    });

    // cards
    for (const c of t.cards) {
      const C = `${F} card ${c.id}`;
      if (!claimIds.has(c.from_claim)) err(C, `from_claim ${c.from_claim} is not a claim of ${id}`);
      if (row.track === 'lld' && !c.force) err(C, 'LLD cards need force');
      if (row.track === 'hld') {
        if (!c.need) err(C, 'HLD cards need need');
        if (!c.lab) err(C, 'HLD cards need lab {unit, holds_test, breaks_test}');
        else {
          const lab = d.labs?.[c.lab.unit];
          if (!lab) err(C, `lab unit ${c.lab.unit} has no lab.yaml`);
          else {
            if (!lab.holds.includes(c.lab.holds_test)) err(C, `holds_test ${c.lab.holds_test} is not in ${c.lab.unit}/lab.yaml holds`);
            if (!lab.breaks.includes(c.lab.breaks_test)) err(C, `breaks_test ${c.lab.breaks_test} is not in ${c.lab.unit}/lab.yaml breaks`);
          }
        }
        const text = JSON.stringify(c).toLowerCase();                       // D9
        for (const p of products) if (new RegExp(`\\b${p.toLowerCase().replace(/[.*+?^${}()|[\]\\]/g, '\\$&')}\\b`).test(text)) err(C, `names the product "${p}" (D9)`);
      }
      if (row.kind === 'measured' && !c.trade_off_table) err(C, 'measured topics need trade_off_table');
      for (const l of c.lookalikes) if (!earlierOrSame(id, l.tool.topic) || !cardsByTopic[l.tool.topic]?.has(l.tool.card)) err(C, `look-alike ${l.tool.topic}/${l.tool.card} does not resolve to a card of this or an earlier topic`);
      if (!c.kill_signals.some((k) => /\d/.test(k))) err(C, 'at least one kill signal needs numbers (over-engineering signal)');
    }
    if (row.kind !== 'capstone') {
      const nMax = row.kind === 'light' ? 2 : 4;
      if (t.cards.length < 1 || t.cards.length > nMax) err(F, `${t.cards.length} cards, expected 1-${nMax} (D2)`);
    }
    for (const dm of t.decision_map) for (const o of dm.over) if (o.topic && !earlierOrSame(id, o.topic)) err(F, `decision_map refers to later topic ${o.topic}`);
    t.lookalike_pairs.forEach((p) => {
      for (const tool of [p.a_tool, p.b_tool]) if (typeof tool === 'object' && (!earlierOrSame(id, tool.topic) || !cardsByTopic[tool.topic]?.has(tool.card))) err(F, `look-alike pair refers to unknown or later card ${tool.topic}/${tool.card}`);
    });
    // D15
    if (row.track === 'hld' && !/^none/.test(row.lab)) {
      const labs = Object.keys(d.labs ?? {}).filter((k) => k.startsWith(`${id}/`));
      if (!labs.length) err(F, `HLD topic ${id} has no lab folder with lab.yaml (D15)`);
      for (const k of labs) {
        const lab = d.labs[k];
        if (!fsx.exists(`code/${k}/${lab.run}`)) err(F, `lab ${k}: run file ${lab.run} does not exist`);
        const tests = fsx.list(`code/${k}`).filter((f) => f.endsWith('_test.go')).map((f) => fsx.read(`code/${k}/${f}`)).join('\n');
        for (const n of [...lab.holds, ...lab.breaks]) if (!new RegExp(`func ${n}\\(`).test(tests)) err(F, `lab ${k}: test ${n} is not defined as func ${n}( in the lab package (D15)`);
        for (const s of lab.stacks) if (!row.infra.includes(s)) err(F, `lab ${k}: stack ${s} is not in the curriculum infra list`);
      }
    }
  }

  // exercises
  const seenGlobal = new Set();
  for (const [topic, file] of Object.entries(d.exercises ?? {})) {
    const F = `src/data/exercises/${topic.replace('.', '-')}.yaml`;
    const row = rowById.get(topic);
    if (!row) { err(F, `topic ${topic} is not in curriculum.yaml`); continue; }
    const rules = CHECKER_RULES[row.track];
    const ladder = file.exercises.filter((e) => e.role === 'ladder');
    for (const e of file.exercises) {
      const G = `${topic}/${e.id}`;
      const E = `${F} ${G}`;
      if (seenGlobal.has(G)) err(E, 'duplicate exercise id');
      seenGlobal.add(G);
      const types = row.track === 'lld' ? Object.keys(CHECKER_RULES.lld) : Object.keys(CHECKER_RULES.hld);
      if (!types.includes(e.type)) { err(E, `type ${e.type} is not allowed in track ${row.track}`); continue; }
      const shape = checkerShape(e.checkers.map((c) => c.kind));
      const allowed = rules[e.type].map((a) => a.join(','));
      if (!allowed.includes(shape)) err(E, `checkers [${shape}] are not allowed for ${row.track} ${e.type} (allowed: ${allowed.map((a) => `[${a}]`).join(' or ')}) (D7)`);
      for (const c of e.checkers) {
        if (c.kind === 'kit') {
          if (!fsx.isDir(`exercises/${c.path}`)) err(E, `kit exercises/${c.path} does not exist (D7)`);
          if (!fsx.isDir(`reference/${c.path}`)) err(E, `reference reference/${c.path} does not exist (D7)`);
        } else if (c.kind === 'rubric' && !rubricIds.has(c.id)) err(E, `rubric ${c.id} does not exist (D7)`);
        else if (c.kind === 'numeric') {
          const p = `code/${c.calc}`;
          if (!fsx.exists(`${p}/expected.txt`)) err(E, `calc program ${c.calc} has no expected.txt (D7)`);
          else if (!new RegExp(`^${c.key} = `, 'm').test(fsx.read(`${p}/expected.txt`))) err(E, `calc program ${c.calc} does not print key ${c.key} (D7)`);
        }
      }
      if (['build', 'deep_dive', 'scale_ladder', 'mock'].includes(e.type) || (e.type === 'lab' && e.rung === 1)) {
        const cl = e.clarifying ?? [];
        if (cl.length < 4 || cl.filter((q) => q.critical).length < 2) err(E, 'clarifying needs at least 4 entries, at least 2 critical (D2)');
      }
      if (['checkpoint', 'exam'].includes(e.role) || e.type === 'mock') if (!e.time_limit_minutes) err(E, 'time_limit_minutes is required');
      if (e.role === 'ladder') {
        if (!e.new_force) err(E, 'ladder rungs need exactly one new_force (D3)');
        if (e.needs_new_structure === undefined) err(E, 'ladder rungs need needs_new_structure');
        if (e.hints?.length !== 3) err(E, 'ladder rungs need exactly 3 hints');
        if (e.checkers[0]?.kind === 'kit' && e.checkers[0].path !== `${topic}/${row.track === 'hld' ? 'lab' : 'ladder'}/rung-${e.rung}`) err(E, `kit path ${e.checkers[0].path} does not follow {topic}/${row.track === 'hld' ? 'lab' : 'ladder'}/rung-${e.rung}`);
      }
      if (e.type === 'recognise' && !e.answer) err(E, 'recognise exercises need an answer');
      if (e.answer?.kind === 'card') {
        const a = e.answer.card;
        if (!earlierOrSame(topic, a.topic) || !cardsByTopic[a.topic]?.has(a.card)) err(E, `answer card ${a.topic}/${a.card} does not resolve to a card of this or an earlier topic (D3)`);
      }
    }
    if (ladder.length && !ladder.some((e) => e.needs_new_structure === false)) err(F, 'the ladder needs a rung with needs_new_structure: false (D3)');
    // drill quotas (Section 8.10)
    const drill = file.exercises.filter((e) => e.role === 'drill' && e.type === 'recognise');
    if (drill.length) {
      const none = drill.filter((e) => e.answer?.kind === 'none').length;
      if (none < Math.ceil(drill.length * 0.2)) err(F, `drill has ${none} "none" items of ${drill.length}; at least 20% (rounded up) are required (D3)`);
      const earlierCards = Object.entries(cardsByTopic).filter(([t]) => t !== topic && earlierOrSame(topic, t)).reduce((n, [, s]) => n + s.size, 0);
      const fromEarlier = drill.filter((e) => e.answer?.kind === 'card' && e.answer.card.topic !== topic).length;
      if (fromEarlier < Math.min(3, earlierCards)) err(F, `drill has ${fromEarlier} items answered by an earlier card; at least ${Math.min(3, earlierCards)} are required (D3)`);
    }
  }

  // D18: no placeholders in finished data
  for (const dir of ['src/data/topics', 'src/data/exercises', 'src/content/docs/lld', 'src/content/docs/hld', 'exercises', 'reference']) {
    for (const f of fsx.list(dir)) {
      if (!/\.(ya?ml|md|go|hpp|cpp|mdx|txt|sh)$/.test(f)) continue;
      if (/^[0-9]/.test(f.split('/').pop() ?? '') && dir === 'src/data/topics') continue;     // CP topic files
      if (fsx.isDir(`${dir}/${f}`)) continue;
      if (hasTodo(fsx.read(`${dir}/${f}`))) err(`${dir}/${f}`, 'contains TODO or an unfilled {{…}} marker (D18)');
    }
  }
  return errors;
}

/** D16/D17: Go and C++ hygiene over the code tree. */
export function validateCodeHygiene(fsx, { l6Prefix = 'L6.' } = {}) {
  const errors = [];
  const err = (f, m) => errors.push(`${f}: ${m}`);
  for (const f of fsx.list('code')) {
    const segs = f.split('/');
    const dirs = fsx.isDir(`code/${f}`) ? segs : segs.slice(0, -1);
    if (dirs.some((seg) => /^[_.]/.test(seg) && seg !== '.build')) err(`code/${f}`, 'folder name starts with _ or . (go ./... would skip it) (D16)');
  }
  for (const root of ['code', 'exercises']) {
    for (const f of fsx.list(root)) {
      const name = f.split('/').pop();
      if (name === 'sanitizer') {
        const top = f.split('/')[0];
        if (!top.startsWith(l6Prefix)) err(`${root}/${f}`, `a sanitizer file is only for ${l6Prefix}* units and kits (D17)`);
      }
      if (name === 'test.sh' && fsx.isDir(`${root}/${f}`) === false) {
        const body = fsx.read(`${root}/${f}`);
        if (/g\+\+/.test(body) && /-std=|-fsanitize|-W(all|extra|error)/.test(body)) err(`${root}/${f}`, 'sets compiler flags directly; use code/shared/cpp/cxxflags.sh (D17)');
      }
    }
  }
  return errors;
}

/** D13/D8: lesson headings and quote length for one design lesson. */
export function validateDesignLesson(text, file) {
  const errors = [];
  const stripped = text.replace(/^```[\s\S]*?^```/gm, '');
  const heads = stripped.split('\n').filter((l) => /^#{2,4} /.test(l));
  const lessonHeads = heads.filter((h) => /^(##|###) /.test(h) && !/^### (Mistake|Example)\b/.test(h));
  const expected = [...DESIGN_HEADINGS];
  const got = lessonHeads.filter((h) => h !== '## See also');
  if (JSON.stringify(got) !== JSON.stringify(expected)) {
    const miss = expected.find((h, i) => got[i] !== h);
    errors.push(`${file}: lesson headings differ from Section 8 at "${miss}" (D13)`);
  }
  const see = heads.indexOf('## See also');
  if (see >= 0 && see !== heads.length - 1) errors.push(`${file}: "## See also" must be the last section (D13)`);
  for (const l of stripped.split('\n')) if (/^>\s/.test(l) && words(l.replace(/^>\s*/, '')) > 15) errors.push(`${file}: a quoted passage is longer than 15 words (D8)`);
  return errors;
}
