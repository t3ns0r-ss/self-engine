# Brief for an inventory agent (Phase 1, read-only on lessons)

Repo: /home/user/self-engine. You write ONLY `docs/restore/<topic-id>.md` files. Do not edit lessons, data files or code. Do not run git commit or push.

Goal: list every idea of the OLD template lesson that is not (fully) in the CURRENT notes lesson, so a later phase can restore it.

Read first: LESSON_RESTORE_PLAN.md Sections 1.2, 3 and Phase 1; docs/restore/README.md (table format).

Inputs for topic X (file ids like 1-4):
- Old lesson: `git show 1d76f35:<lesson path>` (for 3.1 use `git show e5d3412:src/content/docs/phase-3/3-1-backtracking.mdx`). Lesson paths are in LESSON_RESTORE_PLAN.md Section 1.1.
- Old data that the old lesson rendered: `src/data/topics/<id>.yaml` (theorems with plain_words/preconditions, cards, drill, lookalike_pairs, self_test, checkpoint, decision_map). Cards, drill, look-alike pairs, self-test, checkpoint and decision-map items are NOT on the notes page yet, so each is `missing` (group small items: one row per card, per theorem, per drill item set is fine, but never fewer rows than distinct ideas; one row per self-test question and per look-alike pair).
- Current lesson: the file in src/content/docs/ (read all of it, with line numbers).
- Theorem code units: code/<topic>/thm-*/ (mention the unit in the theorem row).

One row per old idea. Cover all of: the motivation (Why this topic exists, with its numbers), scope (what you need / does not cover), each definition, each theorem (statement, tiny instance, each proof step group, the "this proof needs" list, code unit; use separate rows for statement, proof, needs list), each template, each bug catalogue entry, each worked example (and its 6-step recognition reasoning), each card, drill items, look-alike pairs, self-test questions, checkpoint, decision-map lines. Also ladder-only content is out of scope.

Status: present (his note says it completely, even in different words; quote where), partial (say exactly what is missing), missing, duplicate (same as something present; say which). Last column format (the checker reads it): for present/partial give the current lesson heading in double quotes, e.g. `"Finding first 1"`, or `line ~123`; for missing write `→ add in "Heading"` naming the existing section of the current lesson it belongs in (or "What this note covers" for motivation/scope/definitions); for duplicate give the reason.

Separately, at the end of the file add two short lists: "Contradicts his note" (any old idea that conflicts with the current lesson: different bound, convention, number; quote both) and "Uses a later topic" (old ideas that need topics after this one; they stay out). Write "none" if empty.

Be accurate: open the old lesson text and the current text; do not guess. Header of file: `# Inventory <topic id> <title>` and a totals line `Totals: present N, partial N, missing N, duplicate N`. Finish by running `node scripts/check_ideas.mjs <topic ids>` and fix format problems it reports (row numbers must be integers starting at 1; table must have 6 columns; "|" inside a cell must be escaped). Report: totals per topic and any contradictions, in under 100 words.
