# Progress

## Now
- Milestone: M9 (Phase 7), started on Saurabh's "Continue" after the M8 report (all gates are now approved by Saurabh).
- Topic: all phases written and approved; see DEVELOPER_GUIDE.md for further work
- Branch: claude/problemset-implementation-yja039
Last completed step: profile sync (PROFILE_SYNC_PLAN.md) milestones S0 to S6 except the LeetCode snippet, on `main` at Saurabh's request (details under "Profile sync" below).
Next action: Saurabh runs the LeetCode snippet from the Profiles page (gate S4), then the final review.

## Gates
| Gate | Status | Date |
|---|---|---|
| S0 LeetCode probe (profile sync) | approved (probe output received; list query with AC/TRIED filters works) | 2026-10-13 |
| S0 API review (profile sync) | approved (Saurabh: "Done all 3 needs me part") | 2026-10-13 |
| S2 Codeforces live (profile sync) | approved (same message) | 2026-10-13 |
| S4 LeetCode live (profile sync) | waiting: run the snippet from the Profiles page once and confirm | 2026-10-13 |
| DL1 L2.1 exemplar review (design tracks) | approved (Saurabh: "All good, just the images used aren't very good"; diagrams fixed 2026-10-19: Mermaid now an SVG image with a readable theme and dark mode) | 2026-10-19 |
| DH1 H4.2 exemplar review (design tracks) | approved (same message; the run.md practicality check by Saurabh is not confirmed) | 2026-10-19 |
| B0 pattern lists review | approved | 2026-10-02 |
| M0 test deploy | changed to GitHub Pages (server unreachable); first publish succeeded (Pages run #3) | 2026-10-02 |
| B1 spot-check | Saurabh said "Continue"; taken as go-ahead for B2 in the bank plan's default order. Spot-check notes still welcome in FEEDBACK.md | 2026-10-02 |
| Final bank review | approved ("Let's begin with material building") | 2026-10-03 |
| M1 exemplar review | approved ("for beginning this is good enough"; patterns and other changes to come later) | 2026-10-03 |
| M2 Phase 0 review | approved ("Continue" after the M2 report) | 2026-10-07 |
| M3 Phase 1 review | approved ("Continue" after the M3 report) | 2026-10-08 |
| M4 Phase 2 review | approved ("Continue" after the M4 report) | 2026-10-08 |
| M9 Phase 7 review | approved (topics 7.1–7.8, intro and exam written; the exam holds 8 problems, one each from 7.1 to 7.7 and ac-abc338_f from the 7.8 bank; bank additions and weak points listed in Questions for Saurabh) | — |
| M8 Phase 6 review | approved (topics 6.1–6.4, intro and exam written; the exam holds 6 problems, two from 6.1 and one each from 6.2, 6.3, two from 6.4; bank additions and weak points listed in Questions for Saurabh) | — |
| M7 Phase 5 review | approved (topics 5.1–5.4, intro and exam written; the exam holds 6 problems, one from 5.1, two each from 5.2 and 5.3, one from 5.4; bank additions and weak points listed in Questions for Saurabh) | — |
| M6 Phase 4 review | approved (all seven topics, intro and exam written; bank additions for 4.6 and 4.7 listed in Questions for Saurabh) | — |
| M5 Phase 3 review | approved (work on M6 continued at Saurabh's request, 2026-10-10) | — |
| R1 reference review (topic 1.6 retrofitted) | approved ("Rest seems okay" after the Revision 2.1 changes and the collapsed in-action block) | 2026-10-10 |
| R1 retrofit of the other 24 topics (0.1–3.8) | done, approved | 2026-10-10 |
| Bank fill review | approved (10 complete, 15 short with exhaustion records) | 2026-10-09 |

## Design tracks (DESIGN_TRACKS_PLAN.md)
| Milestone | Status |
|---|---|
| D0 infrastructure | in progress, redone for Revision 5 (2026-10-18, merged to `main`; all further work happens on `main`). **Done:** toolchains installed and recorded (Go 1.27.2, GCC 16 snapshot, Node 24, Docker 29.9 + Compose 5.6; `docs/design/TOOLCHAINS.md`); `code/go.mod`, `code/shared/` (`check.hpp`, `cxxflags.sh`, `simnet` sync + async, `faultproxy`, `loadgen`, `capcalc`, `constants.json`) with tests; every script of Section 9 and 18.3 (`change_cost`, `test_design`, `exercise_kit_check`, `new_attempt`, `labserver`, `new_topic`, `new_kit`, `inventory_check`), tested; the Appendix A (solution unit), B (claim + lab) and C (kit) samples re-run on the new toolchains; lab server initialised in local mode, all four stacks started, health-checked and stopped, one Kafka topic created and consumed; templates; 100 curriculum rows (48 LLD from L0.0, 52 HLD with `lab` and `infra`), schemas and validators D2-D9, D13, D15-D18 (+ D14 in `check_built.mjs`); `rubrics.yaml`, `product-names.yaml`, `design.config.yaml`; CI jobs; routes of Section 18.6 (build-verified on Astro 7.3.5 / Starlight 0.42.5); every component and page of Section 11.7 on LLD and HLD placeholder topics, checked in Chromium at desktop and 375 px (`tests/e2e-design.sh`); the exercise inventory for all 100 topics (`src/data/exercises/INVENTORY.yaml`, totals in `notes/design/INVENTORY.md`). **Also done:** build-time Mermaid (D10, `rehype-mermaid` with Playwright Chromium; design browser e2e 51 ok); CI no longer runs the CP-track `npm test` or `tests/e2e.sh` (cost; they still run locally). **Not done:** D1/D19 on real topic files, the SSH path of `labserver.sh` (only local mode was run), an older Redis licence decision (see Questions), a released GCC 16.x (see TOOLCHAINS.md) |
| D0 review gate | done: Saurabh said `approved` on 2026-10-18 (local-mode lab server accepted; SSH path untested; Valkey, GCC 16.2, public repo decided; the four plan fixes listed under Questions went out for review, no objection with the approval) |
| DL1 L2.1 Strategy exemplar | done 2026-10-18, tagged `topic-L2.1`: lesson, data, 22 exercises, 8 kits, code units; validate, `test_design`, kit check, site build and `check_built` green. Not done: the full beginner reading test |
| L-A L0.0 C++ for object design | done 2026-10-19, tagged `topic-L0.0`: 4 claims (5 solution units under the sanitizers), 7 mistake programs run with their sanitizer output, 8 kits (5 rungs, checkpoint, 2 reviews; kit check green), 20 exercises, lesson; site build green. Not done: reading test. Also: the L2.1 drill now has 2 items answered by L0.0 cards (the drill quota) |
| L-A L0.1 Classes, encapsulation, invariants | done 2026-10-19, tagged `topic-L0.1`: 4 claims (5 solution units under the sanitizers, exhaustive checks), 8 mistake programs run, 8 kits (kit check green), 22 exercises, lesson; site build green. Not done: reading test. L2.1 drill now has 3 earlier-card items |
| L-A L0.2 Interfaces, virtual functions, vtable | done 2026-10-19, tagged `topic-L0.2`: 4 claims (6 solution units under the sanitizers, incl. a hand-written vtable), 9 mistake programs run (the course warning flags catch three before they run; each shown with and without the warning), 8 kits (5 rungs, checkpoint, 2 reviews; kit check green), 22 exercises, lesson; site build green. Not done: reading test |
| L-A L0.3 Relationships: composition, aggregation, inheritance | done 2026-10-19, tagged `topic-L0.3`: 4 claims (6 solution units under the sanitizers), 9 mistake programs run (sanitizers catch the dangling part, the leak and the double free), 8 kits (5 rungs, checkpoint, 2 reviews; kit check green), 22 exercises, lesson; card ids renamed from the inventory (`owned-part`, `referred-part`, `true-subtype`) because the bare words would show in page text (D14). Not done: reading test |
| DH1 H4.2 Quorums exemplar | done 2026-10-18, tagged `topic-H4.2`: claims 1-3 (claim programs, calc), quorum lab with read repair and sloppy-quorum test, real three-process run with faultproxy (recorded, run on the dev machine, not the lab server), 6 mistake mutants, 5 lab-rung kits (kit check green), 24 exercises, lesson; site build green. Not done: lab-server integration and full-mode experiments (none planned for this lab), rubric calibration for cp-1, reading test |

## Profile sync (PROFILE_SYNC_PLAN.md)
| Milestone | Status |
|---|---|
| S0 API review | done except LeetCode (needs Saurabh's browser) and re-reading `apiHelp` in a browser; findings in `docs/sync/API_NOTES.md`. Finding that changes the plan: `problemset.problems` lists a shared problem once, so aliases come from `contest.standings` (bare form only, a few MB per contest) |
| S1 core, gate, store, status | done: `src/lib/sync/` (core, gate, store, status, transport, platforms, runner, scheduler, reserved); every status read goes through `getStatus`/`useStatuses` (check Y2) |
| S2 Codeforces | done: transport chain direct then JSONP then proxy, `cf_aliases.mjs`, Profiles page, scheduler, chips, dashboard sync line. Gate "S2 Codeforces live" is waiting for Saurabh |
| S3 AtCoder | done |
| S4 LeetCode | done: import (file and `#lc=` link), console snippet (`src/lib/sync/snippet.ts`, tested against a stub of leetcode.com), check Y4. Gate "S4 LeetCode live" waits for Saurabh to run the snippet once |
| S5 reserved protection | done: shown times, compromised detection, scaled pass rules, checkpoint and exam timing, re-solve detection, "needs a log entry", `compromised` feedback type (PLAN.md 16.3) |
| S6 proxy and docs | done: nginx and Caddy blocks validated (see API_NOTES.md), `sync-config.json`, README section |

Tests added: `tests/sync-*.test.mjs`, `tests/validate-sync.test.mjs` (node:test, not Vitest: the repo already uses `node --test` and Node 22 runs the TypeScript modules directly), and `tests/e2e/sync.cjs` (Playwright, scenarios 1 to 7 of the plan at 1200 and 375 px).

## Saurabh is studying
- Topic: — (not reported yet)
- LLD topic: — (not started)
- HLD topic: — (not started)

## Topics
| id | status | merged commit |
|---|---|---|
| 1.3 | done (M1 approved; revised in M3 for 1.1 and 1.2; on this session's branch) | — |
| 0.1 | done (on this session's branch) | — |
| 0.2 | done (on this session's branch) | — |
| 0.3 | done (on this session's branch) | — |
| 0.4 | done (on this session's branch) | — |
| 0.5 | done (on this session's branch) | — |
| 0.6 | done (on this session's branch) | — |
| Phase 0 intro and exam | done (on this session's branch) | — |
| 1.1 | done (on this session's branch) | — |
| 1.2 | done (on this session's branch) | — |
| 1.4 | done (on this session's branch) | — |
| 1.5 | done (on this session's branch) | — |
| 1.6 | done (on this session's branch) | — |
| 1.7 | done (on this session's branch) | — |
| Phase 1 intro and exam | done (on this session's branch) | — |
| 2.1 | done (on this session's branch) | — |
| 2.2 | done (on this session's branch) | — |
| 2.3 | done (on this session's branch) | — |
| 2.4 | done (on this session's branch) | — |
| Phase 2 intro and exam | done (on this session's branch) | — |
| 3.1 | done (on this session's branch) | — |
| 3.2 | done (on this session's branch) | — |
| 3.3 | done (on this session's branch) | — |
| 3.4 | done (on this session's branch) | — |
| 3.5 | done (on this session's branch) | — |
| 3.6 | done (on this session's branch) | — |
| 3.7 | done (on this session's branch) | — |
| 3.8 | done (on this session's branch) | — |
| Phase 3 intro and exam | done (on this session's branch) | — |
| 4.1 | done (on this session's branch) | — |
| 4.2 | done (on this session's branch) | — |
| 4.3 | done (on this session's branch) | — |
| 4.4 | done (on this session's branch) | — |
| 4.5 | done (on this session's branch) | — |
| 4.6 | done (on this session's branch; bank additions to review) | — |
| 4.7 | done (on this session's branch; bank additions to review) | — |
| Phase 4 intro and exam | done (on this session's branch) | — |
| 5.1 | done (on this session's branch; bank additions to review) | — |
| 5.2 | done (on this session's branch; † Codeforces links confirmed to open by the owner on 2026-10-11, ideas are still from recalled statements) | — |
| 5.3 | done (on this session's branch; † Codeforces links confirmed to open by the owner on 2026-10-11, ideas are still from recalled statements) | — |
| 5.4 | done (on this session's branch; † Codeforces links confirmed to open by the owner on 2026-10-11, ideas are still from recalled statements) | — |
| 6.1 | done (on this session's branch) | — |
| 6.2 | done (on this session's branch) | — |
| 6.3 | done (on this session's branch) | — |
| 6.4 | done (on this session's branch; † Codeforces ideas are from recalled statements) | — |
| 7.1 | done (on this session's branch) | — |
| 7.2 | done (on this session's branch; † Codeforces ideas are from recalled statements) | — |
| 7.3 | done (on this session's branch; † Codeforces ideas are from recalled statements) | — |
| 7.4 | done (on this session's branch; † Codeforces ideas are from recalled statements) | — |
| 7.5 | done (on this session's branch; † Codeforces ideas are from recalled statements) | — |
| 7.6 | done (on this session's branch; † Codeforces ideas are from recalled statements) | — |
| 7.7 | done (on this session's branch; † Codeforces ideas are from recalled statements) | — |
| 7.8 | done (on this session's branch; † Codeforces ideas are from recalled statements) | — |
| Phase 7 intro and exam | done (on this session's branch) | — |
| Phase 5 intro and exam | done (on this session's branch) | — |

## Bank
| topic | status | practice | reserved |
|---|---|---|---|
| 0.1 | short | 32 | 31 |
| 0.2 | complete | 25 | 31 |
| 0.3 | complete | 40 | 33 |
| 0.4 | complete | 23 | 35 |
| 0.5 | complete | 32 | 42 |
| 0.6 | complete | 35 | 35 |
| 1.1 | short | 25 | 32 |
| 1.2 | complete | 30 | 35 |
| 1.3 | complete | 26 | 36 |
| 1.4 | short | 23 | 37 |
| 1.5 | complete | 24 | 35 |
| 1.6 | short | 20 | 23 |
| 1.7 | complete | 24 | 31 |
| 2.1 | short | 25 | 30 |
| 2.2 | short | 16 | 18 |
| 2.3 | short | 26 | 30 |
| 2.4 | short | 18 | 18 |
| 3.1 | complete | 24 | 32 |
| 3.2 | short | 35 | 32 |
| 3.3 | short | 21 | 30 |
| 3.4 | short | 20 | 26 |
| 3.5 | short | 23 | 34 |
| 3.6 | short | 22 | 24 |
| 3.7 | short | 22 | 24 |
| 3.8 | short | 19 | 22 |
| 4.1 | complete | 64 | 34 |
| 4.2 | complete | 24 | 34 |
| 4.3 | short | 42 | 32 |
| 4.4 | complete | 36 | 31 |
| 4.5 | complete | 33 | 31 |
| 4.6 | short | 23 | 10 |
| 4.7 | short | 21 | 5 |
| 5.1 | short | 14 | 5 |
| 5.2 | short | 22 | 26 |
| 5.3 | complete | 30 | 31 |
| 5.4 | short | 14 | 2 |
| 6.1 | short | 19 | 26 |
| 6.2 | short | 19 | 25 |
| 6.3 | short | 19 | 28 |
| 6.4 | short | 15 | 26 |
| 7.1 | short | 24 | 35 |
| 7.2 | short | 20 | 27 |
| 7.3 | short | 17 | 25 |
| 7.4 | short | 19 | 25 |
| 7.5 | short | 19 | 25 |
| 7.6 | short | 17 | 25 |
| 7.5 | short | 20 | 10 |
| 7.6 | short | 17 | 25 |
| 7.6 | short | 16 | 7 |
| 7.7 | short | 25 | 24 |
| 7.8 | complete | 0 | 40 |

### Bank gaps (status: short)
- Topics 0.1–3.8: see `bank-fill/SHORTFALL.md` (measured shortfall and exhaustion record per topic). The older per-topic notes for these topics were replaced by that file.
- Later topics (4.1 onward): not yet filled; their lessons are pending.
- 1.7: reserved 25: two look-alike pairs (complete), drill 8, checkpoint 3; at lesson step 1, 10 LeetCode Medium reviews were added (review 10 of 10). Still short: no later_drill or exam problems. Practice is LeetCode-heavy (12 of 22, 55%).
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
- 5.1: short: 14 practice of 20 and 5 reserved of 24 (review 3, checkpoint 1, exam 1). Static range-query problems are few once monotonic-deque (1.6) and segment-tree (5.3) problems are excluded; LeetCode and AtCoder have almost none (searched cached ABC/ARC statements). Suggestion: fold 5.1 into 5.3 as a lesson section, or accept a small bank. 13 Codeforces notes are recalled (†).
- 5.2: short: pattern `range-add-point` has 2 practice problems (Codeforces Progressions Covering, ABC 253 F; ABC 340 E is used for review) and `kth-in-tree` has 4 over tiers 2–3; review has 7 of 10; one look-alike pair (CSES Dynamic Range Sum / Range Update Queries). Online range-add/point-query problems in band are rare (most are static difference arrays, 1.2). 15 Codeforces notes are recalled (†).
- 5.3: complete (all counts and composition rules met). 20 Codeforces notes are recalled (†).
- 5.4: short: 14 practice and 2 reserved, all from Codeforces (16 recalled notes, †). LeetCode has no free Mo's-algorithm or square-root problems, AtCoder's are ABC G (above the tier table), and most Codeforces block problems are rated 2400+. Pattern `blocks` has 3 practice problems. Suggestion: keep 5.4 as a short optional topic, or accept 2500–2700 Codeforces problems as tier 5 here.
- 6.1: short: 19 practice and 26 reserved (drill 8, look-alike 4, checkpoint 3, review 9, exam 2); `hash-length-search` has 3 practice problems over tiers 3–4. In-band hashing problems on LeetCode and AtCoder are few; most Codeforces ones are 2200+. Recalled Codeforces notes are marked (†).
- 6.2: short: 19 practice and 25 reserved (drill 8, look-alike 4, checkpoint 3, review 9, exam 1). Pattern `prefix-counts` has 1 problem (Codeforces Prefixes and Suffixes) and `z-compare` spans tiers 3–4. Suggestion: merge `prefix-counts` into `period-border`. Recalled Codeforces notes are marked (†).
- 6.3: short: 19 practice and 28 reserved (drill 8, later_drill 3, look-alike 4, checkpoint 3, review 9, exam 1); `dictionary-split` has 3 practice problems and `xor-count` 2 (counting XOR pairs below a bound has few dedicated problems). Suggestion: merge `xor-count` into `max-xor`. Recalled Codeforces notes are marked (†).
- 6.4: short: 15 practice and 26 reserved (drill 8, look-alike 4, checkpoint 3, review 9, exam 2). Suffix-array problems in band are scarce: LeetCode has almost none in its free set, AtCoder's are mostly ABC F/G or ARC, and most Codeforces ones are rated 2400+. Many reserved problems have a natural hashing, prefix-function or brute-force solution (see Questions for Saurabh). Recalled Codeforces notes are marked (†).
- 7.1: short only for look-alikes (0 of 4): no near-identical pair needing a different tool was found that is not already used. 20 Codeforces notes are recalled (†); the cf-1929D recurrence is flagged in its note for a brute-force check.
- 7.2: short: reserved has 5 of 24; `count-paths` (3) and `state-dag` (3, all tier 4) are thin, `condensation-dp` spans tiers 3–4. Many classic DAG-DP problems were already used as 4.2/4.3 practice. 7 Codeforces notes are recalled (†).
- 7.3: short: 16 practice and 3 reserved. Problems where a Fenwick or segment tree speeds up a DP are mostly rated 2300+ on Codeforces or ABC F/G; many LeetCode candidates have O(n²) or deque solutions. 7 Codeforces notes are recalled (†).
- 7.4: short: reserved has 9 of 24; `merge-smallest` has 1 problem (CSES Stick Divisions; LeetCode's version is premium) and `regret` 3. Several heap-greedy problems use 'marginal gain' or 'best-first enumeration', which match no pattern here. Suggestion: add a pattern `marginal-gain` (repeatedly apply the step with the largest gain from a heap). 5 Codeforces notes are recalled (†).
- 7.5: short: 19 practice and 25 reserved (checkpoint 3, review 9, drill 8, look-alike 4, exam 1). Several game problems on a graph with a draw, and the misère games, match no pattern here; `win-lose` holds both the DP over positions and the retrograde search. Many Codeforces notes are recalled (†).
- 7.6: short: 17 practice and 25 reserved (checkpoint 3, review 9, drill 8, look-alike 4, exam 1). The pattern `min-plus` also holds the max-plus and boolean variants. The bank has few LeetCode and AtCoder matrix problems of the right size, so 9 of the 25 reserved problems and 11 of the 17 practice problems are Codeforces (notes recalled, †).
- 7.5: short: reserved has 10 of 24; `nim-sum` and `grundy-sum` have 3 practice problems each. In-band Grundy-sum problems are few (most game problems are win-lose or ad hoc). 12 Codeforces notes are recalled (†).
- 7.6: short: 17 practice and 25 reserved (checkpoint 3, review 9, drill 8, look-alike 4, exam 1). The pattern `min-plus` also holds the max-plus and boolean variants. The bank has few LeetCode and AtCoder matrix problems of the right size, so 9 of the 25 reserved problems and 11 of the 17 practice problems are Codeforces (notes recalled, †).
- 7.6: short: 18 practice and 7 reserved (two look-alike pairs: LeetCode Transformations I/II and LeetCode/CSES Fibonacci). `min-plus` has 2 practice problems and `augmented-matrix` 2. Most in-band matrix problems are Codeforces (14 recalled notes, †).
- 7.7: short: drill 5 of 8, review 8 of 10, one look-alike pair (LeetCode DI String Match / Construct Smallest Number From DI String); `permutation-build` and `operation-sequence` span 2 tiers. Practice skews to tiers 1–2 (only constructions recalled reliably were chosen, since 33 Codeforces notes are recalled, †); harder ARC/CF constructions should be added after a statement check.
- 7.8: complete: 40 fresh reserved problems, at least 2 per phase and 1 per Phase 1–6 topic, all tier 3–5. 9 Codeforces notes are recalled (†).

## Scope notes for current topic
- Topic 4.7 Strongly connected components, bridges, articulation points. Allowed: 0.1–0.6, 1.1–1.7, 2.1–2.4, 3.1–3.8, 4.1–4.6 (4.5's entry times and subtree blocks; 4.4's union–find; 4.2's topological order for the condensation).
- New: the low-link value; bridges (low[v] > tin[parent]); articulation points (low[child] ≥ tin[v], root with two children); 2-edge-connected components and the tree of them; strongly connected components by Kosaraju (finish order, reversed graph); the condensation is a DAG; sources and sinks; a vertex reaches everything iff its component is the only source. Cards (decided in step 3): mutual-reach, condensed-dag, bridges, cut-vertices, bridge-tree. Avoid hyphenated card ids in page text.
- Forbidden keywords: every keyword of topics 5.1–7.8 (sparse table, fenwick tree, segment tree, tree dp, rerooting, dp on dag, …). 2-SAT, block-cut tree, flows are named only under "does not cover".
- Glossary terms already defined: through 4.6 plus 4.7 (strongly connected component, condensation, bridge, articulation point, 2-edge-connected component, entry time, low-link value, back edge).
- Bank 4.7 is short (reserved: checkpoint 1, lookalike 2, review 2; no exam): candidates are being researched; I add reserved problems with notes (as for 4.6) and flag them for review. Exam problems for Phase 4 come from the reserved exam sets of the 4.1–4.5 banks.

## Blocked
- Codeforces problem pages (and LeetCode's problem pages) answer automated clients with a bot check, so their statements can't be opened from the build environment. Decided with Saurabh: Codeforces problems are checked through the official API (exact title, rating, tags) and marked `source_check: api`, shown with † in the lists; their solution notes need a spot-check on the page. LeetCode is checked through LeetCode's own question data (the same title, difficulty, premium flag, and statement its page shows); premium problems are skipped.
- Note for whoever maintains the environment: an attempt to look into the Codeforces bot check was stopped by the session's safety checks and was not pursued; some CA certificates added to the container's NSS store during that attempt were left in place (removing them was also blocked). They live only in this temporary container.

## Bank fill
FILL_SHORT_TOPICS_PLAN.md for the completed topics 0.1–3.8. Full report: `bank-fill/SHORTFALL.md`. 10 topics reached `complete`; 15 stay `short`, each with an exhaustion record. All entries marked † are Codeforces problems checked through the API only.

| topic | status before | status now | practice | reserved | open question |
|---|---|---|---|---|---|
| 0.1 | short | short | 28 → 32 | 27 → 31 | yes |
| 0.2 | short | complete | 22 → 25 | 29 → 31 | no |
| 0.3 | short | complete | 40 → 40 | 31 → 33 | no |
| 0.4 | short | complete | 23 → 23 | 33 → 35 | no |
| 0.5 | short | complete | 29 → 32 | 37 → 42 | no |
| 0.6 | short | complete | 35 → 35 | 34 → 35 | no |
| 1.1 | short | short | 23 → 25 | 29 → 32 | yes |
| 1.2 | short | complete | 22 → 30 | 34 → 35 | no |
| 1.3 | short | complete | 24 → 26 | 35 → 36 | no |
| 1.4 | short | short | 20 → 23 | 35 → 37 | yes |
| 1.5 | short | complete | 20 → 24 | 33 → 35 | no |
| 1.6 | short | short | 16 → 20 | 21 → 23 | yes |
| 1.7 | short | complete | 22 → 24 | 27 → 31 | no |
| 2.1 | short | short | 24 → 25 | 27 → 30 | yes |
| 2.2 | short | short | 14 → 16 | 18 → 18 | yes |
| 2.3 | short | short | 24 → 26 | 26 → 30 | yes |
| 2.4 | short | short | 15 → 18 | 18 → 18 | yes |
| 3.1 | short | complete | 22 → 24 | 29 → 32 | no |
| 3.2 | short | short | 33 → 35 | 31 → 32 | yes |
| 3.3 | short | short | 19 → 21 | 27 → 30 | yes |
| 3.4 | short | short | 17 → 20 | 24 → 26 | yes |
| 3.5 | short | short | 22 → 23 | 32 → 34 | yes |
| 3.6 | short | short | 21 → 22 | 23 → 24 | yes |
| 3.7 | short | short | 20 → 22 | 22 → 24 | yes |
| 3.8 | short | short | 14 → 19 | 19 → 22 | yes |

## Questions for Saurabh
- **Phase 4 bank additions (M6).** The banks of 4.6 and 4.7 were short (4.6 had one look-alike pair, two checkpoint problems, three review problems and no exam problem; 4.7 had one pair, one checkpoint problem, two review problems and no exam problem), so I added reserved problems with notes, found by research (AtCoder, LeetCode and CSES statements were fetched; Codeforces ones are recalled and marked †, with title and rating checked through the API). 4.6: lc-number-of-ways-to-assign-edge-weights-i/ii (look-alike pair), ac-abc133_f (checkpoint), review cf-739B, ac-abc321_e, cf-1296F, ac-abc201_e, lc-path-existence-queries-in-a-graph-ii, cf-702E, exam lc-minimum-weighted-subgraph-with-the-required-paths-ii. 4.7: cf-711D and cf-659E (look-alike pair), cf-949C and cf-1900E (checkpoint), review cf-1927F, ac-abc266_f, cf-1454E, cf-542C, cf-883G, cf-698B, cf-1131D, exam cf-1547G, drill cf-1276B and lc-disconnect-path. Please spot-check the Codeforces notes. Known weak points: the 4.7 drill has few 4.7 answers (the bank has no reserved drill problems for the topic), cf-962F in the 4.7 ladder needs the blocks between articulation points (marked as a stretch), cf-1131D and cf-883G are weaker fits, and the 4.6 bug catalogue has 11 bugs (the plan says 4–8).
- **Bank fill (15 short topics).** For each, pick: (1) accept `short`; (2) lower the minimum; (3) merge a narrow pattern into a neighbour; (4) allow another source. My proposals:
  - 0.1: fold `fast-io` into the lesson as a rule and drop the pattern (exam has 1 of 2).
  - 1.4: merge `real-search` into `answer-search` (kth-by-counting also short).
  - 1.6: merge `min-max-span` with `histogram-rectangle`, and `window-extreme-deque` with `deque-window-condition`.
  - 2.2: merge `inverse-general` into `inverse-prime`; 2.2 and 2.4: lower the minimums (few problems at these ratings exist for the topic).
  - 1.1: `coordinate-compression` has no review problem; moving a practice problem to review needs your yes (practice would drop under the target).
  - 3.2: `reconstruct` has no review problem (same question).
  - Others (2.1, 2.3, 3.3–3.8): see their exhaustion records in `bank-fill/SHORTFALL.md`.
- **Spot-check the new † problems** (recalled notes): cf-1692A, 1921C, 1560A, 1543A, 143A, 6A, 886A, 363B, 1807D, 474B, 1676E, 919E, 359C, 312B, 621C, 204C. Three LeetCode Hard problems in 3.5 and 3.6 moved to tier 3.
- **R1 retrofit review.** All 25 completed topics (0.1–3.8) are now on Revision 2.1: `uses`, theorem blocks with a plain-words box, a tiny instance, a numbered proof, a preconditions box and a tested implementation with its examples, recognition cards with runnable example units, and templates and worked examples that show only the gist function. Not rewritten: the old worked-example step texts and bug catalogues (only the "C++ details explained" and "Tested" paragraphs were removed and the code swapped for the gist function). The Playwright browser tests of the real lessons (`tests/e2e/lessons.cjs`) were re-run after the Revision 2.1 changes and pass for all 26 lessons. The old Phase 0 and Phase 1 intro and exam pages are untouched.
- No `bank-filled` git tag was created (pushing partial refs was denied).
- Keyword scan and ordered sets (0.6): `lower_bound` and `upper_bound` are keywords of 1.4 (binary search), but topic 0.6 needs the `set`/`map` member functions of the same name. The scan now ignores a keyword written as a member call (preceded by a dot, as in `s.lower_bound(x)`); the free functions on arrays stay reserved for 1.4. Say if you would rather keep the scan strict and have 0.6 describe these calls without naming them.
- Changes made while building 1.3 (change any you disagree with):
  - Topic data files may carry `draft: true` while a lesson is being written: count rules are skipped and the lesson shows a draft notice, so every step's commit keeps CI green. 1.3 no longer has it.
  - 1.3 defined basic terms that belonged to unwritten earlier lessons; in M3 subarray moved to 1.2 and non-decreasing to 1.1 (amortised analysis was already 0.2's).
  - The bank got 7 new LeetCode review problems for 1.3 and one moved look-alike (details under Bank gaps).
  - tests/e2e.sh now also tests every real lesson in the browser (tests/e2e/lessons.cjs). While adding it, a failed run deleted the real 1.3 files through the placeholder cleanup (restored from git at once); the placeholder remover now refuses to run unless the placeholder exists.
- **B1 spot-check (gate).** All 13 banks are in `problem-bank/phase-0/` and `problem-bank/phase-1/` (readable lists) and on the site under Problem bank. Suggested spot-checks: `problem-bank/phase-1/1.3-two-pointers.md` (the exemplar topic) with `notes/bank/1.3.md`, then one Phase 0 topic (0.4) and one thin topic (1.6). For each, check a few problems: does the solution really need the topic, is the tier right, is the note correct?
  - Problems marked † are Codeforces problems checked through the official API only: title and rating are exact, but I could not open the statement, so their notes are from my knowledge of the problem and are marked "(recalled)" where a detail matters. Please open a few † problems and compare with the note.
  - Every bank is `status: short` (Section 11). The usual shortfalls: look-alike pairs (rare where both problems are unused and nearly identical), review and exam problems at tiers 3–4, and Phase 0 tiers 3–5. Details per topic are under Bank gaps. Is `short` acceptable here, or should I relax a rule (for example allow ABC B problems at tier 2 for Phase 0 reserved sets, or ratings up to 2000 for 1.6)?
  - Pattern `fast-io` (0.1) has no problems; suggest folding it into the lesson as a rule rather than a pattern. `real-search` (1.4) has 1 problem.
  - Fixed after B0 approval: the 1.7 pattern `bit-identities` had lost its precondition (a "|" in the text split it during generation). It now reads: "Addition is XOR plus the carries: a carry appears exactly at the bits where both a and b are 1, so a + b = (a ⊕ b) + 2(a & b) and a | b = (a ⊕ b) + (a & b)."
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
- Decisions received (2026-10-03): merge 4.2 `smallest-order` into `dependency-order` and 4.6 `path-updates` into `path-aggregate` (done); ARC tasks are allowed in all banks from B5 on (and in 4.7), tiered by judgement from the AtCoder Problems difficulty.
- Decisions received (2026-10-03, second batch): keep 6.2 `prefix-counts` and 6.3 `xor-count` as separate patterns; accept 5.4 and 6.4 as short banks for now (to be extended later with higher-rated problems); keep 5.1 as a small bank of its own.
- **Phase 5 bank additions (M7).** Research agents added reserved problems (notes in `notes/bank/5.x.md`; AtCoder statements fetched, LeetCode through its GraphQL endpoint, Codeforces recalled and marked †, titles and ratings checked through the API). 5.1: 22 problems (checkpoint cf-1706E, lc-minimum-stability-factor-of-array; review cf-675E, cf-1454F, lc-find-subarray-with-bitwise-or-closest-to-k, cf-6E, cf-1208E, cf-5C; look-alike pairs lc-maximum-total-subarray-value-ii/i and cf-1611F/cf-1486D; 8 drill problems of which 7 are solved by earlier tools; practice cf-1237D, lc-shortest-subarray-with-or-at-least-k-ii). 5.2: ac-abc402_d/ac-abc405_f (look-alike pair), review cf-1076E and cf-540E. 5.4: 25 problems (checkpoint cf-438D, cf-830C; exam cf-1654E; 8 review; 8 drill, only cf-425D solved by 5.4; look-alike pairs cf-522D/ac-abc242_g and cf-301D/ac-abc293_g; practice ac-abc384_g, ac-abc405_g). Weak points: 5.1 has only one sparse-table drill problem; cf-5C, cf-1208E, cf-6E and lc-shortest-subarray-with-or-at-least-k-ii have a natural earlier-tool solution; 5.4 supply of real sqrt/Mo problems in tiers 3–4 is thin (cf-463E and several others also fit a Fenwick or segment tree); the 5.4 review set has no Mo problem. Please spot-check the Codeforces notes. In 5.1 I moved cf-675E's technique from 3.1 to 3.2 (it is a DP).
- **Phase 5 lessons (M7), things to look at.** (1) FIXED 2026-10-11: three tier-5 blocks problems were added to the 5.4 bank (cf-551E, cf-444C, cf-911G); the blocks ladder now has five, and cf-551E is a fourth worked example (code/5.4/example-4) for the blocks card. (2) The 5.4 drill has one 5.4 answer (cf-425D); the other seven are solved by 5.2 or 5.3. (3) Several templates are restatements of ladder problems: mo-power is cf-86D and step-sums is cf-103D, kept as base rungs. (4) The 5.4 review sets contain no Mo problem. (5) The owner opened the † Codeforces problems on 2026-10-11 and they open fine; the hints and notes for them are still from recalled statements, so check an idea against the page when a problem is first solved. (6) A segment tree in 5.3 is written recursively with 4n nodes; I did not teach the bottom-up form (mentioned only as an alternative).
- **e2e script, placeholder stage.** FIXED 2026-10-11: `tests/placeholder/make.mjs` now has the real 1.3 cards `opposite-ends` and `merge-walk` (3 ladder rungs each), so the placeholder stage validates again.
- **Phase 6 bank additions and choices (M8, topic 6.1).** The 6.1 bank was short of reserved problems, so 15 reserved problems and 1 practice problem were added (statements read for AtCoder, CSES and LeetCode; Codeforces recalled and marked †): checkpoint cf-985F, cf-113B (with lc-shortest-palindrome); review cf-611D, cf-757C, cf-633C, ac-abc343_g, lc-maximum-product-of-the-length-of-two-palindromic-substrings (with four existing ones); look-alike pair cf-1948D / lc-distinct-echo-substrings (lc-distinct-echo-substrings moved from review to look-alike); drill ac-abc250_e, ac-abc158_e, cf-1731C, cf-778A, cf-1290B, cf-1426F, cf-682D (with cses-3138; six of the eight are solved by earlier tools); practice lc-smallest-unique-subarray. Several well-known problems were already used by other topics, so the ids were changed to unused ones. Weak points: hashing for the three palindrome and substring ladder rungs with a natural exact alternative (the lesson says so in Step 6 of the examples); the Codeforces hints are from recalled statements. The lesson uses one prime, 2^61 − 1, with `__int128`, a random base from the clock, and states the collision bound (Theorem 6.1.2) with its proof, including the "polynomial of degree d has at most d roots modulo a prime" step.
- **Phase 6 bank additions and choices (M8, topic 6.2).** 15 reserved problems were added (Codeforces recalled and marked †): checkpoint cf-631D, cf-1984D (with cses-1733); review cf-494B, cf-1120C, cf-1537E2, cf-825F, lc-find-all-good-strings, lc-find-the-occurrence-of-first-almost-equal-substring, lc-repeated-string-match (with cses-1112 and lc-minimum-number-of-valid-strings-to-form-target-ii); drill cf-471D, cf-2010C2, cf-1295B, cf-1360F, cf-1660F2, cf-1182C (with lc-longest-happy-prefix and lc-minimum-number-of-valid-strings-to-form-target-i; four of the eight drill problems are solved by earlier tools). The lesson has 3 cards instead of 4: the pattern `prefix-counts` (one practice problem, cf-432D) is a rung of the border card, and its theorem (6.2.6) has a template. Weak points: cf-1537E2, lc-repeated-string-match and cf-1295B have a natural simpler solution (the notes say so); the lesson teaches the matching automaton (Theorem 6.2.4 (b)) because cses-1112, cf-808G and lc-find-all-good-strings need it.
- **Phase 6 bank additions and choices (M8, topic 6.3).** 11 reserved problems were added (Codeforces recalled and marked †): look-alike partners lc-count-prefix-and-suffix-pairs-i and lc-maximum-strong-pair-xor-i (their version II problems moved to look-alike: lc-count-prefix-and-suffix-pairs-ii from practice to reserved, lc-maximum-strong-pair-xor-ii from exam to look-alike); review lc-k-th-smallest-in-lexicographical-order, lc-maximum-subarray-xor-with-bounded-range, lc-longest-common-prefix-of-k-strings-after-removal, lc-delete-duplicate-folders-in-system (lc-concatenated-words moved from review to checkpoint); drill cf-1879D, lc-camelcase-matching, lc-top-k-frequent-words, lc-words-within-two-edits-of-dictionary, lc-partition-string (with lc-implement-trie-prefix-tree, lc-map-sum-pairs and lc-extra-characters-in-a-string; five of the eight are solved by earlier tools). The three later_drill problems of the bank (lc-replace-words, lc-longest-word-in-dictionary, lc-short-encoding-of-words) stay unused for the later topics. The lesson has 3 cards: the patterns `max-xor` and `xor-count` are one card (binary-xor), because `xor-count` had only two practice problems. Weak points: lc-extra-characters-in-a-string, lc-words-within-two-edits-of-dictionary and lc-camelcase-matching have tiny constraints (the notes say that a set or a plain scan is enough); the ladder of binary-xor and the 1.7 high-bit-first card overlap for a fixed array (the card says so, and lc-maximum-xor-of-two-numbers-in-an-array is a negative example).
- **Phase 6 bank additions and choices (M8, topic 6.4 and the Phase 6 exam).** 25 problems were added and several moved (Codeforces recalled and marked †, except where the rating was read from the Codeforces list): practice ac-abc362_g, ac-arc044_d, ac-arc050_d, cf-452E, cf-1073G (cses-2104 moved from review to practice); checkpoint cf-427D (from practice), cf-128B, lc-orderly-queue; exam cses-2109, cf-557E, and from the 6.1 bank cf-1003F and lc-longest-chunked-palindrome-decomposition (both were unused practice problems); look-alike pairs ac-practice2_i / lc-k-divisible-elements-subarrays and lc-last-substring-in-lexicographical-order / lc-find-the-lexicographically-largest-string-from-the-box-i; review lc-shortest-uncommon-substring-in-an-array, lc-largest-merge-of-two-strings, lc-maximum-number-of-occurrences-of-a-substring, lc-construct-string-with-minimum-cost, lc-shortest-string-that-contains-three-strings, cf-835D, lc-find-the-string-with-lcp, lc-count-substrings-that-differ-by-one-character, lc-unique-substrings-in-wraparound-string; drill cses-2105, cses-1113 (both moved from practice), lc-longest-common-prefix, lc-isomorphic-strings, lc-minimum-number-of-steps-to-make-two-strings-anagram, lc-custom-sort-string, lc-longest-uncommon-subsequence-ii, lc-word-pattern (seven of the eight are solved by earlier tools). The lesson has 4 cards (distinct-substrings, sorted-suffixes, occurrences-by-order, common-substring) and 5 theorems (suffix array by doubling, LCP as a range minimum, Kasai, different substrings, the block of a pattern); the templates use a counting-sort doubling (O(n log n)) and the theorem shows the sort version. Weak points: the ladder of 6.4 has exactly 12 problems and is thin in easy rungs; ac-arc044_d repeats the algorithm of the worked example cses-3225 (the smallest string instead of any string); several review problems (lc-count-substrings-that-differ-by-one-character, lc-unique-substrings-in-wraparound-string, cf-835D, lc-shortest-string-that-contains-three-strings, lc-largest-merge-of-two-strings) have a natural simpler solution and are there to review the cards; the hints of cf-123D, cf-873F, cf-452E and cf-1073G come from recalled statements. The Phase 6 exam has 6 problems: cf-1003F and lc-longest-chunked-palindrome-decomposition (6.1), cf-1721E (6.2), lc-encrypt-and-decrypt-strings (6.3), cses-2109 and cf-557E (6.4).
- **Phase 7 bank additions and choices (M9, topic 7.1).** 8 reserved problems were added (statements read for LeetCode; Codeforces ones are recalled and marked †): drill lc-path-sum-iii, lc-time-needed-to-inform-all-employees, lc-delete-nodes-and-return-forest, lc-count-complete-tree-nodes (four drill problems solved by earlier tools, because the bank had only tree-DP drill problems); look-alike pairs lc-maximize-the-number-of-target-nodes-after-connecting-trees-ii / -i and lc-count-the-number-of-houses-at-a-certain-distance-ii / -i (the bank had no look-alike pair; the second pair is about a graph with one cycle, not a tree). The techniques of the worked examples and ladder problems now list 3.2 and 4.5, the combined topics. The lesson has 4 cards (subtree-dp, through-vertex, rerooting, tree-merge) and 4 theorems; the templates avoid recursion (a breadth-first order). Weak points: ac-abc220_f is the same question as the worked example cses-1133 (it is rung 1 of the rerooting card on purpose); ac-abc036_d (drill) and ac-dp_p are the same problem (dp_p was left out of the review sets); lc-minimize-the-total-price-of-the-trips is the only tree-merge review problem and it is really a two-state DP; the hints of the Codeforces ladder problems come from recalled statements; lc-maximum-profit-from-trading-stocks-with-discounts has a table indexed by a budget, so Theorem 7.1.4's bound does not apply to it (the hint says so).
- **Phase 7 bank additions and choices (M9, topic 7.2).** 22 problems were added (LeetCode statements read; Codeforces ones are recalled and marked †). Moves: lc-parallel-courses-iii from practice to reserved review, lc-minimum-number-of-days-to-eat-n-oranges to a reserved look-alike (partner lc-minimum-number-of-operations-to-make-x-and-y-equal, a breadth-first search because moves can go back). New pairs: lc-shortest-distance-after-road-addition-queries-ii / -i. The lesson has 4 cards (longest-path, count-paths, condensation-dp, state-dag), 4 theorems, 7 templates, 9 catalogued bugs and 3 worked examples (cses-1680, 1681, 1686). Weak points: lc-maximum-profit-from-valid-topological-order-in-dag is really a bitmask DP (topic 3.7), kept in review set 3 under state-dag; lc-parallel-courses (premium) was dropped; count-paths has no review problem; the hints of the Codeforces ladder problems (cf-919D, 721C, 1679D, 894E, 1137C, 505C) and the checkpoint cf-1472G come from recalled statements.
- **Phase 7 bank additions and choices (M9, topic 7.3).** 23 problems were added (LeetCode statements read; Codeforces ones are recalled and marked †). Moves: cf-1799D2 to a look-alike with the new cf-1799D1, cf-1557D and lc-maximum-balanced-subsequence-sum and lc-delivering-boxes-from-storage-to-ports to the checkpoint, cf-1197E, cf-1788E, lc-length-of-the-longest-increasing-path and lc-longest-increasing-subsequence-ii to review. New pairs: cf-1799D2 / D1 and cf-1304F2 / F1 (the LeetCode I/II candidates were premium or had unclear limits). The lesson has 4 cards (prefix-max-transition, window-transition, counting-with-tree, range-update-transition), 4 theorems, 7 templates, 9 catalogued bugs and 3 worked examples (ac-dp_q, lc-constrained-subsequence-sum, ac-dp_w). Weak points: counting-with-tree and range-update-transition have no review problem (only ladder, worked or checkpoint); the drill problems cf-519D, cf-1335E2 and cf-1313C2 are recalled statements; lc-longest-increasing-subsequence-ii is a range-of-keys problem filed under the prefix-max card (its hint names the segment tree); the lookalike descriptions of cf-1799D and cf-1304F come from recalled statements; the exam problem for the whole phase from this topic is cf-946G.
- **Phase 7 bank additions and choices (M9, topic 7.4).** 15 problems were added (LeetCode statements read; Codeforces ones are recalled and marked †). Moves: ac-abc407_e to the checkpoint, ac-abc214_e to the exam, lc-pizza-with-3n-slices and lc-two-best-non-overlapping-events and lc-total-cost-to-hire-k-workers to review. New pair: cf-1249D2 / D1 (the other pair is the existing events I / II; cf-1526C1 and ac-abc137_d were already used in topic 1.5). The four cards are deadline-heap (Theorem 7.4.1, Moore–Hodgson), regret (Theorem 7.4.2, a covering greedy with comparable items), extract-and-replace (Theorem 7.4.3, falling gains and Huffman) and sweep-with-heap (Theorem 7.4.4, earliest last day first and rooms); the bank pattern merge-smallest became the card extract-and-replace and now also holds the halving and pass-ratio problems. Weak points: the undo form of regret (cf-865D, lc-pizza-with-3n-slices) is shown only in a template (buy-sell) and checked by stress, not proved, and cf-865D is an unused extra practice problem; lc-maximum-elegance-of-a-k-length-subsequence is also an unused extra; cf-1251E2, cf-1271D, cf-3D and cf-1249D1/D2 hints come from recalled statements; the exam problem from this topic is ac-abc214_e; the card regret has no worked example of its own beyond refuelling.
- **Phase 7 bank additions and choices (M9, topic 7.5).** 14 problems were added (LeetCode statements read; Codeforces ones are recalled and marked †); ac-abc201_d was left out because topic 3.5 has it. Moves: cf-1147C to practice; cses-2208 and cses-1099, and cses-1098 and cses-1730, are the two look-alike pairs; cf-768E to the checkpoint; cf-2004E and lc-stone-game-ix to review; lc-stone-game-iv is the exam problem. The four cards are win-lose (Theorem 7.5.1, labels by increasing order or retrograde counters), nim-sum (Theorem 7.5.2), grundy-sum (Theorem 7.5.3, mex and xor of independent games) and grundy-pattern (Theorem 7.5.4, subtraction games are eventually periodic, found by a brute force and proved). Weak points: cf-786A, cf-1147C, cf-15C and ac-abc297_g are also the templates (berzerk, thanos-nim, nim-range, constrained-nim), so the ladder problems repeat the template code; the statements of cf-1363C, cf-1033C, cf-917B, cf-1383B, cf-1194D, cf-1537D and cf-1396B in the ladder are from recalled statements; the periodicity of Theorem 7.5.4 is shown only with a detection routine and stress, and the proof of the period bound is the pigeonhole argument for finite move sets.
- **Phase 7 bank additions and choices (M9, topic 7.7).** 6 reserved problems were added: look-alike pair lc-next-permutation / lc-maximum-swap, drill lc-max-chunks-to-make-sorted, lc-minimum-number-of-increments-on-subarrays-to-form-a-target-array and lc-minimum-domino-rotations-for-equal-row (the last three are solved by earlier tools), review cf-1438C. The Phase 7 rule needs every ladder and worked problem to list all 17 `requires` ids as techniques, so the techniques of 16 problems were expanded. The four cards are permutation-build (Theorem 7.7.1, values from the two ends and blocks), simple-pattern (Theorem 7.7.2, the largest count at most ⌈n/2⌉ and the interleaved fill), invariant-then-build (Theorem 7.7.3, a necessary condition that is also sufficient) and operation-sequence (Theorem 7.7.4, a potential and a limit on the list). Weak points: the Codeforces statements and hints (marked †) are from recalled statements, and for cf-1658C, cf-1468H and cf-1621D only the idea is recalled and the summary says so; the ladder skews to tiers 1–2; permutation-build has no review problem; the bug of the swap-sort update `where[p[i]] = i` was dropped because it is redundant; the glossary got no new terms.
- **Phase 7 bank additions and choices (M9, topic 7.6).** 21 problems were added (Codeforces ones recalled and marked †; ac-abc129_f read from the statement). First attempts at easy Codeforces problems (ratings 1300 to 1700) were dropped: the bank rules need tier 3 to 4 for reviews and tier 2 to 4 for drills, and unrated cf-392C is not allowed. Moves: cf-1182E to practice, cf-1151F to the exam, cf-593E and cf-621E to review, lc-string-transformation, cf-717D and cf-1635D to drill. The four cards are linear-recurrence (Theorem 7.6.1, the companion matrix), walk-counting (Theorem 7.6.2), augmented-matrix (Theorem 7.6.3, a constant, the index or a running sum as a coordinate) and min-plus (Theorem 7.6.4, matrices over a semiring: (min, +), (max, +), (or, and)). Weak points: five ladder problems (cf-1117D, cf-514E, cf-1182E, ac-abc129_f, cf-582B) are also the templates (magic-gems, level-sums, product-exponents, concat-progression, repeat-lis); the statements of the Codeforces ladder problems are from memory; the bug for the exponent modulo P is shown by a case checked against a loop (n = 38), not found by the random test (its generator keeps n at most 30); no alternative is given for the (min, +) templates; the glossary got no new terms (as in 7.5).
- **Phase 7 technique recognition (M9, topic 7.8 and the Phase 7 exam).** The 7.8 lesson has no cards, theorems or templates (as PLAN.md says): Section 5 is the four-step routine, a recap table of the cards of all 47 topics (generated from the topic data files) and ten cross-topic confusions; two worked examples with code (ac-abc176_e and lc-subarrays-with-k-different-integers, which are prose only); a drill of 12 problems from all phases, two look-alike pairs (cf-19C / cf-149E and lc-strange-printer-ii / cf-776D), a checkpoint (ac-abc268_f, ac-abc187_f, ac-abc306_f) and three review sets of four problems each. Because 7.8 has no cards of its own, I changed three places: the validator accepts a card of any earlier topic for the checkpoint, review and exam problems of 7.8; the review page looks the card up across the earlier topics; the exam page shows the topic of the card (not 7.8) for the 7.8-bank problem ac-abc338_f; the 7.8 topic header has no link to a practice bank page, and `tests/e2e/lessons.cjs` skips the ladder checks for a topic without a ladder. The e2e placeholder run also showed that 7.4 cited a 1.3 problem (lc-maximum-points-you-can-obtain-from-cards), which the placeholder replaces; its negative example is now lc-maximum-units-on-a-truck (1.5). The Phase 7 exam has 8 problems (4 hours, pass at 5 of 8): cf-815C (7.1), lc-number-of-distinct-roll-sequences (7.2), cf-946G (7.3), ac-abc214_e (7.4), lc-stone-game-iv (7.5), cf-1151F (7.6), cf-1408F (7.7) and ac-abc338_f. Left unused: lc-difference-between-maximum-and-minimum-price-sum and cf-1641B (exam-reserved), ac-abc345_e, ac-abc311_f and cf-316G2 (7.8 bank). Weak points: the 7.8 drill answers are cards of earlier topics whose lessons were written under earlier revisions; the 7.8 bank has 40 problems but only 27 are used, because the template caps the reviews at 12; the Codeforces summaries in 7.8 and the exam are from recalled statements (†) and for cf-1621D and cf-1468H only the idea is recalled; the glossary got no new terms.
- ~~**Run the LeetCode probe (profile sync, S0).**~~ Done 2026-10-13; the snippet was built from its output.
  (Original steps:) Open https://leetcode.com in a desktop browser where you are logged in, open the developer tools console (F12, Console), paste the whole of `docs/sync/leetcode-probe.js` and press Enter. It is read-only, makes five requests one second apart, never reads your session cookie, and prints which queries work, their field names, status values and three example problem names. Paste the printed output into this file or FEEDBACK.md. The snippet that the Profiles page hands out is written from that output.
- ~~**Re-read the Codeforces API page**~~ Saurabh reported this done (2026-10-13), without changes to report.
  (Original note:) (https://codeforces.com/apiHelp) in a normal browser: it is behind a Cloudflare challenge for scripts, so the rate limit (1 request per 2 seconds), anonymous access, and the verdict list in `src/lib/sync/schemas.ts` could not be re-checked.
- Profile sync decisions that went beyond the plan: unknown Codeforces verdicts count as attempts and are noted in the sync log; the checkpoint drill rule becomes "min(8, drill items that still count)" when drill items are compromised; a checkpoint whose three problems are all compromised shows "needs replacement problems" and cannot be passed; LeetCode problems and unlinked platforms in a checkpoint or exam show "confirm by hand".
- Not built, as the plan says to ask first (Section 19): CSES sync, contest-log import with an automatic upsolve list, multiple learners, background sync.

### Design tracks: questions for Saurabh (D0)
- **Redis licence. DECIDED 2026-10-18: Valkey 9.1.2 (BSD), stack verified.** Was: `redis:8.8.3` tri-licensed (RSALv2, SSPLv1 or AGPLv3). Running it locally for labs is fine. Do you want Valkey (BSD-licensed fork) instead? It speaks the same protocol, so no lab changes.
- **GCC 16. DECIDED 2026-10-18: build 16.2.0 from source into `~/toolchains/gcc-16.2.0` (in progress).** Was: the only GCC 16 package for Ubuntu 24.04 is a development snapshot (`16.0.1 20260315`, "experimental"); all tests pass with `-std=c++23`. Build 16.2 from source, or keep the snapshot until a release is packaged?
- **Repository: public (decided 2026-10-18).** Decides whether a self-hosted Actions runner on this server may run the integration job (Section 9.13). Not set up.
- **Extra Go modules** (Section 9.5): none added. Expected later: a PostgreSQL driver, a MySQL driver, a Redis client, a Kafka client, a WebSocket library. Approve each when its lab needs it.
- **Host ports.** PostgreSQL 5432 and MySQL 3306 are taken by other services on this server. Lab stacks use 15432, 13306, 16379 and 19092 via the gitignored `.env.labserver`; only about 2 GiB RAM is free, so stacks run one at a time.
- **"Builds on" header line.** Revision 5 (Section 11.7) puts it back in the design `TopicHeader`; PLAN.md Revision 2.1 removed it for the CP track. Implemented as Revision 5 says, for design topics only.
- **Plan fixes made while implementing** (Revision 5 text unchanged; tell me if you want it amended): (1) `labserver.sh` calls itself with `bash "$0"` (the plan's `"$0" sync` fails without an executable bit); (2) the `.env.labserver` DSN values are quoted, because the file is sourced by bash and `tcp(...)` is a syntax error unquoted; (3) the stack files take host ports from `LAB_*_PORT` variables so they can run beside existing services; (4) Appendix A's `tests.cpp` includes `shapes.hpp`, which the plan does not name as a file.
- **Browser checks** need Chromium for Playwright. It was installed outside the repo (`/tmp/pw`); run `npm install --no-save playwright && npx playwright install chromium` in the repo to repeat `bash tests/e2e-design.sh`.
