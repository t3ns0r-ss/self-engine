# Progress

## Now
- Milestone: M0 done; B0 approved; B1, B2, B3 and B4 done; B5 (Phase 5 banks) next
- Topic: bank 4.7
- Branch: claude/problemset-implementation-yja039
- Last completed step: B4, all 7 Phase 4 banks (4.1–4.7: 420 problems, 243 practice, 177 reserved; 4.1, 4.2, 4.4 and 4.5 complete), validated and published
- Next action: B5 (Phase 5 banks), one commit per topic

## Gates
| Gate | Status | Date |
|---|---|---|
| B0 pattern lists review | approved | 2026-10-02 |
| M0 test deploy | changed to GitHub Pages (server unreachable); first publish succeeded (Pages run #3) | 2026-10-02 |
| B1 spot-check | Saurabh said "Continue"; taken as go-ahead for B2 in the bank plan's default order. Spot-check notes still welcome in FEEDBACK.md | 2026-10-02 |

## Saurabh is studying
- Topic: —

## Topics
| id | status | merged commit |
|---|---|---|

## Bank
| topic | status | practice | reserved |
|---|---|---|---|
| 0.1 | short | 34 | 13 |
| 0.2 | short | 27 | 20 |
| 0.3 | short | 45 | 24 |
| 0.4 | short | 23 | 22 |
| 0.5 | short | 30 | 22 |
| 0.6 | short | 36 | 27 |
| 1.1 | short | 24 | 20 |
| 1.2 | short | 22 | 23 |
| 1.3 | short | 24 | 24 |
| 1.4 | short | 21 | 19 |
| 1.5 | short | 21 | 22 |
| 1.6 | short | 16 | 10 |
| 1.7 | short | 22 | 15 |
| 2.1 | short | 24 | 14 |
| 2.2 | short | 14 | 3 |
| 2.3 | short | 21 | 19 |
| 2.4 | short | 16 | 3 |
| 3.1 | short | 22 | 18 |
| 3.2 | short | 33 | 26 |
| 3.3 | short | 18 | 22 |
| 3.4 | short | 20 | 17 |
| 3.5 | short | 22 | 30 |
| 3.6 | short | 21 | 18 |
| 3.7 | short | 19 | 9 |
| 3.8 | short | 17 | 10 |
| 4.1 | complete | 64 | 34 |
| 4.2 | complete | 24 | 34 |
| 4.3 | short | 42 | 32 |
| 4.4 | complete | 36 | 31 |
| 4.5 | complete | 33 | 31 |
| 4.6 | short | 23 | 10 |
| 4.7 | short | 21 | 5 |
| other 16 (Phases 5–7) | patterns written, no problems yet | 0 | 0 |

### Bank gaps (status: short)
- 0.1: practice is 85% tier 1 (29 of 34; few 0.1-only problems exist above ABC B / rating 800). Reserved has 13 of 24: no look-alike pair, no review or exam problems, only 1 later_drill. Pattern `fast-io` has no problems: no pure problem was found where only I/O speed matters. Suggestion: fold `fast-io` into the lesson as a rule (always use the fast-I/O lines) rather than a pattern, and drop it from the pattern file.
- 0.2: reserved has 20 of 24: no look-alike pair (no near-identical earlier-topic partner exists; the natural partners need later topics), 2 of 4 later_drill, review 7 of 10, no exam problems. Practice platform mix is 59% AtCoder.
- 0.3: reserved has 24 (the minimum) but no look-alike pair and no exam problems; review has 9 of 10 (no tier-4 problem besides one LeetCode Hard).
- 0.4: reserved has 22 of 24: one look-alike pair (2 of 4), 3 of 4 later_drill, review 6 of 10, no exam problems.
- 0.5: reserved has 22 of 24: no look-alike pair, review 6 of 10, exam 1 of 2. Pattern `permutations` spans only tiers 2–3 in practice.
- 0.6: all reserved purposes are met except look-alikes (none found), so the status is short only for that.
- 1.1: reserved 20 of 24: no look-alike pair, 3 of 4 later_drill, review 6 of 10, no exam problems. Pattern `sort-with-index` has 3 practice problems over 2 tiers.
- 1.2: reserved 23 of 24: one look-alike pair (2 of 4), review 6 of 10, no exam problems. Practice is LeetCode-heavy (13 of 22) because most AtCoder prefix-sum problems went to the reserved set.
- 1.3: reserved 24, but one look-alike pair (2 of 4) and review 5 of 10.
- 1.4: reserved 19 of 24: no look-alike pair, review 4 of 10, no exam problems. Pattern `real-search` has 1 practice problem and `first-reaching-index` 2: pure real-valued binary searches in this phase's range are rare.
- 1.5: reserved 22 of 24: no look-alike pair (the natural partners, merge vs. remove intervals, are already used in 1.1), review 7 of 10, no exam problems.
- 1.6: the thinnest Phase 1 topic. Practice 16 of 20, reserved 10 of 24 (drill 5, checkpoint 3, review 2; no look-alike, later_drill or exam). Patterns `min-max-span` and `deque-window-condition` have 1 practice problem each, `histogram-rectangle` 2. Pure stack/deque problems at ratings 1000–1800 are scarce on these platforms; harder ones (e.g. Codeforces 1313C2, 1900) are above the Phase 1 tier range. Suggest allowing tier-5 problems up to 2000 for this topic, or accepting the gap.
- 1.7: reserved 15 of 24: two look-alike pairs (complete), drill 8, checkpoint 3; no later_drill, review or exam problems left at tier 3–4. Practice is LeetCode-heavy (12 of 22, 55%).
- 2.1: reserved 14 of 24: drill 8, checkpoint 3, review 3; no look-alike, later_drill or exam problems.
- 2.2: very thin. Practice 14 of 20, reserved 3 (checkpoint only). Most modular-arithmetic problems also need nCr (2.3), expectation (2.4) or DP, so they belong later. `inverse-general` has no problems (the fitting ones use extended Euclid and are in 2.1). Suggest merging 2.2's bank with 2.3's for practice purposes, or accepting the gap.
- 2.3: reserved 19 of 24: no look-alike or later_drill problems. Practice is tier-5 heavy (7 of 21).
- 2.4: practice 16 of 20, reserved 3 (checkpoint only). `geometric-wait` has 1 problem. Most expectation problems at these ratings need DP (Phase 3) and belong there.
- 3.1: practice 22, reserved 18 of 24 (drill 5 of 8, review 3 of 10, later_drill 2 of 4, one look-alike pair). `constraint-placement` practice covers tiers 2–3 only; no meet-in-the-middle problem is left for checkpoint or review once practice has three tiers. Practice is 59% LeetCode (limit 60%): unused AtCoder search problems at ABC C–D are scarce after 0.5.
- 3.2: practice 33, reserved 26 of 24. Short on composition only: `reconstruct` has 2 practice problems (most reconstruction tasks need LCS or knapsack, placed in 3.3–3.4), `two-index` practice spans tiers 3–4, later_drill 2 of 4, and no look-alike pair (the near-identical candidates, CF 455A and CF 1272D, need the same tool as their LeetCode twins).
- 3.3: practice 18 of 20, reserved 22 of 24. `value-indexed` has 1 practice problem (EDP E is reserved as a look-alike with EDP D) and `bounded` has 2; most other bounded or value-indexed tasks are rated above 2000. Drill 5 of 8, review 5 of 10. Three ABC candidates are shared ARC tasks whose statements were not cached.
- 3.4: practice 20, reserved 17 of 24 (drill 3 of 8, review 3 of 10). `edit-distance` has 3 practice problems and none left for checkpoint or review; `lis-reduction` practice spans tiers 3–4 only. Two look-alike pairs (LCS vs Minimum Operations to Make a Subsequence; Russian Doll Envelopes vs Maximum Length of Pair Chain).
- 3.5: practice 22, reserved 30. Short on composition only: `partition-counting` has 3 practice problems over tiers 2–3 and none in checkpoint or review (most partition-counting problems are coin-change variants already in 3.3); later_drill 2 of 4; one look-alike pair (Grid 1 vs Grid 2).
- 3.6: practice 21, reserved 18 of 24 (drill 4 of 8, review 3 of 10, later_drill 2 of 4). AtCoder ABC has almost no interval DP below F, so the set leans on LeetCode (57%) and Codeforces († notes). `first-element-match` and `palindrome-segment` practice each span 2 tiers. Two look-alike pairs (Predict the Winner vs Stone Game; Longest Palindromic Subsequence vs Substring).
- 3.7: practice 19 of 20, reserved 9 of 24: bitmask DP below rating 1700 is rare, so tiers 1–2 are empty and most candidates went to practice. `group-mask` has 2 practice problems (two others are in 3.1 as backtracking), `submask-mask` 3. No drill beyond 1, no later_drill, no look-alike pair (the natural partner, Boats to Save People, is used in an earlier bank).
- 3.8: practice 17 of 20, reserved 10 of 24: digit DP is rare below rating 1700, so most problems are tier 3–5 and went to practice. Drill 1 of 8, review 3 of 10, no later_drill; one look-alike pair (Count Numbers with Unique Digits vs Count Special Integers). `neighbour-digits` and `digit-aggregate` practice each span 2 tiers.
- 4.1: complete (all counts and composition rules met). 20 Codeforces notes are recalled from memory (†) and need a spot-check against the statement pages.
- 4.2: complete. Pattern `smallest-order` was merged into `dependency-order` as a variant (owner decision, 2026-10-03). 17 Codeforces notes are recalled (†).
- 4.3: short only because pattern `negative-edges` has 4 practice problems in tiers 3–4 only (needs 3 tiers): no tier-2 or tier-5 Bellman–Ford problem was found that does not need a later topic. 18 Codeforces notes are recalled (†).
- 4.4: complete (all counts and composition rules met). 17 Codeforces notes are recalled (†).
- 4.5: complete (all counts and composition rules met). 19 Codeforces notes are recalled (†).
- 4.6: short: reserved has 10 of 24 (drill 2, later_drill 1, lookalike 2, checkpoint 2, review 3, exam 0), and pattern `lca-query` has 3 practice problems over tiers 2–3. Pattern `path-updates` was merged into `path-aggregate` (owner decision, 2026-10-03). LCA problems in band are scarce once those needing sparse tables, Fenwick trees or tree DP are excluded. 12 Codeforces notes are recalled (†).
- 4.7: short: reserved has 5 of 24 (lookalike 2, checkpoint 1, review 2); pattern `cut-vertices` has 3 practice problems. ARC is allowed for this topic (owner decision, 2026-10-03): all 328 ARC B–E tasks with difficulty 1300–2400 were searched and 2 fit (ARC 111 D, ARC 143 D). 13 Codeforces notes are recalled (†).

## Scope notes for current topic
- Allowed: —
- New: —
- Forbidden keywords: —

## Blocked
- Codeforces problem pages (and LeetCode's problem pages) answer automated clients with a bot check, so their statements can't be opened from the build environment. Decided with Saurabh: Codeforces problems are checked through the official API (exact title, rating, tags) and marked `source_check: api`, shown with † in the lists; their solution notes need a spot-check on the page. LeetCode is checked through LeetCode's own question data (the same title, difficulty, premium flag, and statement its page shows); premium problems are skipped.
- Note for whoever maintains the environment: an attempt to look into the Codeforces bot check was stopped by the session's safety checks and was not pursued; some CA certificates added to the container's NSS store during that attempt were left in place (removing them was also blocked). They live only in this temporary container.

## Questions for Saurabh
- **B1 spot-check (gate).** All 13 banks are in `problem-bank/phase-0/` and `problem-bank/phase-1/` (readable lists) and on the site under Problem bank. Suggested spot-checks: `problem-bank/phase-1/1.3-two-pointers.md` (the exemplar topic) with `notes/bank/1.3.md`, then one Phase 0 topic (0.4) and one thin topic (1.6). For each, check a few problems: does the solution really need the topic, is the tier right, is the note correct?
  - Problems marked † are Codeforces problems checked through the official API only: title and rating are exact, but I could not open the statement, so their notes are from my knowledge of the problem and are marked "(recalled)" where a detail matters. Please open a few † problems and compare with the note.
  - Every bank is `status: short` (Section 11). The usual shortfalls: look-alike pairs (rare where both problems are unused and nearly identical), review and exam problems at tiers 3–4, and Phase 0 tiers 3–5. Details per topic are under Bank gaps. Is `short` acceptable here, or should I relax a rule (for example allow ABC B problems at tier 2 for Phase 0 reserved sets, or ratings up to 2000 for 1.6)?
  - Pattern `fast-io` (0.1) has no problems; suggest folding it into the lesson as a rule rather than a pattern. `real-search` (1.4) has 1 problem.
  - Fixed after B0 approval: the 1.7 pattern `bit-identities` had lost its precondition (a "|" in the text split it during generation). It now reads: "Addition is XOR plus the carries: a carry appears exactly at the bits where both a and b are 1, so a + b = (a ⊕ b) + 2(a & b) and a | b = (a ⊕ b) + (a & b)."
  - Next: B2–B7 before lessons (the bank plan's order), or M1 (the 1.3 lesson) now with banks running one phase ahead?
- Review the 48 pattern files in `src/data/bank/patterns/` (readable versions in `problem-bank/phase-*/`). They decide what each topic teaches. Approve the B0 gate here or leave changes in FEEDBACK.md.
- Hosting: GitHub Pages at https://t3ns0r-ss.github.io/self-engine/ (your server is unreachable). Enable it once: Settings → Pages → Source: "GitHub Actions". The self-hosted files stay as an alternative.
- Deviations in M0, decided while you were travelling (change any you disagree with):
  - Bank plan Section 12 is applied already (it says "once B1 is merged"): topic data files reference bank problems by id, and title, URL, difficulty, and `checked_on` live only in the bank. Doing it now avoids a schema migration later.
  - Lesson components are `.astro` wrappers that hydrate their own React islands, so lessons write `<Ladder topic="1.3" />` (imported from `Ladder.astro`) without `client:load`. PLAN.md Section 6 imports `Ladder.tsx` with `client:load`; that cannot work, because a React island cannot read Astro content collections.
  - Drill answer cards may name an earlier topic's bank pattern when that topic has no lesson yet, since 1.3 is written before 1.1 and 1.2.
  - The checkpoint pass rule counts drill items where the chosen card was right. Whether the written property is right cannot be checked automatically.
  - Review-set pages show a "show anyway" button before the checkpoint is passed, instead of refusing outright.
  - Astro 7 needed `@astrojs/markdown-remark` installed for KaTeX's remark/rehype plugins.
- Git: the session works on the branch `claude/problemset-implementation-yja039`, not the `bank/phase-{n}` and `setup/m0` branches named in the plans. Should I keep that branch name or switch?
- Interpretations made (change any you disagree with):
  - AtCoder titles are stored without the task letter prefix shown in the page heading ("C - Title" → "Title"), matching how the other platforms' titles look.
  - Phase 0 topics (especially 0.1) have few pure problems in tiers 3–5, and reserved purposes need tier ≥ 2 while ABC A–B count as tier 1. Expect `status: short` for several Phase 0 topics; gaps are listed under Bank.
  - Count and composition rules (bank plan Sections 10.3–10.5) apply only to `status: complete`. `in_progress` files must pass every rule for each problem but may be below the counts.
  - Codeforces tier ranges include both ends, so a rating exactly on a boundary (e.g. 1400 in Phase 1) may sit in either tier. Phase 0 tier 1 is rating 800.
  - Pattern files are also checked for later-topic keywords (PLAN.md Section 4).
  - Topic 7.8 has an empty pattern file, since its problems use `{topic}:{pattern-id}`.
  - Bank pages use `/bank/1-3/` (dash, not dot) so `.3` isn't read as a file extension by web servers.
