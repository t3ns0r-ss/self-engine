// Checks of src/data/exercises/INVENTORY.yaml (DESIGN_TRACKS_PLAN.md Sections 10.10 and 18.2).
const norm = (s) => s.toLowerCase().replace(/\s+/g, ' ').trim();

/**
 * @param {{topics: Record<string, object>}} inv parsed inventory
 * @param {Array} rows design curriculum rows
 * @returns {string[]}
 */
export function validateInventory(inv, rows) {
  const errors = [];
  const F = 'src/data/exercises/INVENTORY.yaml';
  const err = (m) => errors.push(`${F}: ${m}`);
  const rowById = new Map(rows.map((r) => [r.id, r]));
  for (const r of rows) if (!inv.topics[r.id]) err(`topic ${r.id} is missing`);
  const seenStub = new Map();
  for (const [id, t] of Object.entries(inv.topics)) {
    const row = rowById.get(id);
    if (!row) { err(`${id} is not a design topic`); continue; }
    const cardOwner = new Map();                    // card id -> topic, for this and earlier topics of the track
    for (const [oid, ot] of Object.entries(inv.topics)) {
      const o = rowById.get(oid);
      if (o && o.track === row.track && o.order <= row.order) for (const c of ot.cards) cardOwner.set(`${oid}/${c.id}`, true);
    }
    const here = new Set(t.cards.map((c) => c.id));
    const kind = row.kind;
    if (kind !== 'capstone') {
      const max = kind === 'light' ? 2 : 4;
      if (t.cards.length < 1 || t.cards.length > max) err(`${id}: ${t.cards.length} cards, expected 1-${max}`);
    }
    const [lo, hi] = row.track === 'hld' ? [4, 6] : kind === 'light' ? [3, 4] : [4, 6];
    if (kind !== 'capstone' && !/^none/.test(row.lab ?? '') && (t.ladder.length < lo || t.ladder.length > hi)) err(`${id}: ${t.ladder.length} ladder rungs, expected ${lo}-${hi}`);
    t.ladder.forEach((r, i) => {
      if (r.rung !== i + 1) err(`${id}: rung ${r.rung} is out of order`);
      if (r.card && !here.has(r.card)) err(`${id} rung ${r.rung}: card ${r.card} is not planned in this topic`);
      if ((r.card === null) !== (r.needs_new_structure === false) && r.card === null) { /* a no-new-structure rung may name a card or none */ }
    });
    if (t.ladder.length && !t.ladder.some((r) => r.needs_new_structure === false)) err(`${id}: the ladder needs a rung with needs_new_structure: false`);
    if (new Set(t.ladder.map((r) => norm(r.new_force))).size !== t.ladder.length) err(`${id}: two rungs have the same new_force`);
    // drill quotas (Section 8.10)
    const [dlo, dhi] = kind === 'light' ? [6, 6] : [6, 8];
    if (kind !== 'capstone' && (t.drill.length < dlo || t.drill.length > dhi)) err(`${id}: ${t.drill.length} drill items, expected ${dlo}-${dhi}`);
    if (t.drill.length) {
      const none = t.drill.filter((d) => d.answer === 'none').length;
      if (none < Math.ceil(t.drill.length * 0.2)) err(`${id}: ${none} "none" drill items of ${t.drill.length}; at least 20% are required`);
      const earlier = [...cardOwner.keys()].filter((k) => !k.startsWith(`${id}/`)).length;
      const used = t.drill.filter((d) => d.answer !== 'none' && d.answer.topic !== id).length;
      if (used < Math.min(3, earlier)) err(`${id}: ${used} drill items use an earlier card; at least ${Math.min(3, earlier)} are required`);
      for (const d of t.drill) if (d.answer !== 'none' && !cardOwner.has(`${d.answer.topic}/${d.answer.card}`)) err(`${id}: drill answer ${d.answer.topic}/${d.answer.card} is not a card of this or an earlier topic`);
    }
    if (kind === 'light' ? t.checkpoint !== null : kind !== 'capstone' && t.checkpoint === null) err(`${id}: ${kind === 'light' ? 'light topics have no checkpoint' : 'a checkpoint is required'}`);
    const wantSets = kind === 'light' ? 1 : 2;
    if (kind !== 'capstone' && t.reviews.length !== wantSets) err(`${id}: ${t.reviews.length} review sets, expected ${wantSets}`);
    // no scenario repeats within a track
    const stubs = [...t.drill.map((d) => d.stub), ...t.reviews.flatMap((r) => r.stubs), ...(t.estimates ?? [])];
    for (const s of stubs) {
      const key = `${row.track}:${norm(s)}`;
      if (seenStub.has(key)) err(`${id}: scenario "${s.slice(0, 50)}…" repeats one in ${seenStub.get(key)}`);
      else seenStub.set(key, id);
    }
  }
  return errors;
}
