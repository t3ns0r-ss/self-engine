# Brief for a Phase 2 restore agent (writes the lesson and its inventory only)

Repo: /home/user/self-engine, branch claude/vigilant-hypatia-iyajxg. You edit ONLY: your lesson file(s) under src/content/docs/, your docs/restore/<id>.md, and new code units under code/<topic>/ if truly needed. No git commit/push. No edits to validators, other lessons, yaml data, PROGRESS.md.

Read first: LESSON_RESTORE_PLAN.md Sections 3, 4.1, 4.2, 4.3 and Phase 2; docs/LESSON_STYLE_GUIDE.md (5, 5A); docs/restore/<id>.md (your inventory); his current lesson in full; the old lesson via `git show 1d76f35:<path>` (3.1: `git show e5d3412:...`); the old data in src/data/topics/<id>.yaml.

Task: for EVERY partial and missing row of your inventory, write the idea INSIDE the lesson section named in the row, in his notes voice (concrete numbers first, brute force to better, short sentences, dry run before code, plain global English, no Hinglish). Theorems use the 4.2 format with number, statement, tiny example, every proof step, "This proof needs" list; add `<TheoremCode unit="..."/>` only if the unit adds something his function does not (import it as the other lessons do; check how). Common-mistake paragraphs carry a failing input and the fix. Worked examples follow example, idea (6-step recognition: budget, tools, deciding property), trace, code, cost, mistake. Maths in `$...$` per 4.3; bold only at definitions; code names in backticks.

Also build the target shape (Section 3): `## What this note covers` gets his overview plus old motivation (with numbers), `<WhatYouNeed topic="X"/>`, old scope ("does not cover"), and "Terms used in this lesson" definitions; then ToC (add new sections to it); technique sections; `## Recognition cards` with one line + `<Cards topic="X"/>` (after his first "how to recognise" section, else before Quick revision); `## Quick revision` extended by one line per restored theorem; `## Check yourself` with `### Identification drill` `<Drill topic="X"/>`, `### Look-alike pairs` `<LookalikePairs topic="X"/>`, `### Self-test` `<SelfTest topic="X"/>`, `### Checkpoint` `<Checkpoint topic="X"/>`, `### Decision map update` `<DecisionMapUpdate topic="X"/>`; `## Practice problems` LAST: keep his existing content there as is (Phase 4 replaces it). Check prop names/imports against an existing component use (grep src/components and the old lesson at 1d76f35) and add imports as needed.

Rules: never edit, delete or reword his content or any of his code blocks (additions only; restored text sits beside his). No duplicates: if his note says the same, keep his and add only the missing part. Contradictions (listed at the end of your inventory) and "Uses a later topic" ideas are NOT restored; leave those rows as they are (status contradiction / later). Convention-only differences: his wins. Any new code must compile and run (`bash scripts/test_units.sh code`). Update each restored row to status `added` with `"New Heading"` (heading must exist in the lesson); rows that are really present stay present with a quote.

Checks to run and pass before finishing:
- `node scripts/check_ideas.mjs <id>` (no missing/partial left except contradiction/later rows; try --strict and report what remains)
- `node scripts/check_code_unchanged.mjs 1d76f35 <lesson>` is for old code; instead verify his code unchanged with `git diff -U0 HEAD -- <lesson>`: no removed lines except none. Removed lines must be zero.
- `node scripts/check_english.mjs --tone <lesson>` clean
- `node scripts/check_depth.mjs --report` shows your lesson ok
- `NOTES_V2=1 node scripts/validate.mjs` has no errors for your lesson (build may be run by main session, do not run astro build).
Report in under 80 words: rows added, rows left (why), new units, any problems.
