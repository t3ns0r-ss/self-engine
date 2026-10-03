// Learner data in localStorage with versioned keys (PLAN.md Section 10). Every read and write is
// wrapped in try/catch: storage can be missing, full, or blocked, and the site must still render.

export const KEYS = {
  problems: 'cp:v1:problems',
  topics: 'cp:v1:topics',
  drills: 'cp:v1:drills',
  contests: 'cp:v1:contests',
  settings: 'cp:v1:settings',
  exams: 'cp:v1:exams',
} as const;

export type ProblemStatus = 'attempted' | 'solved' | 'solved_hints' | 'editorial';
export type Mistake = '' | 'recognition' | 'property' | 'implementation' | 'edge_case' | 'complexity';

export const STATUS_LABELS: Record<ProblemStatus, string> = {
  attempted: 'Attempted',
  solved: 'Solved',
  solved_hints: 'Solved with hints',
  editorial: 'Read editorial',
};
export const MISTAKE_LABELS: Record<Exclude<Mistake, ''>, string> = {
  recognition: 'Recognition miss',
  property: 'Property error',
  implementation: 'Implementation bug',
  edge_case: 'Edge case',
  complexity: 'Complexity misjudgement',
};

export interface ProblemLog {
  status?: ProblemStatus;
  hintsOpened: number;
  minutes?: number | null;
  mistake?: Mistake;
  budget?: string;
  candidates?: string;
  property?: string;
  date?: string;
  note?: string;
}

export const CHANGE_EVENT = 'cp-storage-change';

function read<T>(key: string, fallback: T): T {
  try {
    const raw = globalThis.localStorage?.getItem(key);
    return raw ? (JSON.parse(raw) as T) : fallback;
  } catch {
    return fallback;
  }
}

function write(key: string, value: unknown): boolean {
  try {
    globalThis.localStorage?.setItem(key, JSON.stringify(value));
    globalThis.dispatchEvent?.(new CustomEvent(CHANGE_EVENT, { detail: { key } }));
    return true;
  } catch {
    return false;
  }
}

export function getProblems(): Record<string, ProblemLog> {
  const v = read<Record<string, ProblemLog>>(KEYS.problems, {});
  return v && typeof v === 'object' && !Array.isArray(v) ? v : {};
}

/** Merges `patch` into the stored log for `id`; returns false when storage is unavailable. */
export function saveProblem(id: string, patch: Partial<ProblemLog>): boolean {
  const all = getProblems();
  all[id] = { hintsOpened: 0, ...all[id], ...patch };
  return write(KEYS.problems, all);
}

export const isSolved = (log?: ProblemLog) => log?.status === 'solved' || log?.status === 'solved_hints';

export const today = () => new Date().toISOString().slice(0, 10);

// ---- Topics, drills, contests, settings (PLAN.md Section 10) ----

export interface TopicState {
  started?: string;
  checkpointPassedOn?: string | null;
  /** Epoch milliseconds when the checkpoint timer started, so a reload keeps counting. */
  checkpointStartedAt?: number | null;
  /** Problem ids marked solved in the last checkpoint attempt. */
  checkpointSolved?: string[];
  /** True once the timer ran out or the learner finished early, until results are submitted. */
  checkpointFinished?: boolean;
}
/** One phase exam attempt (PLAN.md Section 11.3), keyed by phase number. */
export interface ExamState {
  /** Epoch milliseconds when the exam timer started. */
  startedAt?: number | null;
  /** True once the timer ran out or the learner finished early, until results are submitted. */
  finished?: boolean;
  solved?: string[];
  /** Solved problems where the first tool tried was the wrong one. */
  recognitionMisses?: string[];
  passedOn?: string | null;
  lastAttemptOn?: string | null;
}
export interface DrillState {
  chosenCard?: string;
  property?: string;
  revealed?: boolean;
}
export interface ContestEntry {
  date: string;
  platform: string;
  name: string;
  solved: number;
  upsolved: string[];
  note: string;
}
export interface Settings {
  currentTopic?: string;
}

const asRecord = <T>(v: unknown): Record<string, T> => (v && typeof v === 'object' && !Array.isArray(v) ? (v as Record<string, T>) : {});

export const getTopics = () => asRecord<TopicState>(read(KEYS.topics, {}));
export function saveTopic(id: string, patch: Partial<TopicState>): boolean {
  const all = getTopics();
  all[id] = { ...all[id], ...patch };
  return write(KEYS.topics, all);
}

export const getExams = () => asRecord<ExamState>(read(KEYS.exams, {}));
export function saveExam(phase: string, patch: Partial<ExamState>): boolean {
  const all = getExams();
  all[phase] = { ...all[phase], ...patch };
  return write(KEYS.exams, all);
}
export const getDrills = () => asRecord<DrillState>(read(KEYS.drills, {}));
export function saveDrill(id: string, patch: Partial<DrillState>): boolean {
  const all = getDrills();
  all[id] = { ...all[id], ...patch };
  return write(KEYS.drills, all);
}

export function getContests(): ContestEntry[] {
  const v = read<unknown>(KEYS.contests, []);
  return Array.isArray(v) ? (v as ContestEntry[]) : [];
}
export const saveContests = (list: ContestEntry[]) => write(KEYS.contests, list);

export const getSettings = (): Settings => asRecord<unknown>(read(KEYS.settings, {})) as Settings;
export const saveSettings = (patch: Partial<Settings>) => write(KEYS.settings, { ...getSettings(), ...patch });

// ---- Export, import, reset (PLAN.md Section 10.6) ----

export function exportAll(): Record<string, unknown> {
  const out: Record<string, unknown> = { format: 'cp-training-progress', version: 1, exportedOn: today() };
  for (const k of Object.values(KEYS)) out[k] = read<unknown>(k, null);
  return out;
}

/** Validates an export and replaces all stored data with it. Returns an error message or null. */
export function importAll(data: unknown): string | null {
  if (!data || typeof data !== 'object' || (data as { format?: string }).format !== 'cp-training-progress')
    return 'This file is not a CP Training progress export.';
  const d = data as Record<string, unknown>;
  const isObj = (v: unknown) => v === null || (typeof v === 'object' && !Array.isArray(v));
  for (const k of [KEYS.problems, KEYS.topics, KEYS.drills, KEYS.settings]) if (!isObj(d[k])) return `Field ${k} has the wrong shape.`;
  // Exports made before the phase exams existed have no exams field.
  if (d[KEYS.exams] !== undefined && !isObj(d[KEYS.exams])) return `Field ${KEYS.exams} has the wrong shape.`;
  if (!(d[KEYS.contests] === null || Array.isArray(d[KEYS.contests]))) return `Field ${KEYS.contests} has the wrong shape.`;
  try {
    for (const k of Object.values(KEYS)) {
      if (d[k] === null || d[k] === undefined) globalThis.localStorage?.removeItem(k);
      else globalThis.localStorage?.setItem(k, JSON.stringify(d[k]));
    }
    globalThis.dispatchEvent?.(new CustomEvent(CHANGE_EVENT, { detail: { key: '*' } }));
    return null;
  } catch {
    return 'Browser storage is unavailable, so nothing was imported.';
  }
}

export function resetAll(): boolean {
  try {
    for (const k of Object.values(KEYS)) globalThis.localStorage?.removeItem(k);
    globalThis.dispatchEvent?.(new CustomEvent(CHANGE_EVENT, { detail: { key: '*' } }));
    return true;
  } catch {
    return false;
  }
}

// ---- Schedules (PLAN.md Sections 10.4 and 10.5) ----

export const addDays = (date: string, days: number) => {
  const d = new Date(`${date}T00:00:00Z`);
  d.setUTCDate(d.getUTCDate() + days);
  return d.toISOString().slice(0, 10);
};
export const REVIEW_OFFSETS = { 1: 3, 2: 14, 3: 60 } as const;

/** Due date of a problem's re-solve, or null if none is due (Section 10.5). */
export function resolveDue(log?: ProblemLog): string | null {
  if (!log?.date) return null;
  const needs = log.status === 'editorial' || (log.status === 'solved_hints' && (log.hintsOpened ?? 0) >= 2);
  return needs ? addDays(log.date, 7) : null;
}
