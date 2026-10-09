# Bank fill: shortfall report (completed topics 0.1–3.8)

Measured on the bank as it stood before any addition (commit bea6b38) and after the fill. Topics 4.1 onward are not touched (their lessons are pending).

| Topic | Practice before → after | Reserved before → after | Patterns below rule before → after | Purpose gaps before → after | Added | Status now |
|---|---|---|---|---|---|---|
| 0.1 | 28 → 32 | 27 → 31 | 4 → 1 | 5 → 1 | 8 | short |
| 0.2 | 22 → 25 | 29 → 31 | 2 → 0 | 2 → 0 | 5 | complete |
| 0.3 | 40 → 40 | 31 → 33 | 0 → 0 | 2 → 0 | 2 | complete |
| 0.4 | 23 → 23 | 33 → 34 | 0 → 0 | 2 → 1 | 1 | short |
| 0.5 | 29 → 29 | 37 → 37 | 1 → 1 | 5 → 5 | 0 | short |
| 0.6 | 35 → 35 | 34 → 34 | 0 → 0 | 1 → 1 | 0 | short |
| 1.1 | 23 → 23 | 29 → 29 | 2 → 2 | 3 → 3 | 0 | short |
| 1.2 | 22 → 22 | 34 → 34 | 4 → 4 | 1 → 1 | 0 | short |
| 1.3 | 24 → 24 | 35 → 35 | 2 → 2 | 1 → 1 | 0 | short |
| 1.4 | 20 → 20 | 35 → 35 | 3 → 3 | 2 → 2 | 0 | short |
| 1.5 | 20 → 20 | 33 → 33 | 3 → 3 | 2 → 2 | 0 | short |
| 1.6 | 16 → 16 | 21 → 21 | 4 → 4 | 10 → 10 | 0 | short |
| 1.7 | 22 → 22 | 27 → 27 | 2 → 2 | 4 → 4 | 0 | short |
| 2.1 | 24 → 24 | 27 → 27 | 2 → 2 | 4 → 4 | 0 | short |
| 2.2 | 14 → 14 | 18 → 18 | 4 → 4 | 13 → 13 | 0 | short |
| 2.3 | 24 → 24 | 26 → 26 | 1 → 1 | 5 → 5 | 0 | short |
| 2.4 | 15 → 15 | 18 → 18 | 3 → 3 | 13 → 13 | 0 | short |
| 3.1 | 22 → 22 | 29 → 29 | 1 → 1 | 3 → 3 | 0 | short |
| 3.2 | 33 → 33 | 31 → 31 | 2 → 2 | 1 → 1 | 0 | short |
| 3.3 | 19 → 19 | 27 → 27 | 4 → 4 | 5 → 5 | 0 | short |
| 3.4 | 17 → 17 | 24 → 24 | 2 → 2 | 7 → 7 | 0 | short |
| 3.5 | 22 → 22 | 32 → 32 | 1 → 1 | 2 → 2 | 0 | short |
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

## 0.4 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 23 | 23 | 20 | 30 |
| Reserved total | 33 | 34 | 24 | 30 |

Practice by tier (after): T1 7, T2 12, T3 3, T4 0, T5 1

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): parity 4/3, divisibility 6/3, gcd-lcm 6/3, mod-arithmetic-basic 7/3

Platforms (practice, after): codeforces 3, cses 4, atcoder 13, leetcode 3

Reserved by purpose (before → after): drill 8→8/8, later_drill 7→7/4, lookalike 5→5/4, checkpoint 3→3/3, review 9→9/10, exam 1→2/2

Patterns below the rule: before none; after none. Patterns in no checkpoint/review problem: before none; after none.

Added: `ac-abc276_d` (r/exam, T3, gcd-lcm).

## 0.5 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 29 | 29 | 20 | 30 |
| Reserved total | 37 | 37 | 24 | 30 |

Practice by tier (after): T1 3, T2 14, T3 9, T4 3, T5 0

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): nested-loops 6/3, subset-bitmask 7/3, permutations 4/2, recursive-choices 7/3, enumerate-answer 5/4

Platforms (practice, after): atcoder 18, cses 3, leetcode 6, codeforces 2

Reserved by purpose (before → after): drill 5→5/8, later_drill 14→14/4, lookalike 5→5/4, checkpoint 3→3/3, review 9→9/10, exam 1→1/2

Patterns below the rule: before permutations; after permutations. Patterns in no checkpoint/review problem: before nested-loops; after nested-loops.

## 0.6 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 35 | 35 | 20 | 30 |
| Reserved total | 34 | 34 | 24 | 30 |

Practice by tier (after): T1 3, T2 16, T3 11, T4 4, T5 1

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): set-membership 9/3, map-counting 10/4, ordered-set-lookup 5/3, heap-extract 4/4, stack-queue 7/3

Platforms (practice, after): cses 2, atcoder 17, leetcode 13, codeforces 3

Reserved by purpose (before → after): drill 8→8/8, later_drill 8→8/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→9/10, exam 2→2/2

Patterns below the rule: before none; after none. Patterns in no checkpoint/review problem: before set-membership; after set-membership.

## 1.1 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 23 | 23 | 20 | 30 |
| Reserved total | 29 | 29 | 24 | 30 |

Practice by tier (after): T1 6, T2 11, T3 5, T4 0, T5 1

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): sort-then-scan 8/3, custom-order 4/3, sort-with-index 3/2, coordinate-compression 4/2, event-sweep 4/3

Platforms (practice, after): codeforces 3, atcoder 11, cses 2, leetcode 7

Reserved by purpose (before → after): drill 7→7/8, later_drill 3→3/4, lookalike 5→5/4, checkpoint 3→3/3, review 10→10/10, exam 1→1/2

Patterns below the rule: before sort-with-index, coordinate-compression; after sort-with-index, coordinate-compression. Patterns in no checkpoint/review problem: before coordinate-compression; after coordinate-compression.

## 1.2 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 22 | 22 | 20 | 30 |
| Reserved total | 34 | 34 | 24 | 30 |

Practice by tier (after): T1 7, T2 3, T3 6, T4 3, T5 3

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): range-sum 6/2, prefix-count-lookup 4/2, difference-array 4/2, prefix-2d 3/3, prefix-extremes 5/3

Platforms (practice, after): leetcode 13, cses 2, atcoder 3, codeforces 4

Reserved by purpose (before → after): drill 8→8/8, later_drill 8→8/4, lookalike 4→4/4, checkpoint 3→3/3, review 10→10/10, exam 1→1/2

Patterns below the rule: before range-sum, prefix-count-lookup, difference-array, prefix-2d; after range-sum, prefix-count-lookup, difference-array, prefix-2d. Patterns in no checkpoint/review problem: before none; after none.

## 1.3 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 24 | 24 | 20 | 30 |
| Reserved total | 35 | 35 | 24 | 30 |

Practice by tier (after): T1 3, T2 5, T3 11, T4 2, T5 3

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): shrinkable-window 6/4, fixed-window 5/4, count-windows 5/2, opposite-ends 4/2, merge-walk 4/3

Platforms (practice, after): atcoder 10, leetcode 8, cses 5, codeforces 1

Reserved by purpose (before → after): drill 7→7/8, later_drill 7→7/4, lookalike 4→4/4, checkpoint 3→3/3, review 12→12/10, exam 2→2/2

Patterns below the rule: before count-windows, opposite-ends; after count-windows, opposite-ends. Patterns in no checkpoint/review problem: before none; after none.

## 1.4 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 20 | 20 | 20 | 30 |
| Reserved total | 35 | 35 | 24 | 30 |

Practice by tier (after): T1 4, T2 3, T3 9, T4 1, T5 3

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): sorted-search 7/3, answer-search 7/5, real-search 1/1, kth-by-counting 3/2, first-reaching-index 2/2

Platforms (practice, after): leetcode 7, atcoder 6, codeforces 4, cses 3

Reserved by purpose (before → after): drill 9→9/8, later_drill 8→8/4, lookalike 5→5/4, checkpoint 3→3/3, review 9→9/10, exam 1→1/2

Patterns below the rule: before real-search, kth-by-counting, first-reaching-index; after real-search, kth-by-counting, first-reaching-index. Patterns in no checkpoint/review problem: before real-search, first-reaching-index; after real-search, first-reaching-index.

## 1.5 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 20 | 20 | 20 | 30 |
| Reserved total | 33 | 33 | 24 | 30 |

Practice by tier (after): T1 3, T2 7, T3 8, T4 0, T5 2

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): exchange-order 4/1, interval-selection 3/3, extreme-first 6/3, sorted-matching 3/3, left-to-right-forced 4/3

Platforms (practice, after): leetcode 7, cses 3, atcoder 9, codeforces 1

Reserved by purpose (before → after): drill 9→9/8, later_drill 7→7/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→9/10, exam 1→1/2

Patterns below the rule: before exchange-order, interval-selection, sorted-matching; after exchange-order, interval-selection, sorted-matching. Patterns in no checkpoint/review problem: before exchange-order; after exchange-order.

## 1.6 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 16 | 16 | 20 | 30 |
| Reserved total | 21 | 21 | 24 | 30 |

Practice by tier (after): T1 2, T2 0, T3 9, T4 3, T5 2

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): nearest-greater 9/3, min-max-span 1/1, histogram-rectangle 2/2, window-extreme-deque 2/2, deque-window-condition 2/2

Platforms (practice, after): leetcode 9, cses 4, atcoder 2, codeforces 1

Reserved by purpose (before → after): drill 4→4/8, later_drill 0→0/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→9/10, exam 1→1/2

Patterns below the rule: before min-max-span, histogram-rectangle, window-extreme-deque, deque-window-condition; after min-max-span, histogram-rectangle, window-extreme-deque, deque-window-condition. Patterns in no checkpoint/review problem: before deque-window-condition; after deque-window-condition.

## 1.7 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 22 | 22 | 20 | 30 |
| Reserved total | 27 | 27 | 24 | 30 |

Practice by tier (after): T1 5, T2 3, T3 11, T4 2, T5 1

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): xor-identities 5/3, prefix-xor 4/2, per-bit-contribution 4/3, high-bit-first 3/2, bit-identities 6/4

Platforms (practice, after): leetcode 12, codeforces 5, atcoder 4, cses 1

Reserved by purpose (before → after): drill 8→8/8, later_drill 0→0/4, lookalike 4→4/4, checkpoint 3→3/3, review 10→10/10, exam 2→2/2

Patterns below the rule: before prefix-xor, high-bit-first; after prefix-xor, high-bit-first. Patterns in no checkpoint/review problem: before none; after none.

## 2.1 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 24 | 24 | 20 | 30 |
| Reserved total | 27 | 27 | 24 | 30 |

Practice by tier (after): T1 2, T2 5, T3 11, T4 3, T5 3

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): sieve 8/3, spf-factorise 6/4, trial-division 3/2, multiples-sieve 3/3, bezout 4/3

Platforms (practice, after): codeforces 7, leetcode 5, atcoder 9, cses 3

Reserved by purpose (before → after): drill 8→8/8, later_drill 2→2/4, lookalike 3→3/4, checkpoint 3→3/3, review 9→9/10, exam 2→2/2

Patterns below the rule: before trial-division, multiples-sieve; after trial-division, multiples-sieve. Patterns in no checkpoint/review problem: before none; after none.

## 2.2 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 14 | 14 | 20 | 30 |
| Reserved total | 18 | 18 | 24 | 30 |

Practice by tier (after): T1 2, T2 2, T3 3, T4 5, T5 2

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): fast-power 6/4, inverse-prime 4/2, fraction-output 1/1, exponent-reduction 3/2, inverse-general 0/0

Platforms (practice, after): cses 3, leetcode 4, atcoder 4, codeforces 3

Reserved by purpose (before → after): drill 2→2/8, later_drill 0→0/4, lookalike 3→3/4, checkpoint 3→3/3, review 9→9/10, exam 1→1/2

Patterns below the rule: before inverse-prime, fraction-output, exponent-reduction, inverse-general; after inverse-prime, fraction-output, exponent-reduction, inverse-general. Patterns in no checkpoint/review problem: before fraction-output, inverse-general; after fraction-output, inverse-general.

## 2.3 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 24 | 24 | 20 | 30 |
| Reserved total | 26 | 26 | 24 | 30 |

Practice by tier (after): T1 1, T2 6, T3 6, T4 4, T5 7

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): ncr-mod-p 8/5, product-sum-rules 5/4, stars-bars 4/3, include-exclude 3/2, bijection-paths 4/3

Platforms (practice, after): leetcode 9, cses 5, codeforces 4, atcoder 6

Reserved by purpose (before → after): drill 8→8/8, later_drill 1→1/4, lookalike 3→3/4, checkpoint 3→3/3, review 9→9/10, exam 2→2/2

Patterns below the rule: before include-exclude; after include-exclude. Patterns in no checkpoint/review problem: before none; after none.

## 2.4 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 15 | 15 | 20 | 30 |
| Reserved total | 18 | 18 | 24 | 30 |

Practice by tier (after): T1 1, T2 0, T3 5, T4 2, T5 7

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): indicator-linearity 4/3, contribution-total 5/2, geometric-wait 3/2, tail-sum 3/2

Platforms (practice, after): leetcode 1, atcoder 8, codeforces 4, cses 2

Reserved by purpose (before → after): drill 3→3/8, later_drill 0→0/4, lookalike 2→2/4, checkpoint 3→3/3, review 9→9/10, exam 1→1/2

Patterns below the rule: before contribution-total, geometric-wait, tail-sum; after contribution-total, geometric-wait, tail-sum. Patterns in no checkpoint/review problem: before geometric-wait; after geometric-wait.

## 3.1 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 22 | 22 | 20 | 30 |
| Reserved total | 29 | 29 | 24 | 30 |

Practice by tier (after): T1 2, T2 10, T3 4, T4 2, T5 4

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): generate-all 7/3, constraint-placement 5/2, bound-pruning 4/3, meet-in-middle 6/3

Platforms (practice, after): leetcode 13, atcoder 7, codeforces 1, cses 1

Reserved by purpose (before → after): drill 6→6/8, later_drill 4→4/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→9/10, exam 3→3/2

Patterns below the rule: before constraint-placement; after constraint-placement. Patterns in no checkpoint/review problem: before none; after none.

## 3.2 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 33 | 33 | 20 | 30 |
| Reserved total | 31 | 31 | 24 | 30 |

Practice by tier (after): T1 4, T2 13, T3 11, T4 4, T5 1

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): linear-state 12/3, extra-small-state 10/4, two-index 4/2, memo-recursion 4/3, reconstruct 3/3

Platforms (practice, after): atcoder 13, leetcode 14, codeforces 5, cses 1

Reserved by purpose (before → after): drill 7→7/8, later_drill 4→4/4, lookalike 4→4/4, checkpoint 3→3/3, review 10→10/10, exam 3→3/2

Patterns below the rule: before two-index, reconstruct; after two-index, reconstruct. Patterns in no checkpoint/review problem: before reconstruct; after reconstruct.

## 3.3 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 19 | 19 | 20 | 30 |
| Reserved total | 27 | 27 | 24 | 30 |

Practice by tier (after): T1 0, T2 7, T3 8, T4 2, T5 2

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): zero-one 6/4, value-indexed 1/1, unbounded 4/1, subset-sums 5/2, bounded 3/1

Platforms (practice, after): cses 3, leetcode 6, atcoder 8, codeforces 2

Reserved by purpose (before → after): drill 6→6/8, later_drill 2→2/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→9/10, exam 3→3/2

Patterns below the rule: before value-indexed, unbounded, subset-sums, bounded; after value-indexed, unbounded, subset-sums, bounded. Patterns in no checkpoint/review problem: before value-indexed; after value-indexed.

## 3.4 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 17 | 17 | 20 | 30 |
| Reserved total | 24 | 24 | 24 | 30 |

Practice by tier (after): T1 1, T2 7, T3 4, T4 2, T5 3

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): lis 6/4, lis-reduction 3/2, lcs 4/2, edit-distance 4/3

Platforms (practice, after): leetcode 9, cses 2, atcoder 5, codeforces 1

Reserved by purpose (before → after): drill 4→4/8, later_drill 2→2/4, lookalike 4→4/4, checkpoint 3→3/3, review 9→9/10, exam 2→2/2

Patterns below the rule: before lis-reduction, lcs; after lis-reduction, lcs. Patterns in no checkpoint/review problem: before edit-distance; after edit-distance.

## 3.5 (status before: short, now: short)
| Measure | Before | After | Minimum | Target |
|---|---|---|---|---|
| Practice total | 22 | 22 | 20 | 30 |
| Reserved total | 32 | 32 | 24 | 30 |

Practice by tier (after): T1 0, T2 8, T3 9, T4 4, T5 1

Practice by pattern (after, count / tiers; each needs ≥ 4 over ≥ 3 tiers): grid-paths 7/3, sequence-counting 8/3, partition-counting 3/2, range-sum-transition 4/3

Platforms (practice, after): cses 2, leetcode 10, atcoder 7, codeforces 3

Reserved by purpose (before → after): drill 8→8/8, later_drill 2→2/4, lookalike 4→4/4, checkpoint 4→4/3, review 10→10/10, exam 4→4/2

Patterns below the rule: before partition-counting; after partition-counting. Patterns in no checkpoint/review problem: before partition-counting; after partition-counting.

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

