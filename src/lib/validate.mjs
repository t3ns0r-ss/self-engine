// Cross-file validation for the curriculum, pattern files, and problem bank.
// PLAN.md Sections 4 and 9.1; PROBLEM_BANK_PLAN.md Sections 4, 5, 6, 7, and 10.
// Pure functions over already-parsed data, so the Node scripts and the Astro build share them.
// Every message starts with the file it concerns and names the problem or pattern id.

export const PLATFORM = {
  codeforces: {
    id: /^cf-(\d+)([A-Z][0-9]?)$/,
    url: (m) => `https://codeforces.com/problemset/problem/${m[1]}/${m[2]}`,
    difficulty: /^\d{3,4}$/,
    bases: ['rating'],
  },
  atcoder: {
    id: /^ac-([a-z0-9_]+_[a-z0-9]+)$/,
    // The contest id is usually the task id without its last part, but not always, so only the
    // task part and the general shape are checked.
    url: null,
    urlPattern: (m) => new RegExp(`^https://atcoder\\.jp/contests/[a-z0-9-]+/tasks/${m[1]}$`),
    difficulty: /^(-?\d+|—)$/,
    bases: ['contest_letter', 'judgement'],
  },
  cses: {
    id: /^cses-(\d+)$/,
    url: (m) => `https://cses.fi/problemset/task/${m[1]}`,
    difficulty: /^—$/,
    bases: ['judgement'],
  },
  leetcode: {
    id: /^lc-([a-z0-9]+(?:-[a-z0-9]+)*)$/,
    url: (m) => `https://leetcode.com/problems/${m[1]}/`,
    difficulty: /^(Easy|Medium|Hard)$/,
    bases: ['judgement'],
  },
};

export const TIER_NAMES = ['Warm-up', 'Easy', 'Core', 'Hard', 'Stretch'];

// Codeforces rating range for each tier, relative to the phase band [L, H] (bank plan Section 4).
// Boundaries are inclusive on both sides, so a rating exactly on a boundary may sit in either tier
// ("when in doubt between two tiers, choose the higher one"). Phase 0 tier 1 is rating 800.
export function cfTierRange(tier, [L, H], phase) {
  if (tier === 1) return phase === 0 ? [0, 800] : [0, L - 200];
  if (tier === 2) return [L - 200, L];
  if (tier === 3) return [L, H];
  if (tier === 4) return [H, H + 200];
  return [H + 200, H + 400];
}

// Allowed tiers for each reserved purpose (bank plan Section 6.3).
export const RESERVED_TIERS = {
  drill: [2, 4],
  later_drill: [2, 3],
  lookalike: [2, 4],
  checkpoint: [3, 4],
  review: [3, 4],
  exam: [3, 4],
};
// Minimum counts per reserved purpose for a complete topic (Section 6.3). Section 11 allows
// `status: short` when these cannot be met without breaking purity.
export const RESERVED_MIN = { drill: 8, later_drill: 4, lookalike: 4, checkpoint: 3, review: 10, exam: 2 };

export const fileId = (topic) => topic.replace('.', '-');

function keywordRegex(kw) {
  const esc = kw.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
  const pre = /^\w/.test(kw) ? '\\b' : '';
  const post = /\w$/.test(kw) ? '\\b' : '';
  return new RegExp(pre + esc + post, 'i');
}

/** Words in `text` that are keywords of topics later than `order`. */
export function laterKeywordHits(text, order, curriculum) {
  const hits = [];
  for (const t of curriculum) {
    if (t.order <= order) continue;
    for (const kw of t.keywords) if (keywordRegex(kw).test(text)) hits.push(`"${kw}" (topic ${t.id})`);
  }
  return hits;
}

/**
 * @param {object} d
 * @param {Array} d.curriculum parsed curriculum.yaml
 * @param {Object<string, object>} d.patterns topic id -> parsed pattern file
 * @param {Object<string, object>} d.banks topic id -> parsed bank file (only topics that have one)
 * @param {Object<string, string|null>} d.notes topic id -> text of notes/bank/{topic}.md (null if missing)
 * @returns {string[]} error messages; empty when everything is valid
 */
export function validateAll({ curriculum, patterns, banks, notes }) {
  const errors = [];
  const err = (file, msg) => errors.push(`${file}: ${msg}`);
  const byId = new Map(curriculum.map((t) => [t.id, t]));

  // Curriculum registry.
  const C = 'src/data/curriculum.yaml';
  curriculum.forEach((t, i) => {
    if (t.order !== i + 1) err(C, `topic ${t.id} has order ${t.order}, expected ${i + 1} (rows must be listed in order)`);
    if (t.phase !== Number(t.id.split('.')[0])) err(C, `topic ${t.id} has phase ${t.phase}`);
    for (const r of t.requires) {
      const rt = byId.get(r);
      if (!rt) err(C, `topic ${t.id} requires unknown topic ${r}`);
      else if (rt.order >= t.order) err(C, `topic ${t.id} requires ${r}, which is not earlier`);
    }
  });
  if (byId.size !== curriculum.length) err(C, 'duplicate topic ids');

  // Pattern files.
  const patternIds = new Map(); // topic -> Set of pattern ids
  for (const t of curriculum) {
    const F = `src/data/bank/patterns/${fileId(t.id)}.yaml`;
    const pf = patterns[t.id];
    if (!pf) {
      err(F, `missing pattern file for topic ${t.id}`);
      continue;
    }
    if (pf.topic !== t.id) err(F, `topic field is "${pf.topic}", expected "${t.id}"`);
    const ids = new Set();
    for (const p of pf.patterns) {
      if (ids.has(p.id)) err(F, `duplicate pattern id ${p.id}`);
      ids.add(p.id);
      const hits = laterKeywordHits(`${p.name} ${p.description} ${p.precondition}`, t.order, curriculum);
      if (hits.length) err(F, `pattern ${p.id} uses later-topic keywords: ${hits.join(', ')}`);
    }
    patternIds.set(t.id, ids);
    if (t.id === '7.8') {
      if (pf.patterns.length) err(F, 'topic 7.8 has no patterns of its own (problems use "{topic}:{pattern-id}")');
    } else if (pf.patterns.length < 3 || pf.patterns.length > 6) {
      err(F, `has ${pf.patterns.length} patterns; 3–6 required`);
    }
  }
  for (const k of Object.keys(patterns)) if (!byId.has(k)) err(`src/data/bank/patterns/${fileId(k)}.yaml`, 'topic not in curriculum');

  // Bank files.
  const seen = new Map(); // problem id -> topic
  const all = new Map(); // problem id -> problem
  for (const [topic, bf] of Object.entries(banks)) {
    const F = `src/data/bank/${fileId(topic)}.yaml`;
    const t = byId.get(topic);
    if (!t) {
      err(F, `topic ${topic} not in curriculum`);
      continue;
    }
    if (bf.topic !== topic) err(F, `topic field is "${bf.topic}", expected "${topic}"`);
    for (const p of bf.problems) {
      if (seen.has(p.id)) err(F, `${p.id} already appears in topic ${seen.get(p.id)} (ids must be unique across the bank)`);
      else seen.set(p.id, topic);
      all.set(p.id, p);
    }
  }

  for (const [topic, bf] of Object.entries(banks)) {
    const F = `src/data/bank/${fileId(topic)}.yaml`;
    const t = byId.get(topic);
    if (!t) continue;
    const is78 = topic === '7.8';
    const note = notes[topic];
    const N = `notes/bank/${topic}.md`;

    for (const p of bf.problems) {
      const P = `${p.id}`;
      // 1. Pattern exists.
      let patternTopic = topic;
      if (is78) {
        const m = /^([0-7]\.[1-8]):(.+)$/.exec(p.pattern);
        if (!m) err(F, `${P}: topic 7.8 patterns must be "{topic}:{pattern-id}"`);
        else {
          patternTopic = m[1];
          const pt = byId.get(m[1]);
          if (!pt || pt.order >= t.order) err(F, `${P}: pattern topic ${m[1]} must be a topic before 7.8`);
          else if (!patternIds.get(m[1])?.has(m[2])) err(F, `${P}: pattern ${p.pattern} does not exist`);
        }
      } else if (!patternIds.get(topic)?.has(p.pattern)) {
        err(F, `${P}: pattern "${p.pattern}" is not in patterns/${fileId(topic)}.yaml`);
      }

      // 2. Id, URL, difficulty, and tier basis match the platform.
      const plat = PLATFORM[p.source];
      const m = plat.id.exec(p.id);
      if (!m) err(F, `${P}: id does not match the ${p.source} id format`);
      else {
        const urlOk = plat.url ? p.url === plat.url(m) : plat.urlPattern(m).test(p.url);
        if (!urlOk) err(F, `${P}: url ${p.url} does not match the ${p.source} URL format`);
      }
      if (!plat.difficulty.test(p.difficulty)) err(F, `${P}: difficulty "${p.difficulty}" is not valid for ${p.source}`);
      if (!plat.bases.includes(p.tier_basis)) err(F, `${P}: tier_basis ${p.tier_basis} not allowed for ${p.source} (use ${plat.bases.join(' or ')})`);

      // 6. Techniques never later than this topic; contain the topic itself unless the problem
      // is an intentional earlier-topic partner (later_drill, lookalike).
      for (const tech of p.techniques) {
        const tt = byId.get(tech);
        if (!tt) err(F, `${P}: unknown technique ${tech}`);
        else if (tt.order > t.order) err(F, `${P}: technique ${tech} is later than topic ${topic}`);
      }
      const partner = p.reserved_for === 'later_drill' || p.reserved_for === 'lookalike';
      if (is78) {
        if (!p.techniques.includes(patternTopic)) err(F, `${P}: techniques must include ${patternTopic}, the topic of its pattern`);
      } else if (!partner && !p.techniques.includes(topic)) {
        err(F, `${P}: techniques must include ${topic}`);
      }

      // 7. Look-alike partners point at each other and are both reserved look-alikes.
      if (p.lookalike_of) {
        const q = all.get(p.lookalike_of);
        if (!q) err(F, `${P}: lookalike_of ${p.lookalike_of} does not exist in the bank`);
        else if (q.lookalike_of !== p.id) err(F, `${P}: ${q.id} does not point back via lookalike_of`);
        if (p.reserved_for !== 'lookalike') err(F, `${P}: has lookalike_of, so it must be reserved_for: lookalike`);
      }

      // 8. Codeforces tier matches the rating range for the topic's phase.
      if (p.source === 'codeforces' && /^\d+$/.test(p.difficulty)) {
        const [lo, hi] = cfTierRange(p.tier, t.target_rating, t.phase);
        const r = Number(p.difficulty);
        if (r < lo || r > hi) err(F, `${P}: rating ${r} is outside tier ${p.tier} (${lo}–${hi}) for phase ${t.phase}`);
      }

      // Reserved purposes have their own tier ranges; 7.8 uses tiers 3–5.
      if (is78) {
        if (p.tier < 3) err(F, `${P}: topic 7.8 problems must be tier 3–5`);
      } else if (p.reserved_for) {
        const [a, b] = RESERVED_TIERS[p.reserved_for];
        if (p.tier < a || p.tier > b) err(F, `${P}: reserved_for ${p.reserved_for} needs tier ${a}–${b}, got ${p.tier}`);
      }

      // 9. Solution note exists.
      const heading = new RegExp(`^## ${p.id.replace(/[.*+?^${}()|[\]\\]/g, '\\$&')} `, 'm');
      if (note == null) err(N, `missing (needed for ${P})`);
      else if (!heading.test(note)) err(N, `no "## ${p.id} …" section for ${P}`);
    }

    // 3–5. Counts and composition. A topic still being collected (in_progress) is exempt;
    // `short` documents an accepted shortfall (bank plan Section 11).
    if (bf.status !== 'complete') continue;
    const practice = bf.problems.filter((p) => p.set === 'practice');
    const reserved = bf.problems.filter((p) => p.set === 'reserved');

    if (is78) {
      if (bf.problems.length < 40) err(F, `topic 7.8 needs 40 problems, has ${bf.problems.length}`);
      if (practice.length) err(F, 'topic 7.8 problems must all be reserved');
      const perPhase = new Map();
      const perTopic = new Set();
      for (const p of bf.problems) {
        const pt = p.pattern.split(':')[0];
        perTopic.add(pt);
        const ph = byId.get(pt)?.phase;
        perPhase.set(ph, (perPhase.get(ph) ?? 0) + 1);
      }
      for (let ph = 0; ph <= 7; ph++) if ((perPhase.get(ph) ?? 0) < 2) err(F, `topic 7.8 needs at least 2 problems from phase ${ph}`);
      for (const x of curriculum) if (x.phase >= 1 && x.phase <= 6 && !perTopic.has(x.id)) err(F, `topic 7.8 needs at least 1 problem for topic ${x.id}`);
      continue;
    }

    if (practice.length < 20) err(F, `practice set has ${practice.length} problems; at least 20 required`);
    if (reserved.length < 24) err(F, `reserved set has ${reserved.length} problems; at least 24 required`);

    for (const pat of patternIds.get(topic) ?? []) {
      const ps = practice.filter((p) => p.pattern === pat);
      const tiers = new Set(ps.map((p) => p.tier));
      if (ps.length < 4 || tiers.size < 3)
        err(F, `pattern ${pat}: ${ps.length} practice problems over ${tiers.size} tiers; need ≥ 4 over ≥ 3 tiers`);
    }
    const platforms = new Map();
    for (const p of practice) platforms.set(p.source, (platforms.get(p.source) ?? 0) + 1);
    if (platforms.size < 2) err(F, 'practice set uses fewer than two platforms');
    for (const [s, c] of platforms)
      if (practice.length && c / practice.length > 0.6) err(F, `practice set is ${Math.round((100 * c) / practice.length)}% ${s}; at most 60% allowed`);

    for (const [purpose, min] of Object.entries(RESERVED_MIN)) {
      const c = reserved.filter((p) => p.reserved_for === purpose).length;
      if (c < min) err(F, `reserved_for ${purpose}: ${c} problems; at least ${min} required`);
    }
    const covered = new Set(reserved.filter((p) => p.reserved_for === 'checkpoint' || p.reserved_for === 'review').map((p) => p.pattern));
    for (const pat of patternIds.get(topic) ?? [])
      if (!covered.has(pat)) err(F, `pattern ${pat} appears in no checkpoint or review problem`);
  }

  return errors;
}

/** Practice problems of one topic, grouped by tier, then by pattern order, then difficulty, then id. */
export function practiceByTier(bank, patternFile) {
  const order = new Map((patternFile?.patterns ?? []).map((p, i) => [p.id, i]));
  const num = (d) => (/^-?\d+$/.test(d) ? Number(d) : { Easy: 1, Medium: 2, Hard: 3 }[d] ?? 0);
  const tiers = [1, 2, 3, 4, 5].map((tier) => ({ tier, name: TIER_NAMES[tier - 1], problems: [] }));
  for (const p of bank?.problems ?? []) if (p.set === 'practice') tiers[p.tier - 1].problems.push(p);
  for (const t of tiers)
    t.problems.sort(
      (a, b) =>
        (order.get(a.pattern) ?? 99) - (order.get(b.pattern) ?? 99) ||
        num(a.difficulty) - num(b.difficulty) ||
        (a.id < b.id ? -1 : a.id > b.id ? 1 : 0),
    );
  return tiers;
}
