// Loads every data collection and runs the cross-file validation (PLAN.md Section 12 and
// PROBLEM_BANK_PLAN.md Section 10), so `astro build` fails on invalid data.
import { getCollection } from 'astro:content';
import { existsSync, readFileSync } from 'node:fs';
import { validateAll } from './validate.mjs';
import { validateTopics } from './validate-topics.mjs';
import { findLessons } from './lessons.mjs';
import { url } from './url';

export type Topic = { order: number; id: string; phase: number; slug: string; title: string; requires: string[]; keywords: string[]; target_rating: [number, number] };
export type Pattern = { id: string; name: string; description: string; precondition: string };
export type Source = 'codeforces' | 'atcoder' | 'cses' | 'leetcode';
export type BankProblem = {
  id: string; source: Source; title: string; url: string; difficulty: string;
  tier: number; tier_basis: string; pattern: string; set: 'practice' | 'reserved'; reserved_for: string | null;
  lookalike_of: string | null; techniques: string[]; checked_on: string; source_check: 'page' | 'api';
};
export type BankFile = { topic: string; status: 'in_progress' | 'complete' | 'short'; problems: BankProblem[] };
export type Ref = { topic: string; card: string };
export type LegacyCard = {
  id: string; name: string; decisive_property: string; from_theorem: string; how_to_test: string;
  weak_signals: string[]; kill_signals: string[];
  lookalikes: { description: string; needs: string; flipping_difference: string }[]; complexity: string;
};
export type PositiveExample = { inline: { input: string; answer: string; why: string } } | { worked_example: string; why: string };
export type NegativeExample =
  | { inline: { input: string; answer: string; method_gives: string; why: string }; correct_tool: Ref }
  | { problem: string; why: string; correct_tool: Ref };
export type CardR2 = {
  id: string; name: string; decisive_property: string; from_theorem: string; how_to_test: string;
  constraint_shapes: string[]; weak_signals: { form: string; shape: string }[]; kill_signals: string[];
  in_action: {
    statement: string; constraints: string; budget: string;
    candidates: { tool: string; verdict: 'chosen' | 'rejected'; because: string }[];
    property_check: string; decision: string;
  };
  examples: { positive: PositiveExample[]; negative: NegativeExample[] };
  lookalikes: { description: string; tool: Ref; flipping_difference: string }[]; complexity: string;
};
export type Card = LegacyCard | CardR2;
export const isCardR2 = (c: Card): c is CardR2 => 'in_action' in c;
/** "Theorem 1.3.1" for either card shape. */
export const theoremLabel = (c: Card) => (c.from_theorem.startsWith('Theorem') ? c.from_theorem : `Theorem ${c.from_theorem}`);
/** One line per weak signal, for the handbook and flashcards. */
export const weakText = (c: Card): string[] => c.weak_signals.map((w) => (typeof w === 'string' ? w : w.form));
export type Role = 'ladder' | 'worked_example' | 'drill' | 'lookalike' | 'checkpoint' | 'review' | 'exam';
export type TopicProblem = {
  id: string; role: Role; card: string | null; rung: number | null; twist: string | null; summary: string;
  hints: string[] | null; editorial_url: string | null; review_set: 1 | 2 | 3 | null;
};
export type TopicFile = {
  id: string; draft: boolean; cards: Card[]; problems: TopicProblem[];
  uses?: { topic: string; what: string }[];
  theorems?: { id: string; title: string; plain_words: string; demo: string }[];
  drill: { problem: string; answer?: Ref; answer_card: string; answer_topic: string; property: string; why_others_fail: string }[];
  lookalike_pairs: { a: string; b: string; a_tool: string | Ref; b_tool: string | Ref; shared_surface?: string; flipping_difference: string; flipping_input?: string }[];
  self_test: { q: string; a: string }[];
  checkpoint: { time_limit_minutes: number; problems: string[] };
  decision_map: { weak_signal: string; choose: string; when: string; over: { topic?: string; card: string; because: string }[] }[];
  glossary_added: string[];
};
export type GlossaryEntry = { term: string; expansion?: string; definition: string; topic: string };

/** A topic problem joined with its bank record: the one source of title, URL, and difficulty. */
export type FullProblem = TopicProblem & Pick<BankProblem, 'source' | 'title' | 'url' | 'difficulty' | 'techniques' | 'checked_on'> & { topic: string };

export type SiteData = {
  curriculum: Topic[];
  patterns: Record<string, { topic: string; patterns: Pattern[] }>;
  banks: Record<string, BankFile>;
  topics: Record<string, TopicFile>;
  glossary: GlossaryEntry[];
  lessons: Record<string, { path: string; text: string }>;
  bankById: Map<string, BankProblem>;
};

let cache: Promise<SiteData> | undefined;

export function loadData(): Promise<SiteData> {
  cache ??= (async () => {
    const curriculum = (await getCollection('curriculum')).map((e) => e.data as Topic).sort((a, b) => a.order - b.order);
    const patterns = Object.fromEntries((await getCollection('bankPatterns')).map((e) => [e.data.topic, e.data]));
    const banks = Object.fromEntries((await getCollection('bank')).map((e) => [e.data.topic, e.data as BankFile]));
    const topics = Object.fromEntries((await getCollection('topics')).map((e) => [e.data.id, e.data as TopicFile]));
    const glossary = (await getCollection('glossary')).map(({ data: { id: _id, ...g } }) => g as GlossaryEntry);
    const notes = Object.fromEntries(
      Object.keys(banks).map((t) => {
        const p = `notes/bank/${t}.md`;
        return [t, existsSync(p) ? readFileSync(p, 'utf8') : null];
      }),
    );
    const { lessons, errors: lessonErrors } = findLessons(process.cwd());
    const errors = [
      ...lessonErrors,
      ...validateAll({ curriculum, patterns, banks, notes }),
      ...validateTopics({ curriculum, patterns, banks, topics, glossary, lessons }),
    ];
    if (errors.length) throw new Error(`Data validation failed:\n${errors.map((e) => `  - ${e}`).join('\n')}`);
    const bankById = new Map<string, BankProblem>();
    for (const b of Object.values(banks)) for (const p of b.problems) bankById.set(p.id, p);
    return { curriculum, patterns, banks, topics, glossary, lessons, bankById };
  })();
  return cache;
}

/** The topic's problems of the given roles, joined with the bank. */
export function problemsOf(data: SiteData, topic: string, roles: Role[]): FullProblem[] {
  const tf = data.topics[topic];
  if (!tf) return [];
  return tf.problems
    .filter((p) => roles.includes(p.role))
    .map((p) => {
      const b = data.bankById.get(p.id)!;
      return { ...p, topic, source: b.source, title: b.title, url: b.url, difficulty: b.difficulty, techniques: b.techniques, checked_on: b.checked_on };
    });
}

/** Practice problems only. Reserved problems must never reach a bank page (bank plan Section 9.1). */
export function practiceOf(bank: BankFile | undefined): BankProblem[] {
  return (bank?.problems ?? []).filter((p) => p.set === 'practice');
}

export const topicSlug = (id: string) => id.replace('.', '-');
export const lessonHref = (t: Topic) => url(`/phase-${t.phase}/${topicSlug(t.id)}-${t.slug}/`);
export const PHASE_NAMES = ['Foundations', 'Array techniques', 'Mathematics I', 'Recursion to dynamic programming', 'Graphs', 'Range data structures', 'Strings', 'Integration'];
export const PLATFORM_NAMES: Record<Source, string> = { codeforces: 'Codeforces', atcoder: 'AtCoder', cses: 'CSES', leetcode: 'LeetCode' };

/** One row per problem the learner can meet: bank practice problems and every problem a topic
 *  file uses. Reserved bank problems that no lesson uses yet are left out on purpose. */
export type IndexedProblem = {
  id: string; title: string; url: string; source: Source; difficulty: string; topic: string;
  role: Role | 'practice'; card: string; cardName: string; reviewSet: number | null;
};

export function problemIndex(data: SiteData): IndexedProblem[] {
  const out = new Map<string, IndexedProblem>();
  for (const [topic, bank] of Object.entries(data.banks)) {
    const names = new Map((data.patterns[topic]?.patterns ?? []).map((p) => [p.id, p.name]));
    for (const p of practiceOf(bank))
      out.set(p.id, { id: p.id, title: p.title, url: p.url, source: p.source, difficulty: p.difficulty, topic, role: 'practice', card: p.pattern, cardName: names.get(p.pattern) ?? p.pattern, reviewSet: null });
  }
  for (const [topic, tf] of Object.entries(data.topics)) {
    const names = new Map(tf.cards.map((c) => [c.id, c.name]));
    const drillCard = new Map(tf.drill.map((d) => [d.problem, d.answer_card]));
    for (const p of tf.problems) {
      const b = data.bankById.get(p.id)!;
      const card = p.card ?? drillCard.get(p.id) ?? b.pattern;
      out.set(p.id, { id: p.id, title: b.title, url: b.url, source: b.source, difficulty: b.difficulty, topic, role: p.role, card, cardName: names.get(card) ?? card, reviewSet: p.review_set });
    }
  }
  return [...out.values()];
}

/** The one list behind both the page header ("Builds on") and "What you need" (PLAN.md Section 6.2). */
export function getUses(data: SiteData, topic: string) {
  return (data.topics[topic]?.uses ?? []).map((u) => {
    const t = data.curriculum.find((x) => x.id === u.topic)!;
    return { topic: u.topic, title: t.title, what: u.what, href: data.lessons[u.topic] ? lessonHref(t) : null };
  });
}
