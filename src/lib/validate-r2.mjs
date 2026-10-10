// Revision 2 checks (PLAN.md Section 12, items 3 and 9–13) for topics that carry a `uses` list.
// Topics without one are still in the pre-revision format until the retrofit milestone R1 reaches them.
import { existsSync, readFileSync } from 'node:fs';
import { laterKeywordHits } from './validate.mjs';

const realFs = { exists: (p) => existsSync(p), read: (p) => readFileSync(p, 'utf8') };

export const isR2 = (tf) => Array.isArray(tf.uses);

/** Every string reachable inside `v`. */
function* strings(v) {
  if (typeof v === 'string') yield v;
  else if (Array.isArray(v)) for (const x of v) yield* strings(x);
  else if (v && typeof v === 'object') for (const x of Object.values(v)) yield* strings(x);
}

/** Topic ids written as "topic 3.2" or "(3.2)" in free text. */
export function topicMentions(text) {
  const out = new Set();
  for (const m of text.matchAll(/\btopics?\s+([0-7]\.[1-8])\b/gi)) out.add(m[1]);
  for (const m of text.matchAll(/\(([0-7]\.[1-8])\)/g)) out.add(m[1]);
  return out;
}

/** The numbered theorem blocks of a lesson: text from "**Theorem x.y.z" to the next theorem or heading. */
export function theoremBlocks(text) {
  const lines = text.split('\n');
  const blocks = [];
  let cur = null;
  let fence = false;
  for (const line of lines) {
    if (/^\s*(```|~~~)/.test(line)) fence = !fence;
    const m = !fence && /^\*\*Theorem (\d\.\d\.\d+)\b/.exec(line);
    if (m) {
      cur = { id: m[1], lines: [line] };
      blocks.push(cur);
    } else if (!fence && /^#{2,4} /.test(line)) cur = null;
    else if (cur) cur.lines.push(line);
  }
  return blocks.map((b) => ({ id: b.id, text: b.lines.join('\n') }));
}

/** Lines "P1 brute=3 method=3" / "N1 brute=3 method=2" of a card example unit. */
export function parseCardUnit(text) {
  const out = {};
  for (const line of text.split('\n')) {
    const m = /^([PN]\d+)\s+brute=(\S+)\s+method=(\S+)\s*$/.exec(line.trim());
    if (m) out[m[1]] = { brute: m[2], method: m[3] };
  }
  return out;
}

export function validateR2({ tid, t, tf, lesson, curriculum, byId, topics, patterns, bankById, F, err, fsx = realFs }) {
  const cardsOfTopic = (topic) => {
    const own = topics[topic]?.cards ?? [];
    return own.length ? new Set(own.map((c) => c.id)) : new Set((patterns[topic]?.patterns ?? []).map((p) => p.id));
  };
  const checkRef = (ref, where) => {
    const rt = byId.get(ref.topic);
    if (!rt) return err(F, `${where}: unknown topic ${ref.topic}`);
    if (rt.order > t.order) return err(F, `${where}: ${ref.topic} ${ref.card} belongs to a later topic than ${tid}`);
    if (!cardsOfTopic(ref.topic).has(ref.card)) err(F, `${where}: ${ref.card} is not a card of topic ${ref.topic}`);
  };

  // `uses` (item 10).
  const used = new Set();
  for (const u of tf.uses) {
    const ut = byId.get(u.topic);
    if (!ut) err(F, `uses: unknown topic ${u.topic}`);
    else if (ut.order >= t.order) err(F, `uses: ${u.topic} is not earlier than ${tid}`);
    if (used.has(u.topic)) err(F, `uses: ${u.topic} listed twice`);
    used.add(u.topic);
  }
  for (const r of t.requires) if (!used.has(r)) err(F, `uses is missing ${r}, which curriculum.yaml lists under requires`);
  const mustUse = (id, why) => {
    if (id !== tid && byId.has(id) && !used.has(id)) err(F, `uses is missing ${id} (${why})`);
  };

  // Cards (item 3 counts, item 9 references, item 13 examples).
  const workedHere = new Set(tf.problems.filter((p) => p.role === 'worked_example').map((p) => p.id));
  const roleHere = new Map(tf.problems.map((p) => [p.id, p.role]));
  const earlierIds = new Set();
  for (const x of curriculum) {
    if (x.order >= t.order) continue;
    for (const p of topics[x.id]?.problems ?? []) earlierIds.add(p.id);
    for (const p of bankById.values()) if (p.bankTopic === x.id && p.set === 'practice') earlierIds.add(p.id);
  }
  for (const c of tf.cards) {
    const W = `card ${c.id}`;
    if (c.in_action.candidates.filter((x) => x.verdict === 'chosen').length !== 1) err(F, `${W}: in_action needs exactly one chosen candidate`);
    const pos = c.examples.positive.filter((e) => e.inline);
    const neg = c.examples.negative.filter((e) => e.inline);
    if (!pos.length) err(F, `${W}: needs an inline positive example`);
    if (!neg.length) err(F, `${W}: needs an inline negative example`);
    if (!c.from_theorem.startsWith(`${tid}.`)) err(F, `${W}: from_theorem ${c.from_theorem} is not a theorem of ${tid}`);
    if (!(tf.theorems ?? []).some((th) => th.id === c.from_theorem)) err(F, `${W}: from_theorem ${c.from_theorem} has no entry under theorems`);
    for (const n of c.examples.negative) checkRef(n.correct_tool, `${W}: correct_tool`);
    for (const l of c.lookalikes) checkRef(l.tool, `${W}: look-alike tool`);
    for (const e of c.examples.positive) {
      if (e.worked_example) {
        const ok = workedHere.has(e.worked_example) || (earlierIds.has(e.worked_example) && !roleHere.has(e.worked_example));
        if (!ok) err(F, `${W}: positive example ${e.worked_example} must be a worked example of ${tid} or a problem of an earlier topic`);
      }
    }
    for (const n of c.examples.negative) {
      if (!n.problem) continue;
      const role = roleHere.get(n.problem);
      if (role ? role !== 'worked_example' : !earlierIds.has(n.problem))
        err(F, `${W}: negative example ${n.problem} must be a worked example of ${tid} or a problem of an earlier topic (not a ${role ?? 'later'} problem)`);
    }
    // Card example unit (item 12).
    if (pos.length || neg.length) {
      const dir = `code/${tid}/card-${c.id}`;
      const out = `${dir}/tests/1.out`;
      if (!fsx.exists(out)) err(F, `${W}: missing card example unit ${dir} (tests/1.out)`);
      else {
        const lines = parseCardUnit(fsx.read(out));
        pos.forEach((e, i) => {
          const L = lines[`P${i + 1}`];
          if (!L) err(F, `${W}: ${out} has no line P${i + 1}`);
          else if (!e.inline.answer.includes(L.brute)) err(F, `${W}: P${i + 1} answer "${e.inline.answer}" does not contain brute=${L.brute}`);
          else if (L.method !== L.brute) err(F, `${W}: P${i + 1} is a positive example but method=${L.method} differs from brute=${L.brute}`);
        });
        neg.forEach((e, i) => {
          const L = lines[`N${i + 1}`];
          if (!L) err(F, `${W}: ${out} has no line N${i + 1}`);
          else {
            if (!e.inline.answer.includes(L.brute)) err(F, `${W}: N${i + 1} answer "${e.inline.answer}" does not contain brute=${L.brute}`);
            if (e.inline.method_gives !== L.method) err(F, `${W}: N${i + 1} method_gives "${e.inline.method_gives}" differs from printed method=${L.method}`);
            if (L.method === L.brute) err(F, `${W}: N${i + 1} is a negative example but method equals brute (${L.brute})`);
          }
        });
      }
    }
  }

  // Look-alike pairs, drill and decision map references (item 9).
  tf.lookalike_pairs.forEach((p, i) => {
    for (const side of ['a_tool', 'b_tool']) {
      if (typeof p[side] === 'string') err(F, `look-alike pair ${i + 1}: ${side} must be a {topic, card} reference`);
      else checkRef(p[side], `look-alike pair ${i + 1}: ${side}`);
    }
  });
  tf.drill.forEach((d) => checkRef(d.answer ?? { topic: d.answer_topic, card: d.answer_card }, `drill ${d.problem}`));
  tf.decision_map.forEach((e) => e.over.forEach((o) => checkRef({ topic: o.topic ?? tid, card: o.card }, `decision map ${e.choose} over`)));
  // Free text may not name a later topic or use its keywords.
  const free = [...strings(tf.cards), ...strings(tf.lookalike_pairs.map((p) => [p.shared_surface, p.flipping_difference, p.flipping_input])), ...strings(tf.decision_map)];
  for (const s of free) {
    for (const id of topicMentions(s)) if (byId.get(id)?.order > t.order) err(F, `later topic ${id} named in "${s.slice(0, 60)}…"`);
    const hits = laterKeywordHits(s, t.order, curriculum);
    if (hits.length) err(F, `later-topic keywords in "${s.slice(0, 60)}…": ${hits.join(', ')}`);
  }

  // `uses` must cover everything the topic links to or cites (item 10).
  for (const p of tf.problems) {
    const b = bankById.get(p.id);
    for (const tech of b?.techniques ?? []) mustUse(tech, `technique of ${p.id}`);
  }
  for (const c of tf.cards) {
    for (const n of c.examples.negative) mustUse(n.correct_tool.topic, `card ${c.id} correct_tool`);
    for (const l of c.lookalikes) mustUse(l.tool.topic, `card ${c.id} look-alike`);
  }
  for (const p of tf.lookalike_pairs) for (const side of [p.a_tool, p.b_tool]) if (typeof side !== 'string') mustUse(side.topic, 'look-alike pair');
  for (const d of tf.drill) mustUse(d.answer?.topic ?? d.answer_topic, `drill ${d.problem}`);
  for (const e of tf.decision_map) for (const o of e.over) mustUse(o.topic ?? tid, 'decision map');

  if (lesson) {
    const text = lesson.text;
    for (const m of text.matchAll(/\]\((?:\.\.\/)+(?:phase-\d\/)?(\d)-(\d)-[a-z0-9-]+\/?(?:#[^)]*)?\)/g)) mustUse(`${m[1]}.${m[2]}`, 'linked in the lesson');
    for (const m of text.matchAll(/\bTheorem (\d\.\d)\.\d+/g)) mustUse(m[1], `cited as Theorem ${m[0].slice(8)}`);
    const need = /### What you need\n([\s\S]*?)### What this topic does not cover/.exec(text);
    if (!need) err(lesson.path, 'missing "What you need" section');
    else {
      if (!/<WhatYouNeed topic="/.test(need[1])) err(lesson.path, '"What you need" must be rendered by <WhatYouNeed topic="…" />');
      if (/^\s*[-*] /m.test(need[1]) || /^\s*\d+\. /m.test(need[1])) err(lesson.path, '"What you need" must not contain a hand-written list (use the uses list in the data file)');
    }

    // Lessons no longer carry "C++ details explained" or "Tested" paragraphs (Section 6.6).
    if (/^\*\*C\+\+ details explained|^\*\*Tested\./m.test(text)) err(lesson.path, 'remove the "C++ details explained" and "Tested" paragraphs (PLAN.md Section 6.6)');

    // Theorems (item 11).
    const blocks = theoremBlocks(text);
    const entries = new Map((tf.theorems ?? []).map((e) => [e.id, e]));
    for (const b of blocks) {
      const e = entries.get(b.id);
      const W = `Theorem ${b.id}`;
      if (!e) {
        err(lesson.path, `${W} has no entry under theorems in the data file`);
        continue;
      }
      const tip = b.text.indexOf(':::tip[In plain words]');
      const note = b.text.indexOf(':::note[This proof needs]');
      if (tip < 0) err(lesson.path, `${W}: missing ":::tip[In plain words]" block`);
      if (note < 0) err(lesson.path, `${W}: missing ":::note[This proof needs]" block`);
      if (tip >= 0 && note >= 0) {
        const steps = b.text.slice(tip, note).split('\n').filter((l) => /^\d+\. /.test(l)).length;
        if (steps > 8) err(lesson.path, `${W}: proof has ${steps} numbered steps; at most 8 (split into lemmas)`);
        if (steps === 0) err(lesson.path, `${W}: proof has no numbered steps`);
        if (tip > note) err(lesson.path, `${W}: the preconditions box must come after the plain-words block`);
      }
      if (tip >= 0 && !b.text.includes(e.plain_words)) err(lesson.path, `${W}: the plain-words block must repeat plain_words from the data file`);
      const tag = new RegExp(`<TheoremCode unit="${e.code.replace(/[.*+?^${}()|[\]\\]/g, '\\$&')}"\\s*/>`);
      if (!tag.test(b.text)) err(lesson.path, `${W}: missing <TheoremCode unit="${e.code}" />`);
      const sol = `code/${e.code}/solution.cpp`;
      if (!fsx.exists(sol)) err(lesson.path, `${W}: code unit ${e.code} has no solution.cpp`);
      else {
        const lines = fsx.read(sol).split('\n').map((l) => l.trim());
        const from = lines.indexOf('// snippet:begin'), to = lines.indexOf('// snippet:end');
        if (from < 0 || to < from) err(lesson.path, `${W}: ${sol} needs // snippet:begin and // snippet:end around the implementation`);
        else if (to - from - 1 > 30) err(lesson.path, `${W}: the shown implementation has ${to - from - 1} lines; at most 30`);
      }
      if (!fsx.exists(`code/${e.code}/tests/1.out`)) err(lesson.path, `${W}: code unit ${e.code} has no tests/1.out (the examples)`);
      else if (fsx.read(`code/${e.code}/tests/1.out`).trim() === '') err(lesson.path, `${W}: code unit ${e.code} has an empty tests/1.out; it holds the examples shown`);
    }
    for (const id of entries.keys()) if (!blocks.some((b) => b.id === id)) err(F, `theorems lists ${id}, which is not a "**Theorem ${id}" heading in the lesson`);
  }
}
