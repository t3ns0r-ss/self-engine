// Types of the design-track topic data files (DESIGN_TRACKS_PLAN.md Section 7.2); the zod schema is designTopicFile.
export type CardRef = { topic: string; card: string };
export type DesignClaim = {
  id: string; kind: 'proved' | 'computed' | 'simulated' | 'measured' | 'experimented' | 'cited';
  title: string; plain_words: string; evidence: string[];
  source: { title: string; url: string; accessed: string; section: string } | null;
};
export type DesignCard = {
  id: string; name: string; force?: string; need?: string; decisive_property: string; from_claim: string; how_to_test: string;
  trade_off_table?: { units: string[]; overhead: string; per_change: string; blast_radius: string; verdict: string };
  capacity_table?: { units: string[]; threshold: string; price: string };
  lab?: { unit: string; holds_test: string; breaks_test: string };
  constraint_shapes: string[];
  weak_signals: { form: string; shape: string }[];
  kill_signals: string[];
  in_action: { statement: string; constraints: string; budget: string; candidates: { tool: string; verdict: 'chosen' | 'rejected'; because: string }[]; property_check: string; decision: string };
  examples: {
    positive: { inline: { input: string; answer: string; why: string } }[];
    negative: { inline: { input: string; answer: string; why: string }; correct_tool: CardRef | { simplest: string } }[];
  };
  lookalikes: { description: string; tool: CardRef; flipping_difference: string }[];
  cost: string;
};
export type DesignTopicFile = {
  id: string; track: 'lld' | 'hld'; uses: { topic: string; what: string }[]; claims: DesignClaim[]; cards: DesignCard[];
  lookalike_pairs: { a: string; b: string; a_tool: CardRef | string; b_tool: CardRef | string; flipping_difference: string; flipping_input?: string }[];
  self_test: { q: string; a: string }[];
  decision_map: { weak_signal: string; choose: string; when: string; over: { topic?: string; card: string; because: string }[] }[];
  glossary_added: string[];
};
