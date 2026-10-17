# Developer guide (for an agent that must add features or content)

Read this first, then skim `PLAN.md` (the spec; `CLAUDE.md` and `AGENTS.md` say to follow it exactly). Everything below is verified against the repository as of the end of milestone M9.

## 1. What this is

A self-study competitive programming course published as a static site: **Astro + Starlight + React islands**, KaTeX for maths, all learner data in browser `localStorage` (no server). Live at https://t3ns0r-ss.github.io/self-engine/ (GitHub Pages, `.github/workflows/pages.yml`).

Content: **48 topics in 8 phases** (0 Foundations, 1 Core algorithms, 2 Number theory and counting, 3 DP, 4 Graphs and trees, 5 Range data structures, 6 Strings, 7 Combinations and recognition). Every topic has a lesson, a data file, tested code units and a problem bank. Spec revision: **2.1** (each lesson follows a 14-section template; Phase 7 lessons open with "This topic combines X and Y.").

## 2. Status

All 48 topics, all phase intros and exams, and the e2e suite are done. All review gates are approved by the owner (Saurabh). New work is feature work or content fixes, not the original milestones. `PROGRESS.md` is the running log (gates, per-topic status, bank table, and a long "Questions for Saurabh" list of weak points per topic). `FEEDBACK.md` is where the owner writes feedback: read it at the start of every session and act on it.

## 3. Quick start

```
npm install
npm run dev                     # http://localhost:4321, live reload
npm run build                   # validate + check problem-bank/ is current + astro build + check built pages
npm run preview
npm test                        # node --test tests/*.test.mjs (71 validator tests)
bash scripts/test_units.sh code/7.7     # compile + fixed tests + 5000 random cases vs brute, for one topic
bash tests/e2e.sh               # Playwright, ~10 min; builds twice (real site, then placeholder topic)
npm run bank:md                 # regenerate problem-bank/*.md from src/data/bank (never hand-edit them)
node scripts/fetch_problem.mjs <id>     # read a problem statement (ids like lc-slug, ac-abc123_a, cses-1234)
```

- `test_units.sh` is slow: run it in the background and poll a log. It keeps `.unit-stamps/` so unchanged units are skipped.
- Mermaid diagrams (design lessons) are rendered to inline SVG at build time by `rehype-mermaid`, which launches Chromium only when a page has a diagram. Without a browser a build that contains a diagram fails; CI installs Chromium in the check and deploy jobs. The project pins `playwright` to the version whose browser is installed. `astro preview` can take ~25 s to answer the first request here; the e2e scripts wait up to 2 minutes.
- Playwright is preinstalled in the cloud image (Chromium at `/opt/pw-browsers`); do not run `playwright install`.
- CI (`ci.yml`) runs `npm test`, `npm run build` and the e2e on every push. It does **not** run `test_units.sh`; you must.

## 4. Where things live

| Path | What |
|---|---|
| `PLAN.md`, `PROBLEM_BANK_PLAN.md` | the specs (lesson template, data schema, validator rules, bank rules) |
| `src/data/curriculum.yaml` | the 48 topics (`order`, `id`, `phase`, `slug`, `title`, `requires`, `target_rating`). Edit `requires` here, not in PLAN.md |
| `src/data/bank/{id}.yaml`, `src/data/bank/patterns/{id}.yaml` | the problem bank and its patterns, per topic (`7.8` patterns are `topic:pattern`) |
| `notes/bank/{id}.md` | private solution note for every bank problem (not on the site) |
| `problem-bank/` | generated readable lists |
| `src/data/topics/{id-with-dash}.yaml` | everything structured in a lesson: `uses`, `theorems`, `cards`, `problems` (by role), `drill`, `lookalike_pairs`, `self_test`, `checkpoint`, `decision_map`, `glossary_added` |
| `src/content/docs/phase-N/N-M-slug.mdx` | lesson prose; `phase-N/index.mdx` intro; `phase-N/exam.mdx` exam; `method.mdx` |
| `code/{topic}/{unit}/` | tested C++ units: `solution.cpp`, `brute.cpp`, `gen.cpp`, `tests/*.in|out` |
| `src/lib/schemas.mjs` | Zod schemas (bank, topic file). `validate.mjs` bank rules; `validate-topics.mjs` + `validate-r2.mjs` topic and lesson rules |
| `src/components/`, `src/pages/` | lesson components (`Cards`, `Ladder`, `Drill`, `Checkpoint`, `TopicHeader`, `PhaseExam`, ...) and pages (dashboard, handbook, glossary, problems, contests, progress, bank, review) |
| `src/lib/storage.ts`, `useStore.ts` | all browser storage, versioned keys `cp:v1:*` |
| `tests/` | validator tests, `e2e/` browser scripts, `placeholder/` (temporary fake topic, never committed into `src/`) |

Naming: topic `1.3` -> `1-3.yaml`, `phase-1/1-3-two-pointers.mdx`, `code/1.3/`, `notes/bank/1.3.md`.

## 5. The data model in one page

**Bank problem** (`src/data/bank/{id}.yaml`): `id` (globally unique, platform prefix: `cf-1234A`/`cf-1234`, `ac-abc123_f`, `cses-1234`, `lc-slug`), `source`, `title`, `url`, `difficulty`, `tier` 1-5, `tier_basis`, `pattern`, `set` (`practice` or `reserved`), `reserved_for` (`drill`, `later_drill`, `lookalike`, `checkpoint`, `review`, `exam`), `lookalike_of`, `techniques` (topic ids it uses), `checked_on`, `source_check` (`page` or `api`).
- Practice problems feed ladders and worked examples; reserved ones feed the other roles and are used once across the whole bank.
- **Phase 7 tiers** (rating 2000-2400): tier 1 below 1800, 2 = 1800-2000, 3 = 2000-2400, 4 = 2400-2600, 5 = 2600-2800. Reserved roles: review tier 3-4, drill 2-4, checkpoint 3-4. Unrated Codeforces problems are not allowed.
- **Techniques** must include the topic itself (look-alike partners and `later_drill` are exempt). Phase 7 ladder and worked problems must list **every** `requires` id of the topic as a technique.
- Codeforces statements cannot be read from the build environment (only API title, rating, tags). Those problems are marked `source_check: api`, their notes and hints are "recalled" and flagged with **†** in prose; links open for the owner. Use another problem if a link is bad.

**Topic file roles** (`problems[].role`): `worked_example`, `ladder` (needs `card`, `rung`, `twist`, 3 `hints`), `drill`, `lookalike`, `checkpoint` (`card`), `review` (`card`, `review_set` 1-3), `exam`. Count rules enforced: 3-6 cards; ladder 12-20 with >= 3 per card, difficulty non-decreasing per platform along rungs; drill 8-12 with >= 3 answered by earlier topics; 2-4 look-alike pairs; 5-8 self-test questions; exactly 3 checkpoint problems, 90/120/150 minutes by phase (<=1 / <=4 / 5+); review sets 1-3 with 3-4 problems each; the phase's last topic holds 6-10 `exam` problems with at least one from every topic of the phase.
- `uses` must contain every `requires` id plus every topic named by a card's `correct_tool`/look-alike, a drill answer, a decision-map `over`, a linked lesson, or a cited `Theorem x.y.z`.
- A card needs >= 2 positive and >= 2 negative examples, at least one inline of each. Inline numbers must match the card example unit's printed `P1 brute=.. method=..` lines in `code/{topic}/card-{id}/tests/1.out` (the validator checks them).
- Negative `correct_tool` and drill answers must be a card of this or an earlier topic. A lesson may link and cite only earlier topics (outside "What this topic does not cover"); a keyword scan rejects later-topic terms.
- **Topic 7.8 is special**: no cards, theorems, templates or ladder; its checkpoint/review/exam problems name a card of the earlier topic they test. The page code and validator have 7.8 exceptions for this.

**Lesson** headings (exact, in order): `## 1. Why this topic exists`, `## 2. Prerequisites and scope` (with `### What you need` rendered by `<WhatYouNeed />` and `### What this topic does not cover`), `## 3. Definitions`, `## 4. Theory and proofs`, `## 5. Recognition Cards`, `## 6. Templates`, `## 7. Bug catalogue`, `## 8. Worked examples` (each `### Example n` has the six `#### Step` headings), `## 9. Problem ladder` ... `## 14. Decision map update`. Theorems: `**Theorem N.M.k ...**` followed by a `:::tip[In plain words]` block (must repeat `plain_words` from the data file), numbered proof (<= 8 steps) and a `:::note[This proof needs]` box, then `<TheoremCode unit="..." />`; theorem code snippets are <= 30 lines between `// snippet:begin` / `// snippet:end`.

**Code units**: template and example units need brute + gen + >= 3 tests; theorem units have `tests/1.out` (hand-checked examples, nonempty); card units print the P/N lines. Compile flags `-std=c++17 -O2 -Wall -Wextra -Werror`. `gen` takes the seed as `argv[1]`.

## 6. Recipes

**Add a feature or page.** Components are `.astro` (static) with a React `*Island.tsx` for interactivity; data comes from `loadData()` in `src/lib/data.ts`. Persist learner state only through `src/lib/storage.ts`/`useStore.ts` (bump the key version on shape changes and keep import/export on the Progress page working). Add or extend a test in `tests/e2e/` and a validator test if you add a rule. Run `npm test`, `npm run build`, then `bash tests/e2e.sh`.

**Change a validator rule.** Edit `src/lib/validate*.mjs` / `schemas.mjs`, add a case to the matching `tests/*.test.mjs`, then run `node scripts/validate.mjs` over the real data; fix the data rather than weakening the rule unless a spec says otherwise.

**Add problems to a bank.** Append to `src/data/bank/{id}.yaml` (id unique across the whole bank: `grep -rn "id: <id>" src/data/bank`), add a note section in `notes/bank/{id}.md` (budget, idea, techniques, why this topic, tier reasoning), pick a `pattern` that exists in `patterns/{id}.yaml`, run `npm run validate`, then `npm run bank:md`. Check the tier/role/technique rules in section 5.

**Add or rework a topic lesson.** Follow `PLAN.md` Section 13 (10 steps). Practical order that worked: bank -> code units + stress -> theorems (lesson Sections 1-4) -> cards -> templates -> bug catalogue (copy a unit, change one line, run `scripts/stress.sh` to prove the bug is caught) -> worked examples -> topic yaml -> `node scripts/validate.mjs` loop -> `npm run bank:md` -> `bash scripts/test_units.sh code/<topic>` -> `npm run build` -> update `PROGRESS.md` -> commit. The topic yaml is long; previous sessions generated it from a small Python script (dicts -> `yaml.safe_dump(..., sort_keys=False, allow_unicode=True, width=100)`); those scripts lived in a scratch directory and are **not** in the repo, so edit the yaml directly (keep key order and the header comment).

**Add a phase-level page or edit a phase intro/exam.** `src/content/docs/phase-N/index.mdx` and `exam.mdx`; the exam list comes from `exam` problems in the phase's last topic yaml (`<PhaseExam phase={N} />`, shuffled by id hash).

**Profile sync** (`PROFILE_SYNC_PLAN.md`, notes in `docs/sync/API_NOTES.md`). Code is in `src/lib/sync/`: `core.ts` (pure logic, tested), `status.ts` (`computeStatus`; the React hook is `useStatuses`/`useSync` in `useStatuses.ts`), `runner.ts` (network plus storage), `reserved.ts` (compromised problems). Every component shows statuses through `useStatuses()`; reading `.status` from `cp:v1:problems` directly fails build check Y2 (`scripts/check_sync.mjs`). New Codeforces problems need `node scripts/cf_aliases.mjs` (slow; fails build check Y1 otherwise). Node tests import the `.ts` files directly, so sync modules must not use constructor parameter properties, enums, or extensionless relative imports. Browser tests: `tests/e2e/sync.cjs` (part of `tests/e2e.sh`).

## 7. Gotchas learned the hard way

- `tests/e2e.sh` part 2 swaps topic 1.3's files for a placeholder. Any later topic that cites a **1.3 practice problem** (by id) breaks that run; cite problems from other topics.
- The e2e lesson script expects `.ladder` unless the topic has no ladder role (7.8 is skipped by design).
- A topic's header links to `/bank/<topic>/`; 7.8 has no practice problems, so the link is hidden for it.
- `npm run build` fails if `problem-bank/` is stale: run `npm run bank:md` after any bank edit and commit the result.
- Bug "mutations" that do not change behaviour (redundant guards) are not bugs; check with `stress.sh` before writing one up.
- Random tests with small `n` cannot reveal overflow/modulus bugs; show such bugs with a hand-checked input instead and say so.
- Do not use unrated Codeforces problems, and do not copy statements or editorials (one-line own-words summaries only).
- Pronouns: use they/them for anyone whose pronouns are not stated.
- `sleep` may be blocked in the shell: run long jobs in the background and poll a log.

## 8. Known weak points (candidates for future work)

See "Questions for Saurabh" in `PROGRESS.md`. In short: many Codeforces hints/notes are from recalled statements (†) and deserve a spot-check; several short banks (for example 5.4, 6.4, 7.7) and thin tiers; a few review problems have a simpler natural solution; 7.8 uses 27 of its 40 bank problems; 7.7 skews to easier tiers; the glossary got no new terms in 7.5-7.8.

## 9. Git conventions

- Develop on the branch the session names (this work: `claude/problemset-implementation-yja039`); push with `git push -u origin <branch>`. **Do not open a pull request unless asked.**
- Commit messages: `topic(7.7): ...`, `bank(7.7): ...`, `fix(...)`, ending with the attribution lines the session specifies. One logical step per commit; never force-push shared history.
- Before every push: `node scripts/validate.mjs`, `npm test`, `npm run build`, and `bash scripts/test_units.sh code/<changed topic>`. Run `bash tests/e2e.sh` for any component, page or validator change.
- Update `PROGRESS.md` (Now, topic rows, bank table, Questions) with every content change.
