// Loads every exercise file at build time and splits practice from reserved items.
import { parse } from 'yaml';

export type Checker =
  | { kind: 'kit'; path: string }
  | { kind: 'numeric'; calc: string; key: string; unit: string; factor?: number }
  | { kind: 'rubric'; id: string };
export type Exercise = {
  id: string; role: string; type: string; title: string; prompt: string;
  topic: string; track: 'lld' | 'hld'; globalId: string;
  card?: string | null; rung?: number | null; new_force?: string | null; needs_new_structure?: boolean;
  clarifying?: { q: string; a: string; critical: boolean }[]; checkers?: Checker[]; run?: string; reference?: string;
  alternatives?: string[]; hints?: string[]; time_limit_minutes?: number | null; techniques?: string[]; checked_on?: string;
};

const PRACTICE = new Set(['ladder', 'worked_example']);

// import.meta.glob reads the files when the site is built; '?raw' gives the file text.
const files = import.meta.glob('/src/data/exercises/*.yaml', { query: '?raw', import: 'default', eager: true }) as Record<string, string>;

export function allExercises(): Exercise[] {
  const out: Exercise[] = [];
  for (const [path, text] of Object.entries(files)) {
    if (path.endsWith('INVENTORY.yaml')) continue;
    const data = parse(text) as { topic: string; exercises: Omit<Exercise, 'topic' | 'track' | 'globalId'>[] };
    const track = data.topic.startsWith('L') ? 'lld' : 'hld';
    for (const e of data.exercises) out.push({ ...e, topic: data.topic, track, globalId: `${data.topic}/${e.id}` });
  }
  return out;
}

export const isPractice = (e: Exercise) => PRACTICE.has(e.role);
