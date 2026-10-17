// Browser-side helpers for the design components: reserved items and the card list (fetched on demand, never in built HTML).
import { url } from './url';
import type { Checker } from './exercises';

export type ReservedItem = {
  id: string; globalId: string; topic: string; track: 'lld' | 'hld'; role: string; type: string; title: string; prompt: string;
  answer?: { kind: 'card'; card: { topic: string; card: string }; property: string; why_others_fail: string } | { kind: 'none'; simplest: string; why: string } | null;
  checkers?: Checker[]; clarifying?: { q: string; a: string; critical: boolean }[]; time_limit_minutes?: number | null; review_set?: number | null;
  run?: string; reference?: string;
};
export type CardOption = { topic: string; card: string; name: string; order: number };

export async function fetchReserved(topic: string): Promise<ReservedItem[]> {
  const r = await fetch(url(`/data/reserved/${encodeURIComponent(topic)}.json`));
  if (!r.ok) throw new Error(`HTTP ${r.status}`);
  return (await r.json()) as ReservedItem[];
}
export async function fetchCards(track: string): Promise<CardOption[]> {
  const r = await fetch(url(`/data/cards/${track}.json`));
  if (!r.ok) throw new Error(`HTTP ${r.status}`);
  return (await r.json()) as CardOption[];
}

/** Rubric score as a percentage: sum of weight x score / 2 (Section 10.7). */
export function rubricPercent(criteria: { id: string; weight: number }[], scores: Record<string, { score: number }>): number {
  return criteria.reduce((a, c) => a + (c.weight * (scores[c.id]?.score ?? 0)) / 2, 0);
}
/** Pass rule of Section 8.13 for the rubric part: at least 70%, every critical criterion at least 1 with an evidence note. */
export function rubricPasses(criteria: { id: string; weight: number; critical: boolean }[], scores: Record<string, { score: number; evidence: string }>, criticalWhen: Record<string, boolean> = {}): boolean {
  if (rubricPercent(criteria, scores) < 70) return false;
  return criteria.every((c) => !(c.critical || criticalWhen[c.id]) || ((scores[c.id]?.score ?? 0) >= 1 && (scores[c.id]?.evidence ?? '').trim().length > 0));
}
/** Numeric check of Section 10.7: pass if answer / reference is between 1/factor and factor. */
export function numericOk(answer: number, reference: number, factor = 2): boolean {
  if (!(answer > 0) || !(reference > 0)) return false;
  const r = answer / reference;
  return r >= 1 / factor && r <= factor;
}
/** Phase shares of Section 11.2, as [label, percent] pairs. */
export const TIMER_PHASES: Record<string, [string, number][]> = {
  hld_full: [['Requirements', 10], ['Estimation', 10], ['API and data', 20], ['High-level design', 25], ['Deep dive', 25], ['Bottlenecks', 10]],
  hld_deep: [['Requirements', 15], ['Mechanism', 60], ['Failure and trade-offs', 25]],
  lld_build: [['Clarify', 10], ['Entities and interfaces', 20], ['Code', 55], ['Extend and test', 15]],
};
export function timerKind(track: string, type: string): keyof typeof TIMER_PHASES | null {
  if (track === 'hld' && (type === 'mock' || type === 'scale_ladder')) return 'hld_full';
  if (track === 'hld' && type === 'deep_dive') return 'hld_deep';
  if (track === 'lld' && (type === 'build' || type === 'mock')) return 'lld_build';
  return null;
}
/** Index of the phase active after `elapsedMin` of `totalMin`. */
export function phaseAt(kind: keyof typeof TIMER_PHASES, elapsedMin: number, totalMin: number): number {
  let acc = 0;
  const ph = TIMER_PHASES[kind];
  for (let i = 0; i < ph.length; i++) { acc += (ph[i][1] / 100) * totalMin; if (elapsedMin < acc) return i; }
  return ph.length - 1;
}
/** Log-scale spacing: is the guess within one order of magnitude of the value? */
export const withinOneOrder = (guess: number, value: number) => guess > 0 && value > 0 && Math.abs(Math.log10(guess / value)) <= 1;
