// Learner data in localStorage with versioned keys (PLAN.md Section 10). Every read and write is
// wrapped in try/catch: storage can be missing, full, or blocked, and the site must still render.

export const KEYS = {
  problems: 'cp:v1:problems',
  topics: 'cp:v1:topics',
  drills: 'cp:v1:drills',
  contests: 'cp:v1:contests',
  settings: 'cp:v1:settings',
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
