// Loads curriculum, patterns, and bank collections and runs the cross-file validation
// (PROBLEM_BANK_PLAN.md Section 10) so `astro build` fails on invalid data.
import { getCollection } from 'astro:content';
import { existsSync, readFileSync } from 'node:fs';
import { validateAll } from './validate.mjs';

export type Topic = { order: number; id: string; phase: number; slug: string; title: string; requires: string[]; keywords: string[]; target_rating: [number, number] };
export type Pattern = { id: string; name: string; description: string; precondition: string };
export type BankProblem = {
  id: string; source: 'codeforces' | 'atcoder' | 'cses' | 'leetcode'; title: string; url: string; difficulty: string;
  tier: number; tier_basis: string; pattern: string; set: 'practice' | 'reserved'; reserved_for: string | null;
  lookalike_of: string | null; techniques: string[]; checked_on: string;
};
export type BankFile = { topic: string; status: 'in_progress' | 'complete' | 'short'; problems: BankProblem[] };

let cache: Promise<{ curriculum: Topic[]; patterns: Record<string, { topic: string; patterns: Pattern[] }>; banks: Record<string, BankFile>; lessons: Set<string> }> | undefined;

export function loadData() {
  cache ??= (async () => {
    const curriculum = (await getCollection('curriculum')).map((e) => e.data as Topic).sort((a, b) => a.order - b.order);
    const patterns = Object.fromEntries((await getCollection('bankPatterns')).map((e) => [e.data.topic, e.data]));
    const banks = Object.fromEntries((await getCollection('bank')).map((e) => [e.data.topic, e.data as BankFile]));
    const notes = Object.fromEntries(
      Object.keys(banks).map((t) => {
        const p = `notes/bank/${t}.md`;
        return [t, existsSync(p) ? readFileSync(p, 'utf8') : null];
      }),
    );
    const errors = validateAll({ curriculum, patterns, banks, notes });
    if (errors.length) throw new Error(`Data validation failed:\n${errors.map((e) => `  - ${e}`).join('\n')}`);
    const lessons = new Set((await getCollection('docs')).map((e) => (e.data as { topic?: string }).topic).filter((t): t is string => !!t));
    return { curriculum, patterns, banks, lessons };
  })();
  return cache;
}

/** Practice problems only. Reserved problems must never reach a bank page (bank plan Section 9.1). */
export function practiceOf(bank: BankFile | undefined): BankProblem[] {
  return (bank?.problems ?? []).filter((p) => p.set === 'practice');
}

export const topicSlug = (id: string) => id.replace('.', '-');
export const PHASE_NAMES = ['Foundations', 'Array techniques', 'Mathematics I', 'Recursion to dynamic programming', 'Graphs', 'Range data structures', 'Strings', 'Integration'];
