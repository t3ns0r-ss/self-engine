# LESSON_RESTORE_PLAN.md: Bring Back the Old Depth, Format the Maths, Research the Problems

**Audience:** an autonomous coding agent working in the `t3ns0r-ss/self-engine` repository.
**Owner:** Saurabh. He reviews each phase's pull request (PR) and replies "merge" or gives changes.
**Scope:** the 14 notes-format lessons only (list in Section 1.1). The other 34 topics are not touched, except for the shared component change in Phase 0, step 4.

Read `PLAN.md` (especially Section 6A), `DEVELOPER_GUIDE.md`, `docs/LESSON_STYLE_GUIDE.md` and `PROBLEM_BANK_PLAN.md` (Sections 7 and 10) before starting. Every rule there still applies unless this file changes it explicitly.

---

## 0. What Saurabh asked for (his words, summarised)

1. **Keep the old ideas.** Before the 14 lessons were converted to his notes format, each lesson had more ideas in it. Those ideas must be in the lessons again. Write them in his notes style of explanation, but bring back the depth the old lessons had.
2. **Format the maths.** Equations, formulas, symbols and terms must be properly formatted (KaTeX maths, bold terms where they are defined, code names in code font). Today most of them are plain text.
3. **Research the problems.** Every practice problem should be chosen with care and checked. Present problems in the same style as the rest of the lesson. **maang.in is a paid site, so remove all its problems.**

---

## 1. Facts you need

### 1.1 The 14 lessons

| Topic | Lesson file | Data file |
|---|---|---|
| 0.1 | `src/content/docs/phase-0/0-1-cpp-for-cp.mdx` | `src/data/topics/0-1.yaml` |
| 0.2 | `src/content/docs/phase-0/0-2-complexity.mdx` | `0-2.yaml` |
| 0.4 | `src/content/docs/phase-0/0-4-elementary-math.mdx` | `0-4.yaml` |
| 0.6 | `src/content/docs/phase-0/0-6-stl-toolbox.mdx` | `0-6.yaml` |
| 1.2 | `src/content/docs/phase-1/1-2-prefix-sums.mdx` | `1-2.yaml` |
| 1.3 | `src/content/docs/phase-1/1-3-two-pointers.mdx` | `1-3.yaml` |
| 1.4 | `src/content/docs/phase-1/1-4-binary-search.mdx` | `1-4.yaml` |
| 1.5 | `src/content/docs/phase-1/1-5-greedy-1.mdx` | `1-5.yaml` |
| 1.6 | `src/content/docs/phase-1/1-6-monotonic-stack.mdx` | `1-6.yaml` |
| 1.7 | `src/content/docs/phase-1/1-7-bits.mdx` | `1-7.yaml` |
| 2.1 | `src/content/docs/phase-2/2-1-number-theory.mdx` | `2-1.yaml` |
| 2.2 | `src/content/docs/phase-2/2-2-modular-arithmetic.mdx` | `2-2.yaml` |
| 2.3 | `src/content/docs/phase-2/2-3-combinatorics.mdx` | `2-3.yaml` |
| 2.4 | `src/content/docs/phase-2/2-4-expected-value.mdx` | `2-4.yaml` |

The problem bank for each topic is `src/data/bank/<id>.yaml`. Lesson code units for the old template lessons are in `code/<topic>/<unit>/` (for example `code/1.4/thm-1`), tested by `bash scripts/test_units.sh code`.

### 1.2 Where the "previous ideas" are

The old template-format lessons are in git history at commit **`1d76f35`**, the last commit before the notes conversion (`58f0068`). Read one with:

```bash
git show 1d76f35:src/content/docs/phase-1/1-4-binary-search.mdx
```

Each old lesson had these sections (PLAN.md Section 6):
- 1. Why this topic exists.
- 2. Prerequisites and scope ("What you need", "What this topic does not cover").
- 3. Definitions.
- 4. Theory and proofs: numbered theorems, each with a plain-words box, a tiny instance, a numbered proof, a "This proof needs" box and `<TheoremCode>`.
- 5. Recognition Cards (`<Cards>`).
- 6. Templates (`<CodeSnippet>`).
- 7. Bug catalogue.
- 8. Worked examples, using the 6-step method: constraints → budget, question form → candidate tools, property check → decision, proof for this problem, code, alternative approach.
- 9. Problem ladder.
- 10. Identification drill (`<Drill>`).
- 11. Look-alike pairs (`<LookalikePairs>`).
- 12. Self-test (`<SelfTest>`).
- 13. Checkpoint (`<Checkpoint>`).
- 14. Decision map update (`<DecisionMapUpdate>`).

The notes conversion dropped almost all of this from the page. Only `<TopicHeader>` and `<Ladder>` are left. **The data is still there:** every topic YAML file still has `theorems`, `cards`, `problems`, `drill`, `lookalike_pairs`, `self_test`, `checkpoint` and `decision_map`. The components still exist in `src/components/` and the 34 template topics still use them.

Example of what was lost. In topic 1.4, the old lesson stated Theorem 1.4.1 with the invariant "$p(\text{lo})$ is false, $p(\text{hi})$ is true". It then gave a 5-step proof, a "This proof needs" box (monotone predicate, invariant at the start, `mid` strictly inside) and the tested `thm-1` unit. The current lesson has his `firstTrue` / `lastTrue` functions and a list of common mistakes, but no invariant, no proof and no statement of when the search is correct.

### 1.3 How maths is written today

`remark-math` and `rehype-katex` are already set up in `astro.config.mjs`. The old lessons used `$...$` everywhere (for example, 88 lines in the old 1.4). The notes lessons mostly do not. A rough count of unformatted maths tokens (such as `O(...)`, `^`, `⌈ ⌊ Σ √ ≤ ≥ ·`, `log2`, `nCr`) outside code is about **3,900** across the 14 lessons:
- About 1,000 in 1.5 and about 660 in 1.4.
- About 280 to 300 in each of 0.6, 1.7 and 2.1.
- About 100 to 220 in each of the rest.

Some lessons (0.2, 2.1, 2.2, 2.3) already mix KaTeX and plain text. Some prose still has import escapes such as `(A/2B)^\{2/3\}`.

The React and Astro components that render YAML text (Ladder, Cards, Drill, SelfTest, Checkpoint, LookalikePairs) do **not** run KaTeX. Some YAML files (4-2 to 5-4) already contain `$x$`, which probably shows as literal dollar signs today. Check this in Phase 0.

### 1.4 How problems are shown today

Each notes lesson ends with `## Practice problems`:
- First, a raw list of links grouped by site. It was copied from his notes and Fabricator files, then topped up from the bank in an earlier pass.
- Then `### Problem ladder` with `<Ladder topic="…" />`.

The ladder is the researched part. Each rung in the topic YAML has these fields: `card`, `rung`, `twist` (the one new idea this rung adds), `summary` (one line in our own words) and up to 3 `hints`. The ladder also shows "More practice" from the bank. The raw list has none of this, and it holds about 60 maang.in links. maang.in also appears:
- in the body of 0.2 (line ~1509), 1.2 (~1462), 1.3 (~630) and 1.7 (~1231);
- inside one of his Fabricator code comments in 1.3 (`https://maang.in/problems/Number-of-Subarray-with-sum-at-most-K-59`).

Run `grep -n maang src/content/docs/phase-*/*.mdx` for the full list.

### 1.5 Tools and checks that already exist

- `node scripts/validate.mjs` and `npm run build` (about 2 minutes). The build also runs validate, bank and sync checks.
- `node scripts/check_links.mjs`, `node scripts/fetch_problem.mjs [--brief|--full] <ids>`.
- `node scripts/check_english.mjs [--tone] <files>`: plain English, no Hinglish, no shorthand.
- `node scripts/check_depth.mjs [--report]`: prose length against `scripts/lesson_targets.json`.
- `node scripts/check_code_unchanged.mjs <ref> <files>`: every original C++ block is still there word for word.
- `node scripts/check_rewrite.mjs`.
- `npx astro preview --port 4321` then `node tests/e2e/lessons.cjs` (809 checks).
- A render check (open each of the 14 pages and count broken images, `.katex-error` elements and page errors) was used before, but it lived outside the repository. Phase 0 adds it as `tests/e2e/render_check.cjs`.

### 1.6 Environment notes

- From the cloud shell and from WebFetch, leetcode.com, cses.fi and codeforces.com were **not reachable** in earlier sessions. AtCoder and the Codeforces API may work through `fetch_problem.mjs`. Check this first (Section 6, Phase 4).
- `gh pr create` fails (GraphQL is blocked). Use REST:
  - Create a PR: `gh api repos/t3ns0r-ss/self-engine/pulls -f title=… -f head=… -f base=main -f body=…`
  - Merge: `gh api -X PUT repos/t3ns0r-ss/self-engine/pulls/<n>/merge -f merge_method=squash`, only after Saurabh says "merge".
- The CI `browser` job already fails on `main` because of `H4-2.yaml` and `L2-1.yaml`. That is not caused by this work. Say so in each PR rather than fixing it here.

---

## 2. Decisions

Saurabh made these earlier, and they still hold:
- Plain global English on the site. No Hinglish (his preference; `check_english.mjs` enforces it).
- His statements, numbers, formulas and code are never changed in meaning. His code is never edited; a corrected version is added as a new function with a one-line reason.
- Code is shown as functions only: no `main`, no `#include`. Problem statements in code use multi-line comment blocks with no leading `*` on each line.
- Terms are defined before first use. Abbreviations are expanded on first use on each page.
- Figures are generated PNG files, never photos of handwriting.

This plan makes the following decisions. **List them in the Phase 0 PR so Saurabh can overrule them.**
1. **"Previous ideas" means the old template lessons at `1d76f35` plus the YAML data they rendered.** Every idea in them must be present in the new lesson, unless it is a true duplicate of something his note already says. Each idea that is left out needs a written reason.
2. **The data components come back on the notes page** (Cards, Drill, LookalikePairs, SelfTest, Checkpoint, DecisionMapUpdate, and TheoremCode where useful), in the positions given in Section 3. This brings back the old ideas without rewriting them by hand.
3. **maang.in is removed everywhere**: the practice lists, body text, and the URL line inside his code comment in 1.3. This is the only allowed exception to "his code is never edited", because the line is a comment and Saurabh asked for it. Update `check_code_unchanged.mjs` so that it ignores a removed line matching `maang\.in`.
4. **The raw link list is replaced by researched entries.** Each non-maang problem from his notes becomes a ladder rung (with `twist`, `summary` and `hints`) or a "More practice" bank entry. `## Practice problems` then holds a short intro line and `<Ladder>`. Problems that his worked examples solve in the body keep their inline link in the body.
5. **A removed maang problem is replaced only when it was the only practice for an idea.** In that case, find a free problem that tests the same idea (AtCoder, CSES, Codeforces, SPOJ, or a free LeetCode problem) and follow the rules in Phase 4. Otherwise, just remove it.
6. **Maths in YAML text uses `$...$` too.** Phase 0 makes the data components render it.

---

## 3. Target shape of a notes lesson

This changes PLAN.md 6A item 1 and LESSON_STYLE_GUIDE Section 5. Update both in Phase 0.

1. Frontmatter, `<TopicHeader />`, title (unchanged).
2. `## What this note covers`. His overview, plus the old "Why this topic exists" (the motivating example with real numbers), "What you need" (`<WhatYouNeed topic="…" />`), "What this topic does not cover" and the old Definitions. Write the definitions as his "Terms used in this lesson" list: **bold** term, one line, a small example.
3. `## Table of contents` (his).
4. His technique sections, in his order. Each restored idea goes **inside the section it belongs to**, not into a separate appended block:
   - A theorem goes next to the technique it proves (format in Section 4.2).
   - An old template goes next to his function for the same job. Add the unit with `<CodeSnippet unit="…" />` only if his code does not already do the same job.
   - An old bug catalogue entry becomes a "Common mistake:" paragraph in that section, with the failing input and the fix.
   - An old worked example goes into the section it uses. Rewrite it in the style guide's worked-example order: example, idea, trace, code, cost, mistake. Keep the 6-step recognition reasoning as the "idea" part: budget from the limits, which tools fit, which property decides.
5. `## Recognition cards`: one line saying what a card is, then `<Cards topic="…" />`. Place it after his first "how to recognise" section if he has one; otherwise place it just before Quick revision.
6. `## Quick revision` (his, extended with one line for each restored theorem).
7. `## Check yourself`, which holds, in this order:
   - `### Identification drill` with `<Drill />`
   - `### Look-alike pairs` with `<LookalikePairs />`
   - `### Self-test` with `<SelfTest />`
   - `### Checkpoint` with `<Checkpoint />`
   - `### Decision map update` with `<DecisionMapUpdate />`
8. `## Practice problems` (the last `##` heading). One intro line, then `<Ladder topic="…" />`. No raw link list.

Update the notes-format checks in the validator to match. They must require `## Quick revision`, `## Check yourself` and `## Practice problems`, in that order, as the last three `##` headings. They must also require the components above to appear once each.

---

## 4. Writing rules for restored content

### 4.1 Voice

Restored text is written the way his notes explain. Rewrite the old formal text into this shape, without dropping a step of the reasoning:
- Start with a small concrete example with real numbers, then the general statement.
- Go from brute force to better: say what the slow way costs and why the better way works.
- Use short sentences, one idea each. Use "so" and "because" instead of bare arrows.
- Do a dry run on a tiny input before the code.
- Plain English only (`check_english.mjs` and `--tone` must pass).

### 4.2 Theorems and proofs

Keep the number (Theorem 1.4.1), the precise statement and every proof step. Use this format:

```mdx
**Theorem 1.4.1 (binary search).** <one-sentence statement, maths in $...$>

Small example first: <the old "tiny instance", with numbers>.

Why it works:
1. <proof step>
2. …

This proof needs: (1) …, (2) …, (3) … ← the old "This proof needs" box; check these on every problem.

<TheoremCode unit="1.4/thm-1" />
```

If his note already has an equivalent function, show his function and keep the theorem text. Only add `<TheoremCode>` when its examples add something his function's examples do not.

### 4.3 Maths formatting

Applies to his text, restored text and YAML text alike.

| Plain text today | Formatted |
|---|---|
| `O(n log n)`, `O(n^2)` | `$O(n \log n)$`, `$O(n^2)$` |
| `10^9`, `2·10^5`, `1e18` (in prose) | `$10^9$`, `$2 \cdot 10^5$`, `$10^{18}$` |
| `⌈d/x⌉`, `⌊(d+x-1)/x⌋` | `$\lceil d/x \rceil$`, `$\lfloor (d+x-1)/x \rfloor$` |
| `Σ(A_i - mid·B_i) ≥ 0` | `$\sum (A_i - \text{mid} \cdot B_i) \ge 0$` |
| `nCr`, `C(n, r)` | `$\binom{n}{r}$` ("n choose r" the first time) |
| `a mod m` (maths) | `$a \bmod m$`. In C++ talk keep `` `a % m` `` |
| `√n`, `sqrt(n)` | `$\sqrt{n}$` |
| `log2(n)` | `$\log_2 n$` |
| `a[i]` meaning the maths value | `$a_i$`. When talking about the program, keep `` `a[i]` `` |
| `[lo, hi]` as an interval | `$[\text{lo}, \text{hi}]$` |
| `x ≤ y`, `x != y` (maths) | `$x \le y$`, `$x \ne y$` |
| `(A/2B)^\{2/3\}` | `$(A/2B)^{2/3}$` (remove import escapes inside maths) |
| a formula derived over several lines | display maths `$$ … $$` on its own lines, with a blank line before and after; `\begin{aligned}` for steps |

More rules:
- A variable named in prose (n, k, x) is maths: `$n$`. A name from the code (`mid`, `lo`, `cnt`) is code: backticks. Multi-letter names inside maths use `\text{mid}`.
- **Terms:** bold only where the term is defined. Every later use is plain text. Library and function names (`lower_bound`, `__builtin_popcount`) are always in code font.
- Headings, figure alt text and figure captions stay plain text (they cannot render KaTeX). Write "O(n log n)" in words there, or reword.
- Never put maths inside code blocks or inline code. Never change a number, an operator or the order of terms. Formatting changes only how a formula looks.
- In MDX, a `<` inside `$...$` must have a space after it (`$i < j$`), or use `\lt`. A `$` used as a currency sign in prose must be written `\$`.

### 4.4 Problem entries (ladder and bank)

Problem entries follow the old ladder style, written in the voice above:
- `summary`: one line in your own words, with the limits in maths (`$n \le 2 \cdot 10^5$`). Never copy the statement.
- `twist`: the one thing this rung adds over the previous rung.
- `hints`: 2 or 3, each one revealing a little more. The last hint names the property or theorem that solves it (for example "Theorem 1.4.1").
- A bank entry with `checked_on` set to the day you actually opened the page, plus the solution note required by PROBLEM_BANK_PLAN.md (topic purity: the problem must be solvable with this topic and earlier topics only).

---

## 5. Work split

Each phase is one branch and one PR. Do lesson work with parallel sub-agents, one per lesson, but treat the maths lessons as a group: 0.4, 2.1, 2.2 and 2.3 come from one note, so give them to one agent, or check them together. Sub-agents write files only. The main session runs builds and checks and does all git work.

Give each sub-agent:
- a written brief: this file's Sections 3 and 4, plus its lesson's inventory;
- the commands to check its own work (`check_english`, `check_code_unchanged`, `check_math` once it exists).

---

## 6. Phases

### Phase 0: Rules and tools (one PR)

1. Add this file to the repository root.
2. Update PLAN.md 6A and `docs/LESSON_STYLE_GUIDE.md` with Sections 3 and 4. Record the decisions from Section 2.
3. Add `tests/e2e/render_check.cjs`. For each of the 14 pages it must:
   - open the page at `localhost:4321` and scroll to the bottom;
   - count images, broken images (`naturalWidth == 0`), `.katex-error` elements, `.ladder-item` elements and page errors;
   - exit with an error if any broken image, KaTeX error or page error is found.
4. Make the data components render inline maths. Add a helper, for example `src/lib/mathText.ts`, that turns the `$…$` and `$$…$$` parts of a string into HTML with `katex.renderToString` (with `throwOnError: false`) and escapes everything else. Use it in:
   - Ladder: `summary`, `twist` and `hints`, through LadderIsland;
   - Cards;
   - Drill;
   - LookalikePairs;
   - SelfTest;
   - Checkpoint;
   - DecisionMapUpdate.

   First, build the site and look at a 5.4 card to confirm whether `$` currently shows as literal dollar signs. Then check every topic YAML for a `$` that is not maths. This change also fixes the 4.x and 5.x topics that already use `$`; say so in the PR.
5. Add `scripts/check_math.mjs <files>`, which:
   - flags maths-like text outside `$…$`, code fences and inline code: `O(`, `^`, `⌈ ⌉ ⌊ ⌋ Σ ∑ √ ≤ ≥ ≠ · ×`, `log2`, `nCr`, `sqrt(`, `1e9`-style numbers in prose, and import escapes `\{` `\}` outside code;
   - prints `file:line` for each one;
   - has an allow-list for headings, alt text and captions;
   - also checks YAML text fields with `--yaml <topic ids>`.
6. Add `scripts/check_numbers.mjs <ref> <files>`. For each paragraph of the old version (at `<ref>`), every number must still appear in the new version of the same lesson. Remove `$`, `\cdot`, `^{}` and braces before comparing, so that `2·10^5` matches `$2 \cdot 10^5$`. It catches a formula whose meaning changed during formatting.
7. Update `check_code_unchanged.mjs` (decision 3).
8. Add `scripts/check_ideas.mjs`. It reads the inventory files from Phase 1 and fails if a row has no status, or if the anchor a row points to is missing from the lesson.
9. Update the validator for the new notes shape (Section 3). Do not switch it on until Phase 2 is merged; use a flag.

Gate: build, `validate`, unit tests and the e2e lessons check all pass, and nothing visible changes on the 14 pages, apart from YAML maths now rendering.

### Phase 1: Idea inventory (read-only, one PR)

For each lesson, write `docs/restore/<topic-id>.md`, a table with one row per old idea:

| # | Old idea | Where in old lesson (`1d76f35`) | Kind | Status | Where now / reason |
|---|---|---|---|---|---|
| 1 | Invariant: p(lo) false, p(hi) true | §4.1 | theorem | missing | → add in "Finding first 1" |
| 2 | lower_bound / upper_bound definitions | §3 | definition | present | "lower_bound / upper_bound", line ~348 |
| … | | | | | |

- **Kind** is one of: motivation, scope, definition, theorem, proof step, template, bug, worked example, card, drill item, look-alike pair, self-test question, checkpoint item, decision-map line.
- **Status** is one of: present, partial (name what is missing), missing, or duplicate.
- Data-driven items (cards, drill and so on) count as "missing" until the component is back on the page.
- An idea his note states differently but completely counts as present. Quote the line it is on.
- Also note:
  - any idea in the old lesson that **contradicts** his note (for example a different bound or convention). These go to Saurabh, not into the lesson;
  - any old idea that used a later topic (it stays out).

Gate: every row has a status, and `check_ideas.mjs` passes. Put the totals per lesson in the PR body (present, partial, missing, duplicate). Stop for Saurabh to read it. He may strike rows.

### Phase 2: Restore depth (one PR, all 14 lessons)

For every partial or missing row:
1. Write it into the lesson at the place named in the inventory, following Section 4.1 (voice) and Section 4.2 (theorems).
2. Add the components in the positions from Section 3.
3. Move his opening, the old motivation, scope and definitions into `## What this note covers`.
4. Update the row's status to "added" with its new heading.

Rules:
- Never delete or reword his content to make room. Restored ideas sit next to his explanation.
- No duplicates. When his note and the old lesson both explain the same thing, keep his version and add only the missing part (usually the proof, the "this proof needs" conditions or the counterexample).
- Every claim keeps its reason. Every complexity claim says why. Every counterexample uses actual numbers.
- Any new code must compile and run. Use the existing tested units, or add new ones under `code/<topic>/` and run `bash scripts/test_units.sh code`.
- Turn on the new validator rules from Phase 0, step 9.

Gate:
- `check_ideas` shows no missing or partial rows;
- `check_code_unchanged <main before Phase 2> <files>` passes, so his code is untouched;
- `check_english --tone` is clean;
- `check_depth --report` is attached to the PR;
- build, render check and e2e pass.

### Phase 3: Format the maths and terms (one PR)

1. Run `check_math.mjs` on all 14 lessons and on their YAML. Fix every finding using the table in Section 4.3. This covers his text, the restored text and the YAML text (cards, ladder, drill, self-test, checkpoint).
2. Make terms bold only where they are defined. Expand abbreviations on their first use on each page.
3. Turn ASCII formulas inside prose into display maths where they are derivations.

Gate:
- `check_math` reports zero;
- `check_numbers <phase-2 commit>` passes;
- the render check shows 0 `.katex-error` on all 14 pages;
- `check_code_unchanged` passes.

Then open 0.2, 1.4, 1.5 and 2.3 in a browser at desktop width and at 375 px width:
- long display formulas must scroll inside their box, not across the page;
- take screenshots and add them to the PR.

### Phase 4: Research the problems (one PR)

1. **Check access first.** Run `node scripts/fetch_problem.mjs --brief` on one id from each source. Record which sources can be opened from this session. For a source that cannot be opened:
   - use the built-in browser or Chrome if this session has one;
   - otherwise confirm the title through a web search result from the site itself, set `source_check: search`, and list the problem in the PR as "statement not read".

   Never write a title, link or difficulty from memory.
2. **Remove maang.in.** Remove it from every list and body mention, and remove the URL line from his code comment in 1.3 (decision 3). Afterwards, `grep -rn maang src/ code/` must print nothing.
3. **Collect his problems.** For each lesson, list every non-maang problem from the raw link list and from the body. For each one:
   1. Open it and read the statement.
   2. Confirm it fits this topic and only earlier topics, and write the bank solution note.
   3. Pick the card it trains.
   4. Then either:
      - insert it as a ladder rung where its twist fits (renumber `rung`, so each rung adds exactly one new twist), or
      - add it to the bank as "More practice".
   5. Write `summary`, `twist` and `hints` in the Section 4.4 style, with maths formatted.

   Drop a problem that turns out to need a later topic. List it in the PR with the topic it needs.
4. **Fill gaps left by maang.** For each removed maang problem, check whether the idea it practised still has at least one problem. If not, find a free problem for it (decision 5) and process it the same way.
5. **Review the existing ladder.** For every rung already in the YAML:
   - re-read the problem;
   - check that the summary is right and that the hints lead to a solution;
   - check that rung order rises by one twist at a time;
   - rewrite summaries and hints into the lesson voice with formatted maths.
6. **Replace the raw list.** `## Practice problems` becomes one intro line and `<Ladder>`. Floors per topic:
   - every card has at least 3 rungs;
   - the ladder plus "More practice" has at least 12 problems.

   Topic 0.4 was short before (4 links). If it is still short after an honest search, keep the honest number and say so in the PR.
7. Run `node scripts/check_links.mjs` and `npm run build`. The bank validation runs in the build.

Gate:
- no maang;
- every problem has `checked_on` and a solution note;
- every ladder rung has a twist, a summary and 2 or 3 hints;
- in the PR, a table per topic: kept from his notes, added, dropped with reason, and unverified;
- build, render check and e2e pass.

### Phase 5: Independent verification (one PR)

Use fresh sub-agents that did not write the lessons, one per lesson (one for the maths group). Each one checks:
1. Every inventory row marked "added": the idea really is on the page, it is correct, and it is not a duplicate.
2. Every theorem: the statement, the small example numbers (recompute them), each proof step and the "needs" list.
3. Maths: compare 30 random formulas against the Phase 2 version. The meaning must be unchanged. Look at the rendered page.
4. Problems: open every ladder problem, read it, and check that the summary, twist and hints are right and that it fits the topic.
5. His code is unchanged. Any new code compiles and its printed output matches the lesson.
6. Every figure that sits next to a restored or reformatted passage: open the image and compare it with the numbers in the text.

The main session fixes what they find, and the PR lists each fix. Items that are Saurabh's to decide go under "Questions for Saurabh" in `PROGRESS.md`: contradictions between the old lesson and his notes, and unreadable hand-drawn items. Known ones from earlier work:
- the "1900 ranges" remark in 1.5;
- the left column of the greedy-halving drawing in 1.4;
- the grouping behind `5+3+2+1 = 11`.

---

## 7. Gate commands (every PR)

```bash
node scripts/validate.mjs
node scripts/check_links.mjs
node scripts/check_english.mjs --tone <14 files>
node scripts/check_code_unchanged.mjs <ref> <14 files>
node scripts/check_math.mjs <14 files>             # from Phase 3 on: must be 0
node scripts/check_ideas.mjs                       # from Phase 2 on
node scripts/check_depth.mjs --report              # attach output to PR
bash scripts/test_units.sh code
npm run build
npx astro preview --port 4321 &   # then:
node tests/e2e/render_check.cjs
node tests/e2e/lessons.cjs
```

Commits and PR bodies end with the attribution lines your session gives you. Update `PROGRESS.md` in the same commit as each phase. Do not merge; wait for Saurabh.

---

## 8. Definition of done

- [ ] Every idea from the `1d76f35` lessons and their YAML data is on the page (inventory shows added, present or a reasoned duplicate), written in his notes voice.
- [ ] Every theorem has a statement, a small example, the full proof and its "needs" list.
- [ ] Recognition cards, drill, look-alike pairs, self-test, checkpoint and decision map are visible on all 14 pages.
- [ ] Zero unformatted maths (`check_math`), zero KaTeX errors, and all numbers unchanged (`check_numbers`).
- [ ] No maang.in anywhere. Every practice problem was opened, fits its topic, and has a summary, twist and hints in the lesson style.
- [ ] His code is unchanged (apart from the one maang comment line), and all new code is tested.
- [ ] Every gate in Section 7 is green.

## 9. When to stop and ask

Stop and write to "Questions for Saurabh" in `PROGRESS.md` when:
- an old idea contradicts his note;
- a problem from his notes cannot be opened from any route;
- a topic cannot reach its problem floor;
- restoring an idea would require changing his code or his statement.

Continue with the other lessons in the meantime.

## 10. Out of scope

- The 34 template-format topics, apart from the shared component change in Phase 0.
- The failing CI `browser` job (`H4-2.yaml`, `L2-1.yaml`).
- New figures, except where a restored idea needs one: generate it, never use a photo.
