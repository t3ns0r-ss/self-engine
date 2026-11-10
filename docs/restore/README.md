# Idea inventories (LESSON_RESTORE_PLAN.md, Phase 1)

One file per lesson: `docs/restore/<topic-id>.md` (for example `1-4.md`). Table columns:

| # | Old idea | Where in old lesson | Kind | Status | Where now / reason |

- Old lesson: `git show 1d76f35:<lesson path>`; for 3.1 use `git show e5d3412:src/content/docs/phase-3/3-1-backtracking.mdx`.
- Kind: motivation, scope, definition, theorem, proof step, template, bug, worked example, card, drill item, look-alike pair, self-test question, checkpoint item, decision-map line.
- Status: present, partial, missing, duplicate (later also: added, struck, contradiction).
- Last column: for present or partial, the heading of the current lesson in double quotes (`"Finding first 1"`) or `line ~123`, plus what is missing; for missing, `→ add in "Heading"` naming the section it belongs in; for duplicate, why.
- Data-driven items (cards, drill, look-alike pairs, self-test, checkpoint, decision map) are `missing` until the components are back on the page.
- Checked by `node scripts/check_ideas.mjs`.
