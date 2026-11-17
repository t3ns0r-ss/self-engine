// Validation of the contest-practice problem sets that live outside curriculum.yaml (CURRICULUM_GAPS_PLAN.md Section 6, items 2 and 3):
// the volume set (src/data/sets/volume-0.yaml, Codeforces 800 to 1000 and the same level elsewhere) and the bridge set
// (src/data/sets/bridge-4-5.yaml, 1900 to 2100, from the end of Phase 4 towards Phase 5).
// A set problem may not be a bank problem: the bank holds reserved exam, drill, checkpoint and review problems and the topic ladders, and
// every problem in the programme has one home, so a set can never spoil a reserved problem. Pure functions over parsed data.
import { PLATFORM, laterKeywordHits } from './validate.mjs';

export const VOLUME_MIN = 20; // target 40; fewer is allowed when an honest search finds fewer (stated in PROGRESS.md)
export const VOLUME_MAX = 60;
export const VOLUME_CF = [800, 1000];
export const VOLUME_AC_MAX = 1000;
export const VOLUME_LAST_PHASE = 1;
export const BRIDGE_MIN = 10;
export const BRIDGE_MAX = 15;
export const BRIDGE_BAND = [1900, 2100];
export const BRIDGE_LAST_PHASE = 4;

const oneLine = (s) => !/[\n\r]/.test(s);

function checkProblem(p, file, err, band, kind) {
  const plat = PLATFORM[p.source];
  const m = plat.id.exec(p.id);
  if (!m) {
    err(file, `${p.id}: id does not match the ${p.source} id format`);
  } else {
    const urlOk = plat.url ? p.url === plat.url(m) : plat.urlPattern(m).test(p.url);
    if (!urlOk) err(file, `${p.id}: url ${p.url} does not match the ${p.source} URL format`);
  }
  if (!plat.difficulty.test(p.difficulty)) err(file, `${p.id}: difficulty "${p.difficulty}" is not valid for ${p.source}`);
  if (p.source_check === 'api' && p.source !== 'codeforces') err(file, `${p.id}: source_check api is only for Codeforces; open the ${p.source} page instead`);
  if (!oneLine(p.summary)) err(file, `${p.id}: summary must be one line`);
  const d = /^-?\d+$/.test(p.difficulty) ? Number(p.difficulty) : null;
  if (kind === 'volume') {
    if (p.source === 'codeforces' && d !== null && (d < VOLUME_CF[0] || d > VOLUME_CF[1])) err(file, `${p.id}: rating ${d} is outside the volume band ${VOLUME_CF[0]} to ${VOLUME_CF[1]}`);
    if (p.source === 'atcoder' && d !== null && d > VOLUME_AC_MAX) err(file, `${p.id}: AtCoder difficulty ${d} is above ${VOLUME_AC_MAX}`);
    if (p.source === 'leetcode' && p.difficulty !== 'Easy') err(file, `${p.id}: the volume set uses LeetCode Easy only`);
  } else {
    if ((p.source === 'codeforces' || p.source === 'atcoder') && d !== null && (d < band[0] || d > band[1])) err(file, `${p.id}: rating ${d} is outside the bridge band ${band[0]} to ${band[1]}`);
    if (p.source === 'leetcode' && p.difficulty !== 'Hard') err(file, `${p.id}: the bridge set uses LeetCode Hard only`);
    // Every new_idea is checked by reading the problem (CURRICULUM_GAPS_PLAN.md Section 6, item 3), so a statement that could not be opened does not qualify.
    if (p.source_check !== 'page') err(file, `${p.id}: bridge problems need source_check: page (the statement must have been read)`);
  }
}

/**
 * @param {object} d
 * @param {Array} d.curriculum CP curriculum rows (drafts included)
 * @param {Object<string, {problems: Array}>} d.banks topic id -> bank file
 * @param {Object<string, {problems: Array}>} d.topics topic id -> topic file
 * @param {Object<string, object>} d.sets set name -> parsed set file ('volume-0', 'bridge-4-5')
 * @returns {string[]}
 */
export function validateSets({ curriculum: allRows, banks, topics, sets }) {
  const errors = [];
  const err = (file, msg) => errors.push(`${file}: ${msg}`);
  const live = allRows.filter((t) => !t.draft);
  const byId = new Map(live.map((t) => [t.id, t]));
  const inBank = new Map();
  for (const [t, b] of Object.entries(banks)) for (const p of b.problems) inBank.set(p.id, `the bank of topic ${t}`);
  for (const [t, tf] of Object.entries(topics)) for (const p of tf.problems ?? []) if (!inBank.has(p.id)) inBank.set(p.id, `the data file of topic ${t}`);
  const seen = new Map(); // id -> set name

  const vol = sets['volume-0'];
  const bri = sets['bridge-4-5'];
  const V = 'src/data/sets/volume-0.yaml';
  const B = 'src/data/sets/bridge-4-5.yaml';
  if (!vol) err(V, 'missing');
  if (!bri) err(B, 'missing');

  for (const [file, set] of [[V, vol], [B, bri]]) {
    if (!set) continue;
    for (const p of set.problems) {
      if (seen.has(p.id)) err(file, `${p.id} already appears in ${seen.get(p.id)} (ids must be unique across the sets)`);
      else seen.set(p.id, file);
      if (inBank.has(p.id)) err(file, `${p.id} is already in ${inBank.get(p.id)}; a set problem may not duplicate a bank or exam problem`);
    }
  }

  if (vol) {
    const n = vol.problems.length;
    if (n < VOLUME_MIN || n > VOLUME_MAX) err(V, `${n} problems, expected ${VOLUME_MIN} to ${VOLUME_MAX} (target 40)`);
    for (const p of vol.problems) {
      checkProblem(p, V, err, VOLUME_CF, 'volume');
      const t = byId.get(p.topic);
      if (!t) err(V, `${p.id}: unknown or draft topic ${p.topic}`);
      else {
        if (t.phase > VOLUME_LAST_PHASE) err(V, `${p.id}: topic ${p.topic} is in Phase ${t.phase}; the volume set needs only Phase 0 and 1 topics`);
        const hits = laterKeywordHits(p.summary, t.order, live);
        if (hits.length) err(V, `${p.id}: summary uses later-topic keywords (topic ${p.topic}): ${hits.join(', ')}`);
      }
    }
  }

  if (bri) {
    const n = bri.problems.length;
    if (n < BRIDGE_MIN || n > BRIDGE_MAX) err(B, `${n} problems, expected ${BRIDGE_MIN} to ${BRIDGE_MAX}`);
    // The new idea must not need a Phase 5 or later technique: the set sits between the phases, after the last Phase 4 topic.
    const lastP4 = Math.max(...live.filter((t) => t.phase <= BRIDGE_LAST_PHASE).map((t) => t.order));
    for (const p of bri.problems) {
      checkProblem(p, B, err, BRIDGE_BAND, 'bridge');
      if (!oneLine(p.new_idea) || p.new_idea.length > 320) err(B, `${p.id}: new_idea must be one line of at most 320 characters`);
      if (!oneLine(p.have)) err(B, `${p.id}: have must be one line`);
      for (const tid of p.have_topics) {
        const t = byId.get(tid);
        if (!t) err(B, `${p.id}: have_topics names unknown or draft topic ${tid}`);
        else if (t.phase > BRIDGE_LAST_PHASE) err(B, `${p.id}: have_topics names ${tid}, which is after Phase ${BRIDGE_LAST_PHASE}`);
      }
      const hits = laterKeywordHits(`${p.summary} ${p.have} ${p.new_idea}`, lastP4, live);
      if (hits.length) err(B, `${p.id}: text uses keywords of topics after Phase ${BRIDGE_LAST_PHASE}: ${hits.join(', ')}`);
    }
  }
  return errors;
}
