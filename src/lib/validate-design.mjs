// Cross-file checks for the LLD and HLD tracks (DESIGN_TRACKS_PLAN.md Sections 7.1, 12 D3 and D11).
// Pure functions: they take parsed data and return error messages.

/** Required level-2 and level-3 headings of the Section 8 lesson template; keywords may not hide inside them. */
export const TEMPLATE_HEADINGS = [
  'Why this topic exists', 'Prerequisites and scope', 'What you need', 'What this topic does not cover', 'Definitions',
  'Principles and claims', 'Recognition Cards', 'Reference designs', 'Mistake catalogue', 'Worked examples',
  'Exercise ladder', 'Recognition drill', 'Look-alike pairs', 'Self-test questions', 'Checkpoint', 'Decision map update', 'See also',
];

const PREFIX = { lld: 'L', hld: 'H' };
const KW = (s) => s.toLowerCase();

/**
 * Keyword collisions (D11): a keyword of a topic may not appear inside a keyword of an earlier topic of the same
 * track (the later lesson would trip the earlier topic's "no later keyword" scan the other way round), nor inside a
 * required template heading. Returns messages naming both topics.
 */
export function keywordCollisions(rows) {
  const errors = [];
  for (const track of ['lld', 'hld']) {
    const rs = rows.filter((r) => r.track === track).sort((a, b) => a.order - b.order);
    rs.forEach((r, i) => {
      for (const kw of r.keywords) {
        const k = KW(kw);
        for (const h of TEMPLATE_HEADINGS) if (KW(h).includes(k)) errors.push(`topic ${r.id}: keyword "${kw}" appears inside the template heading "${h}"`);
        for (const e of rs.slice(0, i)) for (const ekw of e.keywords) if (KW(ekw).includes(k)) errors.push(`topic ${r.id}: keyword "${kw}" appears inside keyword "${ekw}" of earlier topic ${e.id}`);
      }
    });
  }
  return errors;
}

/**
 * @param {Array} rows design-track rows of curriculum.yaml (track lld or hld)
 * @returns {string[]}
 */
export function validateDesignCurriculum(rows) {
  const errors = [];
  const C = 'src/data/curriculum.yaml';
  const err = (m) => errors.push(`${C}: ${m}`);
  const ids = new Set();
  const slugs = new Set();
  for (const track of ['lld', 'hld']) {
    const rs = rows.filter((r) => r.track === track);
    if (!rs.length) continue;
    const byId = new Map(rs.map((r) => [r.id, r]));
    rs.forEach((r, i) => {
      if (r.order !== i + 1) err(`topic ${r.id} has order ${r.order}, expected ${i + 1} (rows must be listed in order)`);
      if (!r.id.startsWith(PREFIX[track])) err(`topic ${r.id} is in track ${track} but its id does not start with ${PREFIX[track]}`);
      if (r.phase !== r.id.split('.')[0]) err(`topic ${r.id} has phase ${r.phase}`);
      if (ids.has(r.id)) err(`duplicate topic id ${r.id}`);
      ids.add(r.id);
      if (slugs.has(`${track}/${r.slug}`)) err(`duplicate slug ${r.slug} in track ${track}`);
      slugs.add(`${track}/${r.slug}`);
      if (track === 'hld' && (r.kind === 'measured' || r.kind === 'light')) err(`topic ${r.id}: HLD topics are standard or capstone, not ${r.kind}`);
      if (r.kind === 'capstone' && i !== rs.length - 1) err(`topic ${r.id}: only the last topic of a track is the capstone`);
      if (i === rs.length - 1 && r.kind !== 'capstone') err(`topic ${r.id}: the last topic of the track must be the capstone`);
      if (i === 0 && r.requires.length) err(`topic ${r.id}: the first topic of a track has empty requires`);
      if (new Set(r.requires).size !== r.requires.length) err(`topic ${r.id}: duplicate entries in requires`);
      for (const q of r.requires) {
        const t = byId.get(q);
        if (!t) err(`topic ${r.id} requires ${q}, which is not a topic of track ${track} (no cross-track dependencies)`);
        else if (t.order >= r.order) err(`topic ${r.id} requires ${q}, which is not earlier`);
      }
      if (r.kind === 'capstone') {
        const earlier = rs.filter((x) => x.order < r.order).map((x) => x.id);
        for (const e of earlier) if (!r.requires.includes(e)) err(`capstone ${r.id} must require every earlier topic; missing ${e}`);
        if (r.keywords.length) err(`capstone ${r.id} has no keywords of its own`);
      } else if (!r.keywords.length) err(`topic ${r.id} has no keywords`);
    });
  }
  return [...errors, ...keywordCollisions(rows)];
}

/** D12: weights sum to 100, at least one critical criterion, unique ids, anchors 0-2 (schema), observable wording. */
export function validateRubrics(rubrics) {
  const errors = [];
  const F = 'src/data/rubrics.yaml';
  const seen = new Set();
  for (const r of rubrics) {
    if (seen.has(r.id)) errors.push(`${F}: duplicate rubric id ${r.id}`);
    seen.add(r.id);
    const sum = r.criteria.reduce((a, c) => a + c.weight, 0);
    if (sum !== 100) errors.push(`${F}: ${r.id} weights sum to ${sum}, expected 100`);
    if (!r.criteria.some((c) => c.critical || c.critical_when)) errors.push(`${F}: ${r.id} has no critical criterion`);
    const ids = new Set();
    for (const c of r.criteria) {
      if (ids.has(c.id)) errors.push(`${F}: ${r.id} has duplicate criterion ${c.id}`);
      ids.add(c.id);
      for (const k of [0, 1, 2]) if (/\b(good|bad|poor|excellent|great)\b/i.test(c.anchors[k]))
        errors.push(`${F}: ${r.id}.${c.id} anchor ${k} uses a judgement word; describe observable evidence`);
    }
  }
  // The four standard rubrics of Section 10.7 must exist.
  for (const id of ['rubric-lld-build-v1', 'rubric-hld-mock-v1', 'rubric-hld-deep-dive-v1', 'rubric-hld-failure-v1'])
    if (!seen.has(id)) errors.push(`${F}: missing standard rubric ${id}`);
  return errors;
}

/** D6 (data part): constant ids unique, finite values, source dates not in the future relative to `today`. */
export function validateConstants(constants, today = new Date().toISOString().slice(0, 10)) {
  const errors = [];
  const F = 'src/data/constants.yaml';
  const seen = new Set();
  for (const c of constants) {
    if (seen.has(c.id)) errors.push(`${F}: duplicate constant id ${c.id}`);
    seen.add(c.id);
    if (!Number.isFinite(c.value) || c.value <= 0) errors.push(`${F}: ${c.id} value must be a positive finite number`);
    if (c.source.accessed > today) errors.push(`${F}: ${c.id} accessed date ${c.source.accessed} is in the future`);
  }
  return errors;
}
