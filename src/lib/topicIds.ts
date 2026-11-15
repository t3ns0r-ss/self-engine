// Renumbering of the CP topic ids on 2026-11-15: the numbers now follow the reading order (`order` in
// src/data/curriculum.yaml). Learner data saved under the old ids is moved to the new ids once.
// Pure functions only, so that node tests can import this file directly.

/** Version of the id scheme. Data without `settings.idScheme === ID_SCHEME` uses the old ids (scheme 1). */
export const ID_SCHEME = 2;

/** Old topic id to new topic id. Ids that did not change are not listed. The map is a permutation: apply it once. */
export const OLD_TO_NEW: Readonly<Record<string, string>> = {
  '2.5': '2.3', '2.6': '2.4', '2.3': '2.5', '2.4': '2.6',
  '3.9': '3.2', '3.2': '3.3', '3.3': '3.4', '3.4': '3.5', '3.5': '3.6', '3.6': '3.7', '3.7': '3.8', '3.8': '3.9',
  '4.9': '4.4', '4.4': '4.5', '4.5': '4.6', '4.6': '4.7', '4.7': '4.8',
  '5.5': '5.4', '5.4': '5.5',
  '7.10': '7.2', '7.2': '7.3', '7.3': '7.4', '7.4': '7.5', '7.5': '7.6', '7.6': '7.7', '7.7': '7.8', '7.8': '7.10',
};

export const renumberTopicId = (id: string): string => (Object.prototype.hasOwnProperty.call(OLD_TO_NEW, id) ? OLD_TO_NEW[id] : id);

/** A drill answer is stored as "{topic}:{card}" (CP) or "{topic}/{card}" (design tracks, ids that start with a letter). */
export function renumberCardValue(v: unknown): unknown {
  if (typeof v !== 'string') return v;
  const m = /^(\d+\.\d+):(.*)$/s.exec(v);
  return m ? `${renumberTopicId(m[1])}:${m[2]}` : v;
}

const isObj = (v: unknown): v is Record<string, unknown> => !!v && typeof v === 'object' && !Array.isArray(v);

export interface ProgressParts {
  topics?: unknown;
  drills?: unknown;
  settings?: unknown;
}

/**
 * Moves the topic-keyed parts of stored progress from the old ids to the new ones and marks the result with the
 * current scheme. Keys that hold problem ids (problems, drills, exams by phase, shown, profiles) are not touched,
 * except that the answer of a drill item names a card as "{topic}:{card}". Inputs are not modified.
 */
export function migrateProgress(p: ProgressParts): { topics: unknown; drills: unknown; settings: Record<string, unknown> } {
  let topics = p.topics;
  if (isObj(topics)) {
    const out: Record<string, unknown> = {};
    for (const [k, v] of Object.entries(topics)) out[renumberTopicId(k)] = v;
    topics = out;
  }
  let drills = p.drills;
  if (isObj(drills)) {
    const out: Record<string, unknown> = {};
    for (const [k, v] of Object.entries(drills)) out[k] = isObj(v) && 'chosenCard' in v ? { ...v, chosenCard: renumberCardValue(v.chosenCard) } : v;
    drills = out;
  }
  const settings: Record<string, unknown> = isObj(p.settings) ? { ...p.settings } : {};
  const cur = settings.currentTopic;
  if (typeof cur === 'string') settings.currentTopic = renumberTopicId(cur);
  else if (isObj(cur) && typeof cur.cp === 'string') settings.currentTopic = { ...cur, cp: renumberTopicId(cur.cp) };
  settings.idScheme = ID_SCHEME;
  return { topics, drills, settings };
}
