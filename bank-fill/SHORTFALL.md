# Bank fill: shortfall report (completed topics 0.1–3.8)

Measured on the bank as it stood before any addition (commit bea6b38) and after the fill. Topics 4.1 onward are not touched (their lessons are pending).

| Topic | Practice before → after | Reserved before → after | Patterns below rule before → after | Purpose gaps before → after | Added | Status now |
|---|---|---|---|---|---|---|
| 0.1 | 28 → 32 | 27 → 31 | 4 → 1 | 5 → 1 | 8 | short |
| 0.2 | 22 → 25 | 29 → 31 | 2 → 0 | 2 → 0 | 5 | complete |
| 0.3 | 40 → 40 | 31 → 33 | 0 → 0 | 2 → 0 | 2 | complete |
| 0.4 | 23 → 23 | 33 → 35 | 0 → 0 | 2 → 0 | 2 | complete |
| 0.5 | 29 → 32 | 37 → 42 | 1 → 0 | 5 → 0 | 8 | complete |
| 0.6 | 35 → 35 | 34 → 35 | 0 → 0 | 1 → 0 | 1 | complete |
| 1.1 | 23 → 25 | 29 → 32 | 2 → 0 | 3 → 0 | 5 | short |
| 1.2 | 22 → 30 | 34 → 35 | 4 → 0 | 1 → 0 | 9 | complete |
| 1.3 | 24 → 26 | 35 → 36 | 2 → 0 | 1 → 0 | 3 | complete |
| 1.4 | 20 → 23 | 35 → 37 | 3 → 2 | 2 → 0 | 5 | short |
| 1.5 | 20 → 24 | 33 → 35 | 3 → 0 | 2 → 0 | 6 | complete |
| 1.6 | 16 → 20 | 21 → 23 | 4 → 4 | 10 → 8 | 6 | short |
| 1.7 | 22 → 24 | 27 → 31 | 2 → 0 | 4 → 0 | 6 | complete |
| 2.1 | 24 → 25 | 27 → 30 | 2 → 1 | 4 → 1 | 4 | short |
| 2.2 | 14 → 16 | 18 → 18 | 4 → 4 | 13 → 13 | 2 | short |
| 2.3 | 24 → 26 | 26 → 30 | 1 → 0 | 5 → 1 | 6 | short |
| 2.4 | 15 → 18 | 18 → 18 | 3 → 2 | 13 → 13 | 3 | short |
| 3.1 | 22 → 24 | 29 → 32 | 1 → 0 | 3 → 0 | 5 | complete |
| 3.2 | 33 → 35 | 31 → 32 | 2 → 1 | 1 → 0 | 3 | short |
| 3.3 | 19 → 21 | 27 → 30 | 4 → 3 | 5 → 2 | 5 | short |
| 3.4 | 17 → 20 | 24 → 26 | 2 → 1 | 7 → 5 | 5 | short |
| 3.5 | 22 → 23 | 32 → 34 | 1 → 1 | 2 → 0 | 3 | short |
| 3.6 | 21 → 21 | 23 → 23 | 2 → 2 | 8 → 8 | 0 | short |
| 3.7 | 20 → 20 | 22 → 22 | 2 → 2 | 10 → 10 | 0 | short |
| 3.8 | 14 → 14 | 19 → 19 | 3 → 3 | 12 → 12 | 0 | short |

## Codeforces rating ceiling check (FILL plan Section 6, item 1)
No Codeforces problem in the bank is above its phase ceiling; the validator now enforces it for every bank file.

## 0.1 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 28 | 32 | 20 | 30 |
| Reserved total | 27 | 31 | 24 | 30 |

Practice by tier (after): T1 26, T2 3, T3 3, T4 0, T5 0

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): fast-io 0/0, overflow-64bit 12/3, multi-test 8/3, integer-rounding 12/3

Platforms (practice, after): cses 3, atcoder 17, leetcode 3, codeforces 9

Reserved by purpose (before → after): drill 8→8/8, later_drill 1→4/4, lookalike 5→5/4, checkpoint 3→3/3, review 9→10/10, exam 1→1/2

Patterns below the rule: before fast-io, overflow-64bit, multi-test, integer-rounding; after fast-io. Patterns in no checkpoint/review problem: before fast-io; after fast-io.

Added: `lc-account-balance-after-rounded-purchase` (p, T2, integer-rounding), `lc-count-total-number-of-colored-cells` (p, T3, overflow-64bit), `cf-1692A` (p, T2, multi-test), `cf-1921C` (p, T3, multi-test), `ac-abc178_b` (r/later_drill, T2, overflow-64bit), `cf-1560A` (r/review, T3, multi-test), `ac-abc341_b` (r/later_drill, T2, overflow-64bit), `ac-abc400_b` (r/later_drill, T2, overflow-64bit).

**Exhaustion record.** Still short on two counts. (1) Pattern `fast-io` has no practice problem: no problem judges input speed alone at these ratings, and the pattern is better folded into the lesson as a rule (question for Saurabh, option 3 of FILL plan Section 4). (2) Exam has 1 of 2: a second tier 3–4 problem that uses nothing beyond 0.1 was not found. Searched: the 79 unused AtCoder ABC A–C tasks whose statements mention bounds of 10^9 or more, the free LeetCode Math tag (Easy and Medium, unused), and the 40 most-solved unused Codeforces implementation/math problems rated 800–1000. Main drop reasons: the solution needs parity or divisibility (0.4), sorting (1.1) or a set (0.6), or the task is solved without overflow or rounding care (so it does not need 0.1).

## 0.2 (status before: short, now: complete)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 22 | 25 | 20 | 30 |
| Reserved total | 29 | 31 | 24 | 30 |

Practice by tier (after): T1 4, T2 13, T3 6, T4 1, T5 1

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): budget-from-constraints 5/3, closed-form 10/4, amortised-total 6/3, harmonic-loops 4/3

Platforms (practice, after): atcoder 15, cses 3, codeforces 3, leetcode 4

Reserved by purpose (before → after): drill 8→8/8, later_drill 4→4/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→10/10, exam 1→2/2

Patterns below the rule: before budget-from-constraints, harmonic-loops; after none. Patterns in no checkpoint/review problem: before none; after none.

Added: `ac-abc152_d` (p, T3, budget-from-constraints), `lc-count-square-sum-triples` (p, T1, budget-from-constraints), `ac-abc134_d` (p, T3, harmonic-loops), `ac-abc180_d` (r/review, T3, closed-form), `ac-abc133_d` (r/exam, T3, closed-form).

## 0.3 (status before: short, now: complete)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 40 | 40 | 20 | 30 |
| Reserved total | 31 | 33 | 24 | 30 |

Practice by tier (after): T1 14, T2 14, T3 11, T4 0, T5 1

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): direct-simulation 10/3, grid-processing 10/4, string-processing 10/3, case-analysis 10/3

Platforms (practice, after): atcoder 22, codeforces 13, leetcode 4, cses 1

Reserved by purpose (before → after): drill 8→8/8, later_drill 6→6/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→10/10, exam 1→2/2

Patterns below the rule: before none; after none. Patterns in no checkpoint/review problem: before none; after none.

Added: `ac-abc241_c` (r/review, T3, grid-processing), `ac-abc218_c` (r/exam, T3, grid-processing).

## 0.4 (status before: short, now: complete)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 23 | 23 | 20 | 30 |
| Reserved total | 33 | 35 | 24 | 30 |

Practice by tier (after): T1 7, T2 12, T3 3, T4 0, T5 1

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): parity 4/3, divisibility 6/3, gcd-lcm 6/3, mod-arithmetic-basic 7/3

Platforms (practice, after): codeforces 3, cses 4, atcoder 13, leetcode 3

Reserved by purpose (before → after): drill 8→8/8, later_drill 7→7/4, lookalike 5→5/4, checkpoint 3→3/3, review 9→10/10, exam 1→2/2

Patterns below the rule: before none; after none. Patterns in no checkpoint/review problem: before none; after none.

Added: `ac-abc276_d` (r/exam, T3, gcd-lcm), `cf-1543A` (r/review, T3, gcd-lcm).

## 0.5 (status before: short, now: complete)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 29 | 32 | 20 | 30 |
| Reserved total | 37 | 42 | 24 | 30 |

Practice by tier (after): T1 3, T2 14, T3 11, T4 4, T5 0

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): nested-loops 6/3, subset-bitmask 8/3, permutations 5/3, recursive-choices 7/3, enumerate-answer 6/4

Platforms (practice, after): atcoder 18, cses 3, leetcode 7, codeforces 4

Reserved by purpose (before → after): drill 5→8/8, later_drill 14→14/4, lookalike 5→5/4, checkpoint 3→3/3, review 9→10/10, exam 1→2/2

Patterns below the rule: before permutations; after none. Patterns in no checkpoint/review problem: before nested-loops; after none.

Added: `lc-permutation-sequence` (p, T4, permutations), `cf-143A` (p, T3, enumerate-answer), `cf-6A` (p, T3, subset-bitmask), `ac-abc173_c` (r/drill, T3, subset-bitmask), `ac-abc404_d` (r/drill, T3, recursive-choices), `ac-abc302_c` (r/drill, T2, permutations), `ac-abc197_c` (r/exam, T3, subset-bitmask), `cf-886A` (r/review, T3, nested-loops).

## 0.6 (status before: short, now: complete)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 35 | 35 | 20 | 30 |
| Reserved total | 34 | 35 | 24 | 30 |

Practice by tier (after): T1 3, T2 16, T3 11, T4 4, T5 1

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): set-membership 9/3, map-counting 10/4, ordered-set-lookup 5/3, heap-extract 4/4, stack-queue 7/3

Platforms (practice, after): cses 2, atcoder 17, leetcode 13, codeforces 3

Reserved by purpose (before → after): drill 8→8/8, later_drill 8→8/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→10/10, exam 2→2/2

Patterns below the rule: before none; after none. Patterns in no checkpoint/review problem: before set-membership; after none.

Added: `lc-longest-square-streak-in-an-array` (r/review, T3, set-membership).

## 1.1 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 23 | 25 | 20 | 30 |
| Reserved total | 29 | 32 | 24 | 30 |

Practice by tier (after): T1 6, T2 11, T3 7, T4 0, T5 1

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): sort-then-scan 8/3, custom-order 4/3, sort-with-index 4/3, coordinate-compression 5/3, event-sweep 4/3

Platforms (practice, after): codeforces 3, atcoder 12, cses 2, leetcode 8

Reserved by purpose (before → after): drill 7→8/8, later_drill 3→4/4, lookalike 5→5/4, checkpoint 3→3/3, review 10→10/10, exam 1→2/2

Patterns below the rule: before sort-with-index, coordinate-compression; after none. Patterns in no checkpoint/review problem: before coordinate-compression; after coordinate-compression.

Added: `lc-minimum-swaps-to-sort-by-digit-sum` (p, T3, sort-with-index), `lc-sort-the-jumbled-numbers` (r/drill, T2, custom-order), `lc-minimum-difference-between-highest-and-lowest-of-k-scores` (r/later_drill, T2, sort-then-scan), `lc-describe-the-painting` (r/exam, T3, event-sweep), `ac-abc304_d` (p, T3, coordinate-compression).

**Exhaustion record.** Still short on one rule: pattern `coordinate-compression` appears in no checkpoint or review problem (its practice set now has 5 problems over tiers 1–3). A second tier 3–4 compression problem for a review set was not found. Searched: the 52 unused AtCoder ABC/ARC tasks with coordinates up to 10^9 and 2·10^5 items (by statement), the 15 Codeforces problems whose titles mention compression or rank, and the 214 unused free LeetCode problems tagged sorting (by name and tags). Main drop reasons: the task reduces to sorting or a set without ranks, or needs binary search (1.4) or a Fenwick tree (5.2). Moving a practice problem into a review set needs Saurabh's answer (Step 4); one of ABC 213 C, ABC 273 C or ABC 304 D could be moved.

## 1.2 (status before: short, now: complete)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 22 | 30 | 20 | 30 |
| Reserved total | 34 | 35 | 24 | 30 |

Practice by tier (after): T1 7, T2 5, T3 10, T4 4, T5 4

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): range-sum 11/3, prefix-count-lookup 5/3, difference-array 5/3, prefix-2d 4/3, prefix-extremes 5/3

Platforms (practice, after): leetcode 17, cses 3, atcoder 4, codeforces 6

Reserved by purpose (before → after): drill 8→8/8, later_drill 8→8/4, lookalike 4→4/4, checkpoint 3→3/3, review 10→10/10, exam 1→2/2

Patterns below the rule: before range-sum, prefix-count-lookup, difference-array, prefix-2d; after none. Patterns in no checkpoint/review problem: before none; after none.

Added: `lc-ways-to-make-a-fair-array` (p, T3, range-sum), `lc-count-submatrices-with-equal-frequency-of-x-and-y` (p, T3, prefix-2d), `lc-count-subarrays-with-median-k` (p, T4, prefix-count-lookup), `lc-stamping-the-grid` (p, T5, difference-array), `lc-continuous-subarray-sum` (r/exam, T3, prefix-count-lookup), `ac-abc182_d` (p, T3, range-sum), `cses-3220` (p, T2, range-sum), `cf-363B` (p, T3, range-sum), `cf-1807D` (p, T2, range-sum).

## 1.3 (status before: short, now: complete)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 24 | 26 | 20 | 30 |
| Reserved total | 35 | 36 | 24 | 30 |

Practice by tier (after): T1 4, T2 5, T3 11, T4 3, T5 3

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): shrinkable-window 6/4, fixed-window 5/4, count-windows 6/3, opposite-ends 5/3, merge-walk 4/3

Platforms (practice, after): atcoder 10, leetcode 10, cses 5, codeforces 1

Reserved by purpose (before → after): drill 7→8/8, later_drill 7→7/4, lookalike 4→4/4, checkpoint 3→3/3, review 12→12/10, exam 2→2/2

Patterns below the rule: before count-windows, opposite-ends; after none. Patterns in no checkpoint/review problem: before none; after none.

Added: `lc-count-the-number-of-good-subarrays` (p, T4, count-windows), `lc-squares-of-a-sorted-array` (p, T1, opposite-ends), `lc-minimum-swaps-to-group-all-1s-together-ii` (r/drill, T3, fixed-window).

## 1.4 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 20 | 23 | 20 | 30 |
| Reserved total | 35 | 37 | 24 | 30 |

Practice by tier (after): T1 4, T2 4, T3 11, T4 1, T5 3

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): sorted-search 7/3, answer-search 7/5, real-search 1/1, kth-by-counting 3/2, first-reaching-index 5/3

Platforms (practice, after): leetcode 8, atcoder 6, codeforces 6, cses 3

Reserved by purpose (before → after): drill 9→9/8, later_drill 8→8/4, lookalike 5→5/4, checkpoint 3→3/3, review 9→10/10, exam 1→2/2

Patterns below the rule: before real-search, kth-by-counting, first-reaching-index; after real-search, kth-by-counting. Patterns in no checkpoint/review problem: before real-search, first-reaching-index; after real-search.

Added: `cf-474B` (p, T3, first-reaching-index), `cf-1676E` (p, T3, first-reaching-index), `lc-h-index-ii` (p, T2, first-reaching-index), `lc-random-pick-with-weight` (r/review, T3, first-reaching-index), `lc-maximum-running-time-of-n-computers` (r/exam, T4, answer-search).

**Exhaustion record.** Two patterns remain below the rule. `real-search` has 1 practice problem (Codeforces 780 B †) and is in no checkpoint or review problem: of the 218 unused Codeforces binary-search/ternary-search problems rated 1000–1800 (read by title and tags), the free LeetCode list and the AtCoder ABC/ARC titles with 'search', 'median' or 'k-th', almost all are integer answer-searches in disguise or have a closed formula; none is a clean real-valued halving problem in band. `kth-by-counting` has 3 practice problems over tiers 3 and 5; a tier 2 or 4 problem was not found (LeetCode's other k-th problems need a heap or a later technique, ABC 391 F and ARC 97 A are heap/string problems, Codeforces 448 D is tier 5 again). Proposal for Saurabh: merge `real-search` into `answer-search` (FILL plan Section 4, option 3).

## 1.5 (status before: short, now: complete)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 20 | 24 | 20 | 30 |
| Reserved total | 33 | 35 | 24 | 30 |

Practice by tier (after): T1 3, T2 8, T3 9, T4 1, T5 3

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): exchange-order 6/3, interval-selection 4/3, extreme-first 6/3, sorted-matching 4/3, left-to-right-forced 4/3

Platforms (practice, after): leetcode 11, cses 3, atcoder 9, codeforces 1

Reserved by purpose (before → after): drill 9→9/8, later_drill 7→7/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→10/10, exam 1→2/2

Patterns below the rule: before exchange-order, interval-selection, sorted-matching; after none. Patterns in no checkpoint/review problem: before exchange-order; after none.

Added: `lc-earliest-possible-day-of-full-bloom` (p, T4, exchange-order), `lc-minimum-initial-energy-to-finish-tasks` (p, T5, exchange-order), `lc-minimum-rectangles-to-cover-points` (p, T3, interval-selection), `lc-minimum-processing-time` (p, T2, sorted-matching), `lc-minimum-amount-of-damage-dealt-to-bob` (r/review, T4, exchange-order), `lc-eliminate-maximum-number-of-monsters` (r/exam, T3, sorted-matching).

## 1.6 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 16 | 20 | 20 | 30 |
| Reserved total | 21 | 23 | 24 | 30 |

Practice by tier (after): T1 2, T2 0, T3 10, T4 5, T5 3

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): nearest-greater 9/3, min-max-span 3/3, histogram-rectangle 3/2, window-extreme-deque 2/2, deque-window-condition 3/2

Platforms (practice, after): leetcode 12, cses 4, atcoder 3, codeforces 1

Reserved by purpose (before → after): drill 4→6/8, later_drill 0→0/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→9/10, exam 1→1/2

Patterns below the rule: before min-max-span, histogram-rectangle, window-extreme-deque, deque-window-condition; after min-max-span, histogram-rectangle, window-extreme-deque, deque-window-condition. Patterns in no checkpoint/review problem: before deque-window-condition; after deque-window-condition.

Added: `lc-subarray-with-elements-greater-than-varying-threshold` (p, T4, histogram-rectangle), `lc-find-the-number-of-subarrays-where-boundary-elements-are-maximum` (p, T4, min-max-span), `ac-abc407_f` (p, T5, min-max-span), `lc-count-subarrays-with-cost-less-than-or-equal-to-k` (p, T3, deque-window-condition), `lc-minimum-operations-to-convert-all-elements-to-zero` (r/drill, T3, nearest-greater), `lc-next-greater-element-iv` (r/drill, T4, nearest-greater).

**Exhaustion record.** Practice now meets its minimum (20). Still short: reserved 23 of 24 (drill 6 of 8, later_drill 0 of 4, review 9 of 10, exam 1 of 2) and all four span/deque patterns are below the rule (min-max-span 3 problems, histogram-rectangle 3 over tiers 3–4, window-extreme-deque 2, deque-window-condition 3 over tiers 3–4; deque-window-condition is also in no review problem). Searched: all 43 unused free LeetCode problems tagged monotonic-stack or monotonic-queue (read by title, tags and, for the 12 most promising, the full statement), the 36 unused Codeforces data-structures problems rated 1300–1800, the unused CSES sliding-window and range-query sections, and AtCoder ABC/ARC tasks whose titles or statements mention buildings, windows, rectangles, nearest or visible elements (22 tasks matched by statement text and checked by title). Main drop reasons: n small enough for a double loop, solved by a running maximum, needs binary search (1.4), a segment tree (5.3) or dynamic programming (Phase 3), or the problem is already used in another topic's bank. Proposal for Saurabh (FILL plan Section 4, option 3): merge min-max-span and histogram-rectangle (both are the lesson card 'span of an element'), and merge window-extreme-deque and deque-window-condition (card 'sliding window extremes').

## 1.7 (status before: short, now: complete)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 22 | 24 | 20 | 30 |
| Reserved total | 27 | 31 | 24 | 30 |

Practice by tier (after): T1 5, T2 3, T3 11, T4 3, T5 2

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): xor-identities 5/3, prefix-xor 5/3, per-bit-contribution 4/3, high-bit-first 4/3, bit-identities 6/4

Platforms (practice, after): leetcode 14, codeforces 5, atcoder 4, cses 1

Reserved by purpose (before → after): drill 8→8/8, later_drill 0→4/4, lookalike 4→4/4, checkpoint 3→3/3, review 10→10/10, exam 2→2/2

Patterns below the rule: before prefix-xor, high-bit-first; after none. Patterns in no checkpoint/review problem: before none; after none.

Added: `lc-find-longest-awesome-substring` (p, T4, prefix-xor), `lc-minimize-or-of-remaining-elements-using-operations` (p, T5, high-bit-first), `lc-score-after-flipping-matrix` (r/later_drill, T3, high-bit-first), `lc-minimum-numbers-of-function-calls-to-make-target-array` (r/later_drill, T3, per-bit-contribution), `lc-longest-nice-subarray` (r/later_drill, T3, per-bit-contribution), `lc-minimum-impossible-or` (r/later_drill, T3, bit-identities).

## 2.1 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 24 | 25 | 20 | 30 |
| Reserved total | 27 | 30 | 24 | 30 |

Practice by tier (after): T1 2, T2 5, T3 11, T4 4, T5 3

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): sieve 8/3, spf-factorise 6/4, trial-division 4/3, multiples-sieve 3/3, bezout 4/3

Platforms (practice, after): codeforces 7, leetcode 6, atcoder 9, cses 3

Reserved by purpose (before → after): drill 8→8/8, later_drill 2→4/4, lookalike 3→3/4, checkpoint 3→3/3, review 9→10/10, exam 2→2/2

Patterns below the rule: before trial-division, multiples-sieve; after multiples-sieve. Patterns in no checkpoint/review problem: before none; after none.

Added: `lc-maximum-element-sum-of-a-complete-subset-of-indices` (p, T4, trial-division), `lc-prime-palindrome` (r/review, T3, trial-division), `lc-three-divisors` (r/later_drill, T2, trial-division), `lc-number-of-common-factors` (r/later_drill, T2, trial-division).

**Exhaustion record.** Two gaps remain. (1) `multiples-sieve` has 3 practice problems over tiers 3–5; a fourth was not found. Searched: the 42 unused free LeetCode problems tagged number-theory, the 32 unused AtCoder tasks whose statements mention multiples, divisors or primes with bounds near 10^6 (listed by title), and the unused CSES Mathematics section. Drop reasons: the task needs inclusion–exclusion (2.3), binary search (1.4), a graph or DP, or has bounds small enough for a double loop. (2) Look-alike has 3 of 4: the only completed pair is LeetCode Four Divisors / Count of Numbers Which Are Not Special; the second pair's partner lives in 0.4 (Number of Subarrays With GCD Equal to K / Number of Different Subsequences GCDs). A fourth look-alike needs a free, nearly identical partner that needs a different tool; none was found among the 42 LeetCode candidates.

## 2.2 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 14 | 16 | 20 | 30 |
| Reserved total | 18 | 18 | 24 | 30 |

Practice by tier (after): T1 2, T2 2, T3 3, T4 5, T5 4

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): fast-power 7/4, inverse-prime 4/2, fraction-output 1/1, exponent-reduction 4/2, inverse-general 0/0

Platforms (practice, after): cses 3, leetcode 4, atcoder 4, codeforces 5

Reserved by purpose (before → after): drill 2→2/8, later_drill 0→0/4, lookalike 3→3/4, checkpoint 3→3/3, review 9→9/10, exam 1→1/2

Patterns below the rule: before inverse-prime, fraction-output, exponent-reduction, inverse-general; after inverse-prime, fraction-output, exponent-reduction, inverse-general. Patterns in no checkpoint/review problem: before fraction-output, inverse-general; after fraction-output, inverse-general.

Added: `cf-919E` (p, T5, exponent-reduction), `cf-359C` (p, T5, fast-power).

**Exhaustion record.** Still short: practice 16 of 20 and reserved 18 of 24 (drill 2 of 8, later_drill 0 of 4, look-alike 3 of 4, review 9 of 10, exam 1 of 2); `inverse-general` has no problem, `fraction-output` has 1 and `exponent-reduction` and `inverse-prime` lack a third tier. Searched: the Codeforces number-theory/math problems rated 1300–2100 without combinatorics, dp, graph or data-structure tags (103 candidates, read by title), the 32 unused AtCoder tasks that mention a modulus without binomials, probabilities, strings or graphs, and the unused free LeetCode math problems that avoid dp and combinatorics. Almost every modular-arithmetic problem in band also needs binomial coefficients (2.3), expected values (2.4), a DP (Phase 3) or a data structure; the rest are already in other banks. Options for Saurabh (FILL plan Section 4): accept 2.2 as short; lower its minimums (for example practice 16, reserved 18); merge `inverse-general` into `inverse-prime`; or allow Codeforces problems up to 2300 for this topic.

## 2.3 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 24 | 26 | 20 | 30 |
| Reserved total | 26 | 30 | 24 | 30 |

Practice by tier (after): T1 1, T2 6, T3 7, T4 5, T5 7

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): ncr-mod-p 8/5, product-sum-rules 5/4, stars-bars 4/3, include-exclude 5/3, bijection-paths 4/3

Platforms (practice, after): leetcode 10, cses 6, codeforces 4, atcoder 6

Reserved by purpose (before → after): drill 8→8/8, later_drill 1→4/4, lookalike 3→3/4, checkpoint 3→3/3, review 9→10/10, exam 2→2/2

Patterns below the rule: before include-exclude; after none. Patterns in no checkpoint/review problem: before none; after none.

Added: `lc-kth-smallest-amount-with-single-denomination-combination` (p, T4, include-exclude), `lc-find-nth-smallest-integer-with-k-one-bits` (r/review, T4, ncr-mod-p), `lc-direction-assignments-with-exactly-k-visible-people` (r/later_drill, T3, ncr-mod-p), `lc-find-the-n-th-value-after-k-seconds` (r/later_drill, T2, bijection-paths), `lc-count-the-number-of-computer-unlocking-permutations` (r/later_drill, T3, product-sum-rules), `cses-2185` (p, T3, include-exclude).

**Exhaustion record.** One gap remains: look-alikes are 3 of 4. All three have their partner in another topic's bank (Ugly Number III with Minimize the Maximum of Two Arrays in 1.4, Distribute Candies Among Children II with its Easy version in 0.5, ABC 126 C with ABC 154 D in 2.4), so a fourth needs a new nearly identical pair whose two problems need different tools. Searched: the 14 unused free LeetCode combinatorics problems that avoid dp, graph and string tags (all read by title, 6 by statement), the unused CSES Mathematics section, and AtCoder tasks whose statements ask for counts of 'at least one', 'none of' or 'exactly k' (11 candidates, read by title). No such pair was found.

## 2.4 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 15 | 18 | 20 | 30 |
| Reserved total | 18 | 18 | 24 | 30 |

Practice by tier (after): T1 1, T2 1, T3 5, T4 3, T5 8

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): indicator-linearity 5/3, contribution-total 6/2, geometric-wait 4/3, tail-sum 3/2

Platforms (practice, after): leetcode 1, atcoder 8, codeforces 7, cses 2

Reserved by purpose (before → after): drill 3→3/8, later_drill 0→0/4, lookalike 2→2/4, checkpoint 3→3/3, review 9→9/10, exam 1→1/2

Patterns below the rule: before contribution-total, geometric-wait, tail-sum; after contribution-total, tail-sum. Patterns in no checkpoint/review problem: before geometric-wait; after geometric-wait.

Added: `cf-312B` (p, T2, geometric-wait), `cf-621C` (p, T4, indicator-linearity), `cf-204C` (p, T5, contribution-total).

**Exhaustion record.** Still short: practice 18 of 20 and reserved 18 of 24 (drill 3 of 8, later_drill 0 of 4, look-alike 2 of 4, review 9 of 10, exam 1 of 2); `geometric-wait` and `tail-sum` each have 3–4 problems over 2–3 tiers and `geometric-wait` is in no review problem. Searched: the 18 unused AtCoder tasks that mention an expected value (ABC 189–417 and ARC; read by title and statement head), the Codeforces probability problems rated 1300–2100 without dp, graph or data-structure tags (10 candidates), the free LeetCode probability and math lists, and the unused CSES Mathematics section. Almost every in-band expected-value problem needs a DP over states (Phase 3), a Fenwick tree, or inclusion–exclusion with binomials (2.3 is allowed but those problems are already used). Options for Saurabh: accept 2.4 as short; lower its minimums (for example practice 18, reserved 18); or allow dynamic-programming-based expectation problems here, as later look-alike or review items only.

## 3.1 (status before: short, now: complete)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 22 | 24 | 20 | 30 |
| Reserved total | 29 | 32 | 24 | 30 |

Practice by tier (after): T1 2, T2 10, T3 5, T4 3, T5 4

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): generate-all 7/3, constraint-placement 7/3, bound-pruning 4/3, meet-in-middle 6/3

Platforms (practice, after): leetcode 14, atcoder 8, codeforces 1, cses 1

Reserved by purpose (before → after): drill 6→8/8, later_drill 4→4/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→10/10, exam 3→3/2

Patterns below the rule: before constraint-placement; after none. Patterns in no checkpoint/review problem: before none; after none.

Added: `lc-tiling-a-rectangle-with-the-fewest-squares` (p, T4, constraint-placement), `lc-construct-the-lexicographically-largest-valid-sequence` (r/review, T3, constraint-placement), `lc-find-the-punishment-number-of-an-integer` (r/drill, T2, generate-all), `lc-maximum-points-in-an-archery-competition` (r/drill, T3, generate-all), `ac-abc196_d` (p, T3, constraint-placement).

## 3.2 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 33 | 35 | 20 | 30 |
| Reserved total | 31 | 32 | 24 | 30 |

Practice by tier (after): T1 4, T2 14, T3 11, T4 5, T5 1

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): linear-state 12/3, extra-small-state 10/4, two-index 6/3, memo-recursion 4/3, reconstruct 3/3

Platforms (practice, after): atcoder 13, leetcode 16, codeforces 5, cses 1

Reserved by purpose (before → after): drill 7→8/8, later_drill 4→4/4, lookalike 4→4/4, checkpoint 3→3/3, review 10→10/10, exam 3→3/2

Patterns below the rule: before two-index, reconstruct; after reconstruct. Patterns in no checkpoint/review problem: before reconstruct; after reconstruct.

Added: `lc-champagne-tower` (p, T2, two-index), `lc-minimum-difficulty-of-a-job-schedule` (p, T4, two-index), `lc-minimum-swaps-to-make-sequences-increasing` (r/drill, T3, extra-small-state).

**Exhaustion record.** Still short on composition: pattern `reconstruct` has 3 practice problems over tiers 2–4 and is in no checkpoint or review problem. Searched: the 56 unused free LeetCode dynamic-programming problems that avoid string, tree, graph, bitmask and combinatorics tags, the 13 unused AtCoder tasks that ask to print one optimal choice with small bounds (listed by title and checked against their statements), and the unused CSES dynamic-programming section. Almost every task that prints the chosen items is a knapsack, LIS/LCS or interval problem and belongs to 3.3–3.6 (ABC 369 F is kept for 3.4). Moving a practice problem to a review set needs Saurabh's answer (Step 4).

## 3.3 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 19 | 21 | 20 | 30 |
| Reserved total | 27 | 30 | 24 | 30 |

Practice by tier (after): T1 0, T2 7, T3 8, T4 4, T5 2

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): zero-one 6/4, value-indexed 1/1, unbounded 4/1, subset-sums 6/3, bounded 4/2

Platforms (practice, after): cses 3, leetcode 8, atcoder 8, codeforces 2

Reserved by purpose (before → after): drill 6→8/8, later_drill 2→2/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→10/10, exam 3→3/2

Patterns below the rule: before value-indexed, unbounded, subset-sums, bounded; after value-indexed, unbounded, bounded. Patterns in no checkpoint/review problem: before value-indexed; after value-indexed.

Added: `lc-count-of-sub-multisets-with-bounded-sum` (p, T4, bounded), `lc-number-of-great-partitions` (p, T4, subset-sums), `lc-minimum-time-to-make-array-sum-at-most-x` (r/review, T4, zero-one), `lc-maximum-value-of-k-coins-from-piles` (r/drill, T4, zero-one), `lc-minimum-operations-to-form-subset-sum-i` (r/drill, T3, subset-sums).

**Exhaustion record.** Practice now meets its minimum (21). Still short on composition: `value-indexed` has 1 practice problem (AtCoder ABC 364 E) and is in no review problem; `unbounded` has 4 problems all in tier 2; `bounded` has 4 over tiers 3–4; later_drill is 2 of 4. Searched: the 57 unused free LeetCode dynamic-programming problems with coin, sum, subset, partition, profit or capacity in the name (read by title, 9 by statement; two Premium problems were skipped), the unused AtCoder tasks whose statements mention unlimited use of items or weights up to 10^9 with N ≤ 1000 (8 candidates: all greedy, graph or counting problems), and the unused CSES dynamic-programming section. Weights up to 10^9 with small total value occur in AtCoder's educational contest (already used as the look-alike pair) and in Codeforces problems rated above 2000; unbounded problems at tier 3–4 are mostly counting variants that belong to 3.5.

## 3.4 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 17 | 20 | 20 | 30 |
| Reserved total | 24 | 26 | 24 | 30 |

Practice by tier (after): T1 1, T2 7, T3 6, T4 2, T5 4

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): lis 7/4, lis-reduction 4/3, lcs 5/2, edit-distance 4/3

Platforms (practice, after): leetcode 11, cses 2, atcoder 6, codeforces 1

Reserved by purpose (before → after): drill 4→6/8, later_drill 2→2/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→9/10, exam 2→2/2

Patterns below the rule: before lis-reduction, lcs; after lcs. Patterns in no checkpoint/review problem: before edit-distance; after edit-distance.

Added: `ac-abc369_f` (p, T5, lis-reduction), `lc-find-maximum-removals-from-source-string` (p, T3, lcs), `lc-longest-unequal-adjacent-groups-subsequence-ii` (p, T3, lis), `lc-longest-subsequence-with-decreasing-adjacent-difference` (r/drill, T4, lis), `lc-find-the-maximum-length-of-valid-subsequence-ii` (r/drill, T3, lis).

**Exhaustion record.** Practice now meets its minimum (20). Still short: `lcs` has 5 practice problems over tiers 2–3 only, `edit-distance` is in no checkpoint or review problem, and reserved has drill 6 of 8, later_drill 2 of 4, review 9 of 10 (reserved total 29, above its minimum). Searched: the unused free LeetCode dynamic-programming problems whose names mention subsequences, strings, arrays, increasing or distinct (about 150 names read, 12 statements), the unused AtCoder tasks with two strings or sequences and N ≤ 5000 (1 candidate in the cached statements), and the unused CSES dynamic-programming section. Edit-distance and LCS problems beyond the textbook ones are rare below rating 1900; the harder variants add an automaton (6.2) or a segment tree (Phase 5). ABC 369 F was added as the tier 5 chain problem.

## 3.5 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 22 | 23 | 20 | 30 |
| Reserved total | 32 | 34 | 24 | 30 |

Practice by tier (after): T1 0, T2 8, T3 9, T4 5, T5 1

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): grid-paths 7/3, sequence-counting 8/3, partition-counting 3/2, range-sum-transition 5/3

Platforms (practice, after): cses 2, leetcode 11, atcoder 7, codeforces 3

Reserved by purpose (before → after): drill 8→8/8, later_drill 2→4/4, lookalike 4→4/4, checkpoint 4→4/3, review 10→10/10, exam 4→4/2

Patterns below the rule: before partition-counting; after partition-counting. Patterns in no checkpoint/review problem: before partition-counting; after partition-counting.

Added: `lc-count-number-of-ways-to-place-houses` (r/later_drill, T2, sequence-counting), `lc-count-paths-with-the-given-xor-value` (r/later_drill, T3, grid-paths), `lc-find-the-count-of-monotonic-pairs-ii` (p, T4, range-sum-transition).

**Exhaustion record.** One gap remains: pattern `partition-counting` has 3 practice problems over tiers 2–3 and is in no checkpoint or review problem. Searched: the unused free LeetCode dynamic-programming problems whose names mention ways, count, number-of, paths, sequences or dice (about 90 names read, 3 statements), the unused AtCoder tasks that ask for a number of ways with a sum constraint and a modulus (0 matches in the cached statements), and the unused CSES counting sections (already used up in 3.3 and 3.5). Most partition-counting tasks are coin-change variants placed in 3.3, or digit and composition counts that need binomials.

## 3.6 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 21 | 21 | 20 | 30 |
| Reserved total | 23 | 23 | 24 | 30 |

Practice by tier (after): T1 0, T2 3, T3 10, T4 3, T5 5

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): merge-split 7/4, take-from-ends 5/3, palindrome-segment 5/2, first-element-match 4/2

Platforms (practice, after): atcoder 3, leetcode 12, cses 1, codeforces 5

Reserved by purpose (before → after): drill 4→4/8, later_drill 1→1/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→9/10, exam 2→2/2

Patterns below the rule: before palindrome-segment, first-element-match; after palindrome-segment, first-element-match. Patterns in no checkpoint/review problem: before none; after none.

## 3.7 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 20 | 20 | 20 | 30 |
| Reserved total | 22 | 22 | 24 | 30 |

Practice by tier (after): T1 0, T2 0, T3 8, T4 7, T5 5

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): assignment-mask 9/3, path-mask 5/3, group-mask 2/1, submask-mask 4/2

Platforms (practice, after): atcoder 9, leetcode 6, codeforces 4, cses 1

Reserved by purpose (before → after): drill 3→3/8, later_drill 0→0/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→9/10, exam 3→3/2

Patterns below the rule: before group-mask, submask-mask; after group-mask, submask-mask. Patterns in no checkpoint/review problem: before group-mask; after group-mask.

## 3.8 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 14 | 14 | 20 | 30 |
| Reserved total | 19 | 19 | 24 | 30 |

Practice by tier (after): T1 1, T2 1, T3 4, T4 2, T5 6

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): count-up-to-n 3/3, digit-sum-state 4/3, neighbour-digits 3/2, digit-aggregate 4/2

Platforms (practice, after): atcoder 6, cses 1, leetcode 5, codeforces 2

Reserved by purpose (before → after): drill 2→2/8, later_drill 0→0/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→9/10, exam 1→1/2

Patterns below the rule: before count-up-to-n, neighbour-digits, digit-aggregate; after count-up-to-n, neighbour-digits, digit-aggregate. Patterns in no checkpoint/review problem: before none; after none.

