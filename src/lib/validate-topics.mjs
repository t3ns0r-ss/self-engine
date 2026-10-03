// Cross-file validation for topic data files, the glossary, and lesson MDX files (PLAN.md Section 12,
// with PROBLEM_BANK_PLAN.md Section 12 applied). Pure functions over parsed data.
import { fileId, laterKeywordHits } from './validate.mjs';

export const LESSON_HEADINGS = [
  '## 1. Why this topic exists',
  '## 2. Prerequisites and scope',
  '### What you need',
  '### What this topic does not cover',
  '## 3. Definitions',
  '## 4. Theory and proofs',
  '## 5. Recognition Cards',
  '## 6. Templates',
  '## 7. Bug catalogue',
  '## 8. Worked examples',
  '## 9. Problem ladder',
  '## 10. Identification drill',
  '## 11. Look-alike pairs',
  '## 12. Self-test questions',
  '## 13. Checkpoint',
  '## 14. Decision map update',
];
// Topic 7.8 replaces Sections 4, 6, and 7 with a recap (PLAN.md Section 4 notes).
const HEADINGS_78 = LESSON_HEADINGS.filter((h) => !/^## [467]\. /.test(h));

export const WORKED_EXAMPLE_STEPS = [
  '#### Step 1: Constraints → budget',
  '#### Step 2: Question form → candidate tools',
  '#### Step 3: Property check → decision',
  '#### Step 4: Proof for this problem',
  '#### Step 5: Code',
  '#### Step 6: Alternative approach',
];

/** Checkpoint time limit by phase (PLAN.md Section 6.13). */
export const checkpointMinutes = (phase) => (phase <= 1 ? 90 : phase <= 4 ? 120 : 150);

/** Headings (outside fenced code) in the order they appear. */
export function headingsOf(text) {
  const out = [];
  let fence = false;
  for (const line of text.split('\n')) {
    if (/^\s*(```|~~~)/.test(line)) fence = !fence;
    else if (!fence && /^#{2,4} /.test(line)) out.push(line.trimEnd());
  }
  return out;
}

/** Lesson text minus frontmatter, imports, and the "What this topic does not cover" subsection. */
export function textForKeywordScan(text) {
  const body = text.replace(/^---\n[\s\S]*?\n---\n/, '').replace(/^import .*$/gm, '');
  const lines = body.split('\n');
  const out = [];
  let skipping = false;
  for (const line of lines) {
    if (/^#{2,3} /.test(line)) skipping = line.trim() === '### What this topic does not cover';
    if (!skipping) out.push(line);
  }
  return out.join('\n');
}

const num = (d) => (/^-?\d+$/.test(d) ? Number(d) : { Easy: 1, Medium: 2, Hard: 3 }[d] ?? null);

/**
 * @param {object} d
 * @param {Array} d.curriculum
 * @param {Object<string, object>} d.patterns topic -> pattern file
 * @param {Object<string, object>} d.banks topic -> bank file
 * @param {Object<string, object>} d.topics topic -> topic data file
 * @param {Array} d.glossary glossary entries
 * @param {Object<string, {path: string, text: string}>} d.lessons topic -> lesson file
 * @returns {string[]}
 */
export function validateTopics({ curriculum, patterns, banks, topics, glossary, lessons }) {
  const errors = [];
  const err = (file, msg) => errors.push(`${file}: ${msg}`);
  const byId = new Map(curriculum.map((t) => [t.id, t]));
  const bankById = new Map();
  for (const b of Object.values(banks)) for (const p of b.problems) bankById.set(p.id, { ...p, bankTopic: b.topic });

  // Glossary.
  const G = 'src/data/glossary.yaml';
  const terms = new Map();
  for (const g of glossary) {
    if (terms.has(g.term.toLowerCase())) err(G, `duplicate term "${g.term}"`);
    terms.set(g.term.toLowerCase(), g);
    if (!byId.has(g.topic)) err(G, `term "${g.term}" has unknown topic ${g.topic}`);
  }

  // Cards available as drill answers: this topic's cards and every earlier topic's cards or patterns
  // (an earlier lesson may not be written yet; its bank patterns stand in for its cards).
  const cardsOf = (topic) => new Set([...(topics[topic]?.cards ?? []).map((c) => c.id), ...(patterns[topic]?.patterns ?? []).map((p) => p.id)]);

  for (const [tid, tf] of Object.entries(topics)) {
    const F = `src/data/topics/${fileId(tid)}.yaml`;
    const t = byId.get(tid);
    if (!t) {
      err(F, `topic ${tid} not in curriculum`);
      continue;
    }
    if (tf.id !== tid) err(F, `id field is "${tf.id}", expected "${tid}"`);
    const own = new Set(tf.cards.map((c) => c.id));
    if (own.size !== tf.cards.length) err(F, 'duplicate card ids');
    const is78 = tid === '7.8';

    // Problems: exist in the bank, unique here, come from the right set, techniques allowed.
    const roleOf = new Map();
    for (const p of tf.problems) {
      if (roleOf.has(p.id)) err(F, `${p.id} listed twice`);
      roleOf.set(p.id, p.role);
      const b = bankById.get(p.id);
      if (!b) {
        err(F, `${p.id} is not in the problem bank`);
        continue;
      }
      const practiceRole = p.role === 'ladder' || p.role === 'worked_example';
      if (practiceRole && b.set !== 'practice') err(F, `${p.id}: role ${p.role} must come from the practice set`);
      if (!practiceRole && b.set !== 'reserved') err(F, `${p.id}: role ${p.role} must come from the reserved set`);
      if (practiceRole && b.bankTopic !== tid) err(F, `${p.id}: ${p.role} problems must come from this topic's bank (it is in ${b.bankTopic})`);
      for (const tech of b.techniques) {
        const tt = byId.get(tech);
        if (tt && tt.order > t.order) err(F, `${p.id}: uses technique ${tech}, later than ${tid}`);
      }
      if (t.phase === 7 && !is78 && (p.role === 'ladder' || p.role === 'worked_example'))
        for (const r of t.requires) if (!b.techniques.includes(r)) err(F, `${p.id}: Phase 7 problems must use the combined topics; missing ${r}`);
      if (p.card && (p.role === 'ladder' || p.role === 'checkpoint' || p.role === 'review') && !own.has(p.card))
        err(F, `${p.id}: card ${p.card} is not a card of topic ${tid}`);
      // Exam problems test earlier topics of the phase: their card belongs to the topic of their bank.
      if (p.role === 'exam' && (!p.card || !cardsOf(b.bankTopic).has(p.card)))
        err(F, `${p.id}: exam problems need the card of topic ${b.bankTopic} they test (found ${p.card})`);
    }
    const ofRole = (r) => tf.problems.filter((p) => p.role === r);

    // Counts (PLAN.md Section 12.3).
    const ladder = ofRole('ladder');
    // Skipped while the topic is a draft (pipeline steps 1–9).
    if (!tf.draft) {
      if (!is78 && (tf.cards.length < 3 || tf.cards.length > 6)) err(F, `has ${tf.cards.length} cards; 3–6 required`);
      if (!is78) {
        if (ladder.length < 12 || ladder.length > 20) err(F, `ladder has ${ladder.length} problems; 12–20 required`);
        for (const c of tf.cards) {
          const n = ladder.filter((p) => p.card === c.id).length;
          if (n < 3) err(F, `card ${c.id} has ${n} ladder problems; at least 3 required`);
        }
      }
      if (tf.drill.length < 8 || tf.drill.length > 12) err(F, `drill has ${tf.drill.length} items; 8–12 required`);
      const earlier = tf.drill.filter((d) => byId.get(d.answer_topic) && byId.get(d.answer_topic).order < t.order).length;
      // The first topics have few earlier topics to draw from: 0.1 needs none, 0.2 one, 0.3 two.
      const needEarlier = Math.min(3, t.order - 1);
      if (!is78 && earlier < needEarlier) err(F, `drill has ${earlier} earlier-topic answers; at least ${needEarlier} required`);
      if (tf.lookalike_pairs.length < 2 || tf.lookalike_pairs.length > 4) err(F, `has ${tf.lookalike_pairs.length} look-alike pairs; 2–4 required`);
      if (tf.self_test.length < 5 || tf.self_test.length > 8) err(F, `has ${tf.self_test.length} self-test questions; 5–8 required`);
      if (tf.checkpoint.problems.length !== 3) err(F, `checkpoint has ${tf.checkpoint.problems.length} problems; exactly 3 required`);
      if (tf.checkpoint.time_limit_minutes !== checkpointMinutes(t.phase))
        err(F, `checkpoint time limit must be ${checkpointMinutes(t.phase)} minutes for phase ${t.phase}`);
      for (const s of [1, 2, 3]) {
        const n = ofRole('review').filter((p) => p.review_set === s).length;
        if (n < 3 || n > 4) err(F, `review set ${s} has ${n} problems; 3–4 required`);
      }
      const exam = ofRole('exam');
      if (exam.length) {
        const last = curriculum.filter((x) => x.phase === t.phase).at(-1);
        if (last.id !== tid) err(F, `exam problems belong in the phase's last topic (${last.id})`);
        if (exam.length < 6 || exam.length > 10) err(F, `phase exam has ${exam.length} problems; 6–10 required`);
        const covered = new Set(exam.map((p) => bankById.get(p.id)?.bankTopic));
        for (const x of curriculum.filter((c) => c.phase === t.phase)) if (!covered.has(x.id)) err(F, `phase exam has no problem from topic ${x.id}`);
      }
    }

    // References between sections.
    for (const id of tf.checkpoint.problems) if (roleOf.get(id) !== 'checkpoint') err(F, `checkpoint lists ${id}, which is not a problem with role checkpoint`);
    if (ofRole('checkpoint').length !== tf.checkpoint.problems.length) err(F, 'every checkpoint-role problem must be listed under checkpoint.problems');
    const drillIds = new Set();
    for (const d of tf.drill) {
      if (roleOf.get(d.problem) !== 'drill') err(F, `drill item ${d.problem} is not a problem with role drill`);
      drillIds.add(d.problem);
      const at = byId.get(d.answer_topic);
      if (!at || at.order > t.order) err(F, `drill item ${d.problem}: answer_topic ${d.answer_topic} must be this or an earlier topic`);
      else if (!cardsOf(d.answer_topic).has(d.answer_card)) err(F, `drill item ${d.problem}: ${d.answer_card} is not a card or pattern of topic ${d.answer_topic}`);
    }
    for (const p of ofRole('drill')) if (!drillIds.has(p.id)) err(F, `${p.id} has role drill but no drill item`);
    for (const pair of tf.lookalike_pairs)
      for (const id of [pair.a, pair.b]) if (roleOf.get(id) !== 'lookalike') err(F, `look-alike pair lists ${id}, which is not a problem with role lookalike`);

    // Rungs 1..k per card; difficulty non-decreasing per platform along the rungs.
    for (const c of tf.cards) {
      const rungs = ladder.filter((p) => p.card === c.id).sort((a, b) => a.rung - b.rung);
      rungs.forEach((p, i) => {
        if (p.rung !== i + 1) err(F, `card ${c.id}: rungs must be 1..${rungs.length} without gaps (found ${p.rung} at position ${i + 1})`);
      });
      const lastBy = new Map();
      for (const p of rungs) {
        const b = bankById.get(p.id);
        if (!b) continue;
        const v = num(b.difficulty);
        if (v === null) continue;
        const prev = lastBy.get(b.source);
        if (prev && v < prev.v) err(F, `card ${c.id}: ${p.id} (${b.difficulty}) is easier than earlier rung ${prev.id} (${prev.d}) on ${b.source}`);
        lastBy.set(b.source, { v, id: p.id, d: b.difficulty });
      }
    }

    // Decision map.
    for (const e of tf.decision_map) {
      if (!own.has(e.choose)) err(F, `decision map chooses ${e.choose}, which is not a card of ${tid}`);
      for (const o of e.over) {
        const ok = [...byId.values()].some((x) => x.order <= t.order && cardsOf(x.id).has(o.card));
        if (!ok) err(F, `decision map compares with unknown card ${o.card}`);
      }
    }

    // Glossary terms.
    for (const term of tf.glossary_added) {
      const g = terms.get(term.toLowerCase());
      if (!g) err(F, `glossary_added "${term}" is not in glossary.yaml`);
      else if (g.topic !== tid) err(F, `glossary_added "${term}" has topic ${g.topic} in glossary.yaml`);
    }
  }

  // Lessons: required headings in order, worked-example steps, data file present, keyword scan.
  for (const [tid, lesson] of Object.entries(lessons)) {
    const t = byId.get(tid);
    if (!t) {
      err(lesson.path, `frontmatter topic ${tid} is not in the curriculum`);
      continue;
    }
    if (!topics[tid]) err(lesson.path, `no data file src/data/topics/${fileId(tid)}.yaml`);
    const hs = headingsOf(lesson.text);
    const required = tid === '7.8' ? HEADINGS_78 : LESSON_HEADINGS;
    let i = 0;
    for (const h of hs) if (i < required.length && h === required[i]) i++;
    if (i < required.length) err(lesson.path, `missing or out-of-order heading "${required[i]}"`);
    const examples = [];
    for (const h of hs) {
      if (/^### Example \d+: /.test(h)) examples.push([]);
      else if (h.startsWith('#### ') && examples.length) examples.at(-1).push(h);
    }
    examples.forEach((steps, k) => {
      if (steps.join('\n') !== WORKED_EXAMPLE_STEPS.join('\n')) err(lesson.path, `Example ${k + 1} must have exactly the six step headings in order`);
    });
    const hits = laterKeywordHits(textForKeywordScan(lesson.text), t.order, curriculum);
    if (hits.length) err(lesson.path, `later-topic keywords outside "What this topic does not cover": ${hits.join(', ')}`);
  }

  return errors;
}
