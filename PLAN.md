# PLAN.md: Competitive Programming Training Website and Material

**Audience of this file:** an autonomous coding agent working in a git repository.
**Learner:** Saurabh, a backend software engineer new to competitive programming (CP). He submits solutions on the problem platforms themselves (Codeforces, AtCoder, CSES, LeetCode). The site gives him lessons, problem links, hints, drills, and tracking; it does not judge code.

Read this entire file before doing anything, and follow it exactly. Problems are collected up front by a separate plan, `PROBLEM_BANK_PLAN.md`; read it too, and apply its Section 12 changes to this plan once its milestone B1 is merged. If you believe something here is wrong, write the concern in `PROGRESS.md` under "Questions for Saurabh" and continue with work that doesn't depend on it.

**Revision 2 (quality upgrade).** This file was revised after a review of the live site (topics 1.6 and 2.1). The review found five weaknesses, and the revision fixes each one in place:
1. Recognition Cards were abstract and thin → every card now has constraint shapes, a worked "Recognition in action" block, and positive and negative examples (Sections 5, 6.5).
2. Look-alike pairs cited later topics and showed raw slugs → references are structured, may point only to the same or earlier topics, and render as card names (Sections 5, 6.11, 12).
3. Some proofs were too dense for a beginner → a fixed proof layout with size limits (Section 6.4).
4. Theorems had no code to look at → every theorem gets a small tested demo whose output is shown under it (Sections 6.4, 8.6).
5. The page header and the "What you need" list disagreed → both render from one `uses` list in the topic data file (Sections 5, 6.2, 12).
Topics merged before this revision are brought up to the new standard in the retrofit milestone R1 (Section 15).

---

## Table of contents

0. Operating rules
1. Goal and quality bar
2. Tech stack
3. Repository layout
4. Curriculum registry (48 topics)
5. Topic data file: schema
6. Lesson page: exact template and section rules
7. Writing rules
8. Lesson code and testing
9. Problem selection and link checking
10. Site features
11. Other pages and documents
12. Build-time validation
13. Per-topic pipeline
14. Git workflow and deployment
15. Milestones and review gates
16. Progress, resuming, and feedback
17. Definition of Done
18. Failure handling

---

## 0. Operating rules

1. **Never write a problem link, title, or difficulty from memory.** Open every problem page during your work, confirm the title, and read the full statement before using it (Section 9).
2. **Never copy problem statements or editorials** into the repository. Write a one-line summary in your own words and link to the original.
3. **Strict dependency order.** A topic may only rely on itself and topics earlier in the curriculum order (Section 4). Later topics may be named only in the "What this topic does not cover" subsection.
4. **Topic purity.** Every problem assigned to a topic must be solvable with only allowed techniques. You prove this with a short written solution note per problem (Section 9.4). No solution code is written for problems.
5. **All lesson code is tested** (templates, worked examples, bug catalogue) with the two scripts in Section 8. This is the only code in the repository that no judge checks, so it must be right.
6. **One topic at a time, one pipeline step at a time, commit after every step,** updating `PROGRESS.md` in the same commit.
7. **Stop at review gates** (Section 15) until `PROGRESS.md` shows the gate approved.
8. **`npm run build` and `bash scripts/test_units.sh code` must pass** before merging any topic.
9. **Read `FEEDBACK.md` at the start of every session.** Open items come before new topics.

---

## 1. Goal and quality bar

### 1.1 Goal
A self-study website that takes a beginner to roughly Codeforces Expert / Candidate Master, with special emphasis on **recognition**: looking at an unseen problem and deciding which technique applies by verifying a structural property, not by matching surface features.

### 1.2 Quality properties, in priority order
1. **Correct:** proofs hold, lesson code works, links are right, problems fit their topics.
2. **Builds recognition:** each technique is tied to a decisive property that is exactly the precondition of its correctness proof.
3. **Sticks:** spaced reviews, re-solves, and self-tests reinforce each topic over months.
4. **Calibrated:** problem ladders rise in small steps, each adding exactly one new twist.
5. **Readable for Saurabh:** terms defined before use; abbreviations expanded on first use on each page; code shown for every mechanism; every C++ idiom (macros, lambdas, references, STL (Standard Template Library) calls) explained in prose.

### 1.3 Pedagogical inspiration
- **Russian school** (e-maxx / cp-algorithms, ITMO University courses): rigorous definitions, short proofs, understanding why before how, honest struggle before solutions, upsolving.
- **Chinese school** (OI Wiki, Luogu problem lists, Li Yudong's *Advanced Guide to Algorithm Competitions*): finely graded ladders, one new idea per rung, clean templates, solving one problem several ways (一题多解).

You may read these sources to check your understanding. Do not copy their text.

---

## 2. Tech stack

| Concern | Choice |
|---|---|
| Framework | Astro with the Starlight documentation theme (create with `npm create astro@latest -- --template starlight`) |
| Lesson format | MDX files in `src/content/docs/` |
| Structured data | One YAML file per topic in `src/data/topics/`, loaded as an Astro content collection with a Zod schema |
| Math | `remark-math` + `rehype-katex`, KaTeX CSS added via Starlight `customCss` |
| Code display | Starlight's `<Code>` component, fed by importing the tested `.cpp` file with `?raw`, so displayed code is always the tested code |
| Interactive parts | React islands (`npx astro add react`), hydrated with `client:load` |
| Learner data | Browser `localStorage`, with export/import as JSON (Section 10.6) |
| Search | Starlight's built-in Pagefind search |
| Hosting | Saurabh's own server. The site is a static build (`dist/`) served by Caddy or nginx over HTTPS (Section 14.2) |
| Lesson code testing | `g++` and two shell scripts (Section 8) |

Keep dependencies minimal. No database, no server, no login.

---

## 3. Repository layout

```
.
├── PLAN.md                     # this file
├── PROBLEM_BANK_PLAN.md        # how the problem bank is built
├── AGENTS.md                   # one line: "Read PLAN.md fully before any work and follow it exactly."
├── CLAUDE.md                   # same line as AGENTS.md
├── PROGRESS.md                 # Section 16.1
├── FEEDBACK.md                 # Saurabh writes; you read every session (Section 16.3)
├── README.md                   # how to run the site locally, deploy, and where things live
├── astro.config.mjs
├── package.json
├── .env.deploy.example         # Section 14.2 (the real .env.deploy is gitignored)
├── deploy/
│   ├── Caddyfile.example       # Section 14.2
│   └── nginx.conf.example      # Section 14.2
├── scripts/
│   ├── stress.sh               # Section 8.3 (exact code given, tested)
│   ├── test_units.sh           # Section 8.4 (exact code given, tested)
│   └── deploy.sh               # Section 14.2
├── code/                       # lesson code units, by topic
│   └── 1.3/
│       ├── window-sum/         # template unit
│       │   ├── solution.cpp
│       │   ├── brute.cpp
│       │   ├── gen.cpp
│       │   └── tests/1.in, 1.out, ...
│       ├── thm-1/              # theorem demo unit (Section 8.6): solution.cpp + tests/1.in, 1.out
│       └── card-shrinkable-window/   # card example unit (Section 8.6): produces the inline example numbers
├── notes/                      # private solution notes (Section 9.4); NOT rendered on the site
│   └── 1.3.md
└── src/
    ├── content.config.ts       # collections and Zod schemas (Section 5, 12)
    ├── data/
    │   ├── curriculum.yaml     # Section 4
    │   ├── glossary.yaml       # Section 5.4
    │   └── topics/
    │       └── 1-3.yaml        # one per topic (Section 5)
    ├── lib/
    │   ├── data.ts             # loads data, runs cross-file validation (Section 12)
    │   └── storage.ts          # localStorage helpers (Section 10.6)
    ├── components/             # Section 10
    ├── pages/                  # custom pages: dashboard, handbook, glossary, problems, log, progress
    └── content/
        └── docs/
            ├── index.mdx               # home / dashboard entry (Section 10.1)
            ├── method.mdx              # Section 11.1
            ├── phase-0/
            │   ├── index.mdx           # phase intro (Section 11.2)
            │   ├── exam.mdx            # phase exam (Section 11.3)
            │   └── 0-1-cpp-for-cp.mdx  # lessons
            └── phase-1/ ...
```

File naming: topic `1.3` → data file `1-3.yaml`, lesson `phase-1/1-3-two-pointers.mdx`, code folder `code/1.3/`, notes `notes/1.3.md`.

---

## 4. Curriculum registry

Put this into `src/data/curriculum.yaml` in milestone M0. Topics are ordered by `order`, not by id. Topic 1.3 is written first as the exemplar (Section 15) but its `order` stays 9.

**Keywords** are specific phrases that only that topic's lesson would use. Before finishing any lesson, search it (e.g., `grep -inw`) for every keyword of every later topic; matches are allowed only inside "What this topic does not cover".

```yaml
- {order: 1,  id: "0.1", phase: 0, slug: cpp-for-cp,        title: "C++ for competitive programming: I/O, types, overflow, compiling, online judges", requires: [], keywords: ["sync_with_stdio", "fast io"]}
```
(Use that shape for every row below; `target_rating` is the phase band.)

### Phase 0: Foundations (target 800–1000)
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 1 | 0.1 | cpp-for-cp | C++ for CP: I/O, types, overflow, compiling, online judges | — | fast io, sync_with_stdio |
| 2 | 0.2 | complexity | Complexity analysis and reading constraints | 0.1 | big-o, operations per second |
| 3 | 0.3 | implementation | Implementation and simulation | 0.1, 0.2 | simulation |
| 4 | 0.4 | elementary-math | Parity, divisibility, GCD via Euclid, basic modular arithmetic | 0.2 | euclidean algorithm, gcd |
| 5 | 0.5 | brute-force | Brute force: loops, bitmask subsets, permutations, simple recursion | 0.2 | next_permutation, subset enumeration |
| 6 | 0.6 | stl-toolbox | STL toolbox: vector, pair, set, map, priority_queue and their costs | 0.2 | priority_queue, multiset |

### Phase 1: Array techniques (target 1000–1400)
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 7 | 1.1 | sorting | Sorting, comparators, coordinate compression | 0.x | coordinate compression, comparator |
| 8 | 1.2 | prefix-sums | Prefix sums and difference arrays (1D, 2D) | 0.x | prefix sum, difference array |
| 9 | 1.3 | two-pointers | Two pointers and sliding window | 1.1, 1.2 | two pointers, sliding window |
| 10 | 1.4 | binary-search | Binary search: invariant template, search on the answer | 1.1 | binary search, lower_bound, upper_bound |
| 11 | 1.5 | greedy-1 | Greedy I: exchange argument, stays ahead (arrays and sorting only) | 1.1 | exchange argument, greedy stays ahead |
| 12 | 1.6 | monotonic-stack | Monotonic stack and deque | 0.6 | monotonic stack, monotonic deque, next greater element |
| 13 | 1.7 | bits | Bits: XOR properties, prefix XOR, per-bit contribution | 1.2 | prefix xor, bitwise contribution |

### Phase 2: Mathematics I (target 1400–1700)
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 14 | 2.1 | number-theory | Sieve, factorisation, divisors, extended Euclid | 0.4 | sieve of eratosthenes, extended euclid, smallest prime factor |
| 15 | 2.2 | modular-arithmetic | Fast exponentiation, Fermat's little theorem, modular inverse | 2.1 | modular inverse, binary exponentiation, fermat's little theorem |
| 16 | 2.3 | combinatorics | Counting rules, nCr mod p, stars and bars, inclusion–exclusion | 2.2 | stars and bars, inclusion-exclusion, binomial coefficient |
| 17 | 2.4 | expected-value | Linearity of expectation, contribution technique | 2.3 | linearity of expectation, expected value |

### Phase 3: Recursion to dynamic programming (target 1500–1900)
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 18 | 3.1 | backtracking | Recursion, backtracking, pruning | 0.5 | backtracking, pruning |
| 19 | 3.2 | dp-foundations | DP foundations: state, transition, base case; memoisation vs tabulation | 3.1 | dynamic programming, memoization, memoisation, tabulation |
| 20 | 3.3 | knapsack | Knapsack family: 0/1, unbounded, bounded | 3.2 | knapsack |
| 21 | 3.4 | sequence-dp | LIS in O(n log n), LCS, edit distance | 3.2, 1.4 | longest increasing subsequence, longest common subsequence, edit distance |
| 22 | 3.5 | counting-dp | Grid and counting DP modulo a prime | 3.2, 2.2 | counting dp, grid dp |
| 23 | 3.6 | interval-dp | Interval DP | 3.2 | interval dp |
| 24 | 3.7 | bitmask-dp | Bitmask DP | 3.2, 1.7 | bitmask dp |
| 25 | 3.8 | digit-dp | Digit DP | 3.2 | digit dp |

### Phase 4: Graphs (target 1600–2000)
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 26 | 4.1 | graph-traversal | Representation, BFS, DFS, components, grids as graphs | 0.6 | breadth-first search, depth-first search, adjacency list |
| 27 | 4.2 | graph-structure | Bipartiteness, cycle detection, topological sort | 4.1 | topological sort, bipartite |
| 28 | 4.3 | shortest-paths | Dijkstra, 0-1 BFS, Bellman–Ford, Floyd–Warshall | 4.1 | dijkstra, bellman-ford, floyd-warshall, 0-1 bfs |
| 29 | 4.4 | dsu-mst | DSU and MST: Kruskal, Prim, cut property | 4.1, 1.1 | disjoint set union, union-find, kruskal, prim's algorithm, minimum spanning tree |
| 30 | 4.5 | trees | Tree properties, subtree sizes, diameter, centre, Euler tour | 4.1 | tree diameter, euler tour, subtree size |
| 31 | 4.6 | lca | LCA via binary lifting | 4.5 | lowest common ancestor, binary lifting |
| 32 | 4.7 | connectivity | SCC, bridges, articulation points | 4.2 | strongly connected component, articulation point, tarjan, kosaraju |

### Phase 5: Range data structures (target 1800–2100)
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 33 | 5.1 | sparse-table | Sparse table and RMQ | 1.2, 1.7 | sparse table, range minimum query |
| 34 | 5.2 | fenwick | Fenwick tree (BIT), inversion counting | 1.2, 1.7 | fenwick tree, binary indexed tree |
| 35 | 5.3 | segment-tree | Segment tree, lazy propagation | 5.2 | segment tree, lazy propagation |
| 36 | 5.4 | sqrt-decomposition | Square-root decomposition, Mo's algorithm | 1.1, 1.2 | sqrt decomposition, square-root decomposition, mo's algorithm |

### Phase 6: Strings (target 1900–2200)
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 37 | 6.1 | string-hashing | Polynomial hashing | 2.2 | polynomial hash, rolling hash |
| 38 | 6.2 | prefix-function | Prefix function (KMP) and Z-function | 0.x | prefix function, knuth-morris-pratt, z-function |
| 39 | 6.3 | trie | Trie, binary trie for max-XOR | 1.7 | trie, binary trie |
| 40 | 6.4 | suffix-array | Suffix array and LCP array | 1.1, 6.2 | suffix array, lcp array |

### Phase 7: Integration (target 2000–2400)
Each Phase 7 lesson opens with "This topic combines X and Y." linking both.
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 41 | 7.1 | tree-dp | DP on trees, rerooting | 3.2, 4.5 | tree dp, rerooting |
| 42 | 7.2 | dag-dp | DP on DAGs | 3.2, 4.2 | dp on dag |
| 43 | 7.3 | dp-with-ds | DP sped up with Fenwick or segment trees | 3.4, 5.2, 5.3 | dp optimization with segment tree |
| 44 | 7.4 | greedy-2 | Greedy II: priority-queue greedy, regret greedy | 1.5, 0.6 | regret greedy |
| 45 | 7.5 | game-theory | Sprague–Grundy theorem | 3.2, 1.7 | sprague-grundy, grundy number, nim |
| 46 | 7.6 | matrix-exponentiation | Matrix exponentiation for linear recurrences | 2.2, 3.2 | matrix exponentiation |
| 47 | 7.7 | constructive | Constructive algorithms | Phases 0–2 | constructive |
| 48 | 7.8 | recognition | Technique recognition: mixed sets, topic not given | all | (none) |

Notes:
- "requires" lists the topics a lesson leans on most; any earlier topic may be used. In `curriculum.yaml`, write `requires` as explicit topic ids only. Expand the shorthands in the tables above (`0.x`, `Phases 0–2`, `all`) into the actual list when you do Step 1 of the pipeline for that topic, and keep the table in this file unchanged. The lesson's `uses` list (Section 5) must contain every id in `requires`.
- Dijkstra and MST are taught as graph topics with graph proofs (relaxation invariant, cut property), not as "greedy on graphs". Greedy lessons never use graph problems.
- Topic 7.8 has no new technique: its lesson is a guide to the recognition procedure, a recap of the Recognition Handbook, and mixed sets. It keeps the lesson template, with Sections 4, 6, and 7 replaced by that recap.

---

## 5. Topic data file: schema

Each topic has `src/data/topics/{id-with-dash}.yaml`. The lesson MDX holds prose; this file holds everything structured, which components render. Define the Zod schema in `src/content.config.ts` to match exactly.

```yaml
id: "1.3"

uses:                             # every earlier topic this lesson relies on; rendered by BOTH the page header ("Builds on") and "What you need"
  - {topic: "1.1", what: "Sorting, only to explain why order matters in the stretch problems"}
  - {topic: "1.2", what: "Prefix sums, used as the brute-force baseline and as a look-alike"}
  # must include every id in this topic's `requires` (curriculum.yaml) and every earlier topic cited anywhere in the lesson or this file

theorems:                         # one entry per numbered theorem in Section 4 of the lesson
  - id: "1.3.1"
    title: "Shrinking a valid window keeps it valid"
    plain_words: "If a segment is allowed, every smaller piece cut from its ends is allowed too."
    demo: "1.3/thm-1"             # code unit folder under code/ (Section 8.6)

cards:
  - id: shrinkable-window
    name: "Shrinkable window"
    decisive_property: "If a window [l, r] is valid, every window inside it is valid (validity is closed under shrinking)."
    from_theorem: "1.3.1"
    how_to_test: "Take any valid window, remove its first element, and argue it stays valid for every possible input."
    constraint_shapes:            # 1–3; each pairs a concrete bound with what it forces
      - "n up to 2·10^5 with one array: O(n²) is about 2·10^10 pair checks, so the answer must come from one or two passes"
    weak_signals:                 # 2–4; each is a question form AND a typical constraint/statement shape, never just "there is an array"
      - form: "Asks for the longest or shortest contiguous segment satisfying a condition"
        shape: "One array or string, n ≥ 10^5, condition mentions only the segment's own contents (sum, count of distinct values, max − min)"
      - form: "Asks to count segments satisfying a condition"
        shape: "Same shape as above; the count is usually up to n(n+1)/2, so it needs a 64-bit integer"
    kill_signals:
      - "Sum condition with possibly negative values: for [5, -4, 1] and sum ≤ 2, the segment [5] is invalid but extending it to [5, -4, 1] (sum 2) is valid, so an invalid window can become valid by growing"
      - "Asks about subsequences, not contiguous segments"
    in_action:                    # one complete recognition, using the three layers; invented problem, numbers must be real
      statement: "Given n positive integers and K, find the length of the longest contiguous segment whose sum is at most K."
      constraints: "n ≤ 2·10^5, 1 ≤ a_i ≤ 10^9, K ≤ 10^14"
      budget: "All segments: n(n+1)/2 ≈ 2·10^10 sums even with prefix sums. At about 10^8 simple operations per second that is over 200 seconds. Need about O(n)."
      candidates:                 # at least two, all from allowed (earlier) topics
        - {tool: "Check every segment using prefix sums (1.2)", verdict: rejected, because: "About 2·10^10 checks: too slow."}
        - {tool: "Shrinkable window (this topic)", verdict: chosen, because: "Property holds, see below."}
      property_check: "Take a valid window and delete its first element. All values are positive, so the sum drops. It is still at most K. Closed under shrinking: yes."
      decision: "Shrinkable window, O(n)."
    examples:                     # at least 2 positive and 2 negative; at least one of each kind is inline with real numbers
      positive:
        - inline: {input: "a = [2, 1, 3, 1, 1], K = 4", answer: "2", why: "All values positive, so deleting an end element only lowers the sum. The window method gives 2, matching brute force."}
        - worked_example: cf-1234A      # a worked-example problem of THIS topic only (never ladder, drill, checkpoint, review or exam problems)
          why: "At most k distinct values: removing an element never adds a distinct value."
      negative:
        - inline: {input: "a = [5, -4, 1], K = 2", answer: "3 (the whole array sums to 2)", method_gives: "2", why: "Trace: at r = 0 the window [5] has sum 5 > 2, so the method discards 5 for good. It ends with best length 2 (the window [-4, 1]). But the whole array [5, -4, 1] has sum 2, so the true answer is 3. The method assumes a window that is invalid now can never become valid by growing; negative values break that."}
          correct_tool: {topic: "1.2", card: prefix-sum-lookup}
        - problem: cf-7777D                # a problem from THIS or an EARLIER topic (a problem the learner has solved or will see in an earlier ladder); not this topic's ladder/drill
          why: "Asks for subsequences, not segments; the window idea does not apply."
          correct_tool: {topic: "0.5", card: subset-enumeration}
    lookalikes:                   # structured references only; topics must be this topic or earlier (Section 12)
      - description: "Longest subarray with sum at most K when values can be negative"
        tool: {topic: "1.2", card: prefix-sum-lookup}
        flipping_difference: "Negative values break closure under shrinking."
    complexity: "O(n): each pointer moves right at most n times in total."

problems:
  - id: cf-1234A                  # formats in Section 9.1
    role: ladder                  # ladder | worked_example | drill | lookalike | checkpoint | review | exam
    source: codeforces            # codeforces | atcoder | cses | leetcode
    title: "Exact Title As Shown On The Page"
    url: "https://codeforces.com/problemset/problem/1234/A"
    difficulty: "1400"            # Codeforces rating; AtCoder Problems difficulty; LeetCode Easy/Medium/Hard; "—" for CSES
    card: shrinkable-window       # ladder, checkpoint, review: required; others: optional
    rung: 3                       # ladder only, from 1 within its card
    twist: "Condition is 'at most k distinct values' instead of 'sum at most K'."   # ladder only
    summary: "Longest contiguous segment with at most k distinct values."            # own words, one line
    hints:                        # ladder only; exactly 3
      - "What happens to the count of distinct values when the window grows? When it shrinks?"
      - "Validity is closed under shrinking: every sub-window of a valid window is valid."
      - "Advance the right end; while invalid, advance the left end; track the best length."
    editorial_url: null           # only a URL you saw linked from the problem or contest page
    techniques: ["1.3", "0.6"]    # topic ids the solution note uses
    review_set: null              # review only: 1, 2, or 3
    checked_on: "2026-10-12"      # date you opened the page and confirmed the title

drill:                            # 8–12 items; each references a problem with role drill
  - problem: cf-2222B
    answer: {topic: "1.2", card: prefix-sum-lookup}   # this topic or an earlier one
    property: "Exact-sum condition: count pairs of equal prefix values (mod / difference)."
    why_others_fail: "Two pointers: values can be negative, so validity is not closed under shrinking."

lookalike_pairs:                  # 2–4; both tools must belong to this topic or earlier ones
  - a: cf-3333C
    b: cf-4444D
    a_tool: {topic: "1.3", card: shrinkable-window}
    b_tool: {topic: "1.2", card: prefix-sum-lookup}
    shared_surface: "Both ask for a subarray with a sum condition on one array of about 2·10^5 numbers."
    flipping_difference: "B allows negative values, so removing an end element can raise the sum."
    flipping_input: "a = [5, -4, 1], K = 2: the window method answers 2, the true answer is 3."

self_test:                        # 5–8
  - q: "Give a length-3 array with a negative value where the shrinking-window method returns the wrong answer for 'longest subarray with sum ≤ 2'."
    a: "…"

checkpoint:
  time_limit_minutes: 90
  problems: [cf-5555B, ac-abc300_d, cf-6666C]   # exactly 3, role checkpoint

decision_map:                     # how this topic's cards are chosen vs earlier cards
  - weak_signal: "Longest/shortest contiguous segment with a condition"
    choose: shrinkable-window
    when: "Validity is closed under shrinking."
    over:
      - card: prefix-sum-lookup
        because: "Prefix lookup is needed only when the condition is an exact sum or values can be negative."

glossary_added: ["window", "pointer"]   # terms first defined in this topic (entries live in glossary.yaml)
```

### 5.1 Glossary file: `src/data/glossary.yaml`
```yaml
- term: "GCD"
  expansion: "greatest common divisor"   # abbreviations only
  definition: "The largest positive integer dividing both numbers."
  topic: "0.4"
```

---

## 6. Lesson page: exact template and section rules

Lesson file: `src/content/docs/phase-{n}/{id-dash}-{slug}.mdx`.

```mdx
---
title: "1.3 Two pointers and sliding window"
sidebar:
  order: 9
topic: "1.3"
---
import { Code } from '@astrojs/starlight/components';
import TopicHeader from '../../../components/TopicHeader.astro';
import Cards from '../../../components/Cards.astro';
import Ladder from '../../../components/Ladder.tsx';
import Drill from '../../../components/Drill.tsx';
import LookalikePairs from '../../../components/LookalikePairs.astro';
import SelfTest from '../../../components/SelfTest.astro';
import Checkpoint from '../../../components/Checkpoint.tsx';
import DecisionMapUpdate from '../../../components/DecisionMapUpdate.astro';
import WhatYouNeed from '../../../components/WhatYouNeed.astro';
import TheoremDemo from '../../../components/TheoremDemo.astro';
import windowSum from '../../../../code/1.3/window-sum/solution.cpp?raw';

<TopicHeader topic="1.3" />

## 1. Why this topic exists
## 2. Prerequisites and scope
### What you need
<WhatYouNeed topic="1.3" />
### What this topic does not cover
## 3. Definitions
## 4. Theory and proofs
<TheoremDemo unit="1.3/thm-1" />
## 5. Recognition Cards
<Cards topic="1.3" />
## 6. Templates
<Code code={windowSum} lang="cpp" title="window-sum/solution.cpp" />
## 7. Bug catalogue
## 8. Worked examples
## 9. Problem ladder
<Ladder topic="1.3" client:load />
## 10. Identification drill
<Drill topic="1.3" client:load />
## 11. Look-alike pairs
<LookalikePairs topic="1.3" />
## 12. Self-test questions
<SelfTest topic="1.3" />
## 13. Checkpoint
<Checkpoint topic="1.3" client:load />
## 14. Decision map update
<DecisionMapUpdate topic="1.3" />
```
(Adjust relative import depth to the actual folder depth. The headings above are required, with this exact text and order.)

### 6.1 Section 1: Why this topic exists
- A small problem you write yourself where brute force is too slow.
- Its brute-force complexity computed against the budget (e.g., "n = 2·10⁵, O(n²) ≈ 4·10¹⁰ operations, about 400 seconds at 10⁸ per second").
- One paragraph with the key idea in plain words. No code yet.

### 6.2 Section 2: Prerequisites and scope
- `### What you need`: rendered by `<WhatYouNeed topic="…" />` from the `uses` list in the topic data file (Section 5). Do not hand-write this list. `<TopicHeader>` shows the same `uses` list under "Builds on", so the two can never disagree. Each entry is a link to the earlier lesson plus its one-line `what`.
- `### What this topic does not cover`: nearby ideas from later topics, each with "covered in topic X.Y". The only place later-topic keywords may appear.

### 6.3 Section 3: Definitions
Each new term in bold at its definition, a precise definition, and a tiny example. Add it to `glossary.yaml` and `glossary_added`.

### 6.4 Section 4: Theory and proofs
Every theorem is numbered `Theorem {topic}.{n}`, has an entry in the data file's `theorems` list (Section 5), and uses exactly this layout, in this order:

1. **Statement** in precise mathematical words, with LaTeX math (`$…$`, `$$…$$`).
2. **In plain words:** one or two sentences with no symbols a beginner has not met, rendered as `:::tip[In plain words]`. Copy of `plain_words` from the data file.
3. **A tiny instance with real numbers** (an array or graph of 3–6 elements) showing the statement true on one case, before any proof. Use a table or a one-line trace.
4. **Proof,** as numbered steps. Each step is one claim plus its reason, at most two lines. At most 8 steps; a longer argument is split into named lemmas, each laid out the same way. No step may use a fact that is not (a) a definition on this page, (b) an earlier numbered step, or (c) a cited earlier theorem with its number. The proof's last line says which statement of the theorem has now been shown.
5. **Preconditions box,** exactly:
   ```mdx
   :::note[This proof needs]
   1. …
   2. …
   :::
   ```
6. **Demo:** `<TheoremDemo unit="{topic}/thm-{n}" />` shows a small tested program and its real output (Section 8.6). The demo runs the theorem's claim on the tiny instance from item 3 or a close variant, so the reader sees the numbers the proof talks about.
7. **Complexity** (for algorithm theorems) with the reason, in one or two lines.

Rules for proofs a beginner must be able to follow:
- Every symbol is defined in Section 3 or in the statement. A proof about "windows $[l, r]$" says what $l$ and $r$ index.
- Prefer a concrete argument on the tiny instance followed by "the same argument works for any input because…" over a purely abstract chain. Never leave "similarly" or "by induction" without writing the base case and the step.
- If a proof has a case split, list the cases first ("Case A: …; Case B: …"), then argue each under its own sub-heading.
- Reading test (part of Section 17.1): read each proof imagining only Phase 0 knowledge plus this page. Any step that needs a pause gets split into two steps.
- Prefer a concrete trace (a table of pointer positions or DP values on a small input) alongside abstract arguments.

### 6.5 Section 5: Recognition Cards
3–6 cards, rendered by `<Cards>` from the data file. Each card is shown in this order, with these labels:

1. **Name** and **Decisive property**, which restates the preconditions box of the theorem in `from_theorem`, in problem language.
2. **How to test it:** the one check to run on a problem (`how_to_test`).
3. **Constraint shapes:** what the input sizes force (`constraint_shapes`), always with the actual arithmetic (e.g., "2·10^5 elements, so n² ≈ 4·10^10").
4. **Weak signals:** each is a pair of *question form* and *statement/constraint shape* (`weak_signals`). "There is an array" or "the problem mentions a sum" alone is never a weak signal. These only raise the card as a candidate; they never decide.
5. **Kill signals:** facts that rule the card out immediately, each with a concrete instance whenever the kill depends on numbers (`kill_signals`).
6. **Recognition in action:** the card's `in_action` block, rendered as the three-layer procedure on one problem: statement → constraints → budget → candidates (≥ 2, each accepted or rejected with a reason) → property check → decision. Same shape as worked-example Steps 1–3 (Section 6.8) but short, about 10 lines. It is a different problem from the worked examples, so the reader sees a fresh recognition.
7. **Examples:** `examples.positive` (the property holds) and `examples.negative` (it looks like this card but the property fails, with the correct tool named).
8. **Look-alikes:** the card's `lookalikes`, each showing the other card's *name*, never a slug, and the flipping difference.
9. **Complexity.**

Rules for examples:
- At least 2 positive and 2 negative per card. At least one positive and one negative must be `inline`: a tiny invented instance with concrete numbers, the answer, and (for negatives) what the wrong method outputs. These numbers must be produced by a code unit (Section 8.6), not by hand.
- Positive examples may reference only (a) inline instances, (b) this topic's `worked_example` problems, or (c) problems from earlier topics. They never reference this topic's ladder, drill, checkpoint, review or exam problems, so no later exercise is spoiled.
- Every negative example names a `correct_tool`: a `{topic, card}` of this or an earlier topic. If the right tool is only taught later, the negative is instead written as "a problem where no tool from this course applies yet" and is not used.
- Each example's `why` is one to three sentences that point to the decisive property (holds / fails because …), never just "it works".
- Every negative example that depends on numbers (like the `[5, -4, 1]` case) must also appear in the topic's bug catalogue or self-test, so the failing input is exercised in code.

### 6.6 Section 6: Templates
For each template:
- A level-3 heading, then `<Code>` with the imported tested file.
- **How it works:** a walk-through referring to variable names.
- **C++ details explained:** every macro, lambda, reference parameter, `auto`, structured binding, STL call, or other non-obvious construct, in plain words. If none: "None beyond earlier topics."
- **Tested:** e.g., "Stress-tested against brute force on 5000 random inputs (n ≤ 8)."
- **Alternative formulation** (when one exists): a correct variant with its proof (see Section 8.5).

### 6.7 Section 7: Bug catalogue
4–8 bugs. Each `### Bug: {short name}` contains: the wrong line, a small failing input found by the stress script, wrong vs correct output, and the fix with one sentence on why. Produce each by actually breaking a copy of the template and running `stress.sh` (Section 8.5).

### 6.8 Section 8: Worked examples
2–3 examples, each `### Example {n}: {Exact Title}` with the problem link, then these level-4 headings exactly:
1. `#### Step 1: Constraints → budget`
2. `#### Step 2: Question form → candidate tools` (at least two candidates from allowed topics)
3. `#### Step 3: Property check → decision` (why each rejected candidate fails)
4. `#### Step 4: Proof for this problem`
5. `#### Step 5: Code` (a tested code unit in `code/{topic}/example-{n}/`, shown with `<Code>`)
6. `#### Step 6: Alternative approach` (another allowed solution, or one sentence on why there's no natural one)

Worked-example problems are recorded with role `worked_example`. Since their code is shown in full, these are the only problems with code; test them on the samples from the problem page, written by hand into `tests/`, plus a stress test when a brute force is feasible.

### 6.9 Section 9: Problem ladder
12–20 problems with role `ladder`, grouped by card (≥ 3 per card), ordered by rung. Difficulty bands within a ladder:
- first ~30% warm-up (CSES, LeetCode, or about 300 below the phase band);
- middle ~50% within the phase band, or AtCoder ABC (AtCoder Beginner Contest) C–E;
- last ~20% stretch, 200–300 above the phase band's lower bound.
Difficulty must not decrease within a card group for problems from the same platform. Each rung's `twist` names the one new idea over the previous rung (first rung: "Base case of the card").

### 6.10 Section 10: Identification drill
8–12 items, at least 3 answered by an earlier topic's card. The summary must include the constraints that matter for recognition.

### 6.11 Section 11: Look-alike pairs
2–4 pairs; at least one side of each uses this topic's tool. Both tools in a pair, and anything in `needs` or `flipping_difference`, must belong to this topic or an earlier one: a look-alike whose other side is taught later is written in the later topic's lesson, where it is allowed. Tools are `{topic, card}` references and render as card names with a link (e.g., "Prefix-sum lookup (topic 1.2)"), never as the internal card id. Each pair shows both problem summaries, the `shared_surface` (what makes them look alike), the `flipping_difference`, and, when the difference depends on numbers, the `flipping_input` with each method's output.

### 6.12 Section 12: Self-test questions
5–8 conceptual questions answerable without code, with concrete counterexamples where relevant.

### 6.13 Section 13: Checkpoint
Exactly 3 problems near the phase band. Time limits: Phases 0–1: 90 minutes; Phases 2–4: 120; Phases 5–7: 150. Pass rule: solve at least 2 of 3 in time, and name the right property on at least 8 drill items.

### 6.14 Section 14: Decision map update
Rendered from `decision_map`. Add entries to every weak-signal group this topic touches, including groups created by earlier topics.

---

## 7. Writing rules

- Plain English, short sentences, active voice.
- Define every term before its first use on the page. Terms from earlier lessons: link the lesson the first time on each page.
- Expand every abbreviation at its first occurrence on each page, as "breadth-first search (BFS)" or "BFS (breadth-first search)". Avoid unexpanded abbreviations in headings.
- Never write "obviously", "clearly", "trivially", "it's easy to see", or "simply" in place of an argument.
- Every correctness claim is proved here or cited to a numbered theorem in an earlier lesson. Every complexity claim includes its reason. Counterexamples use actual numbers.
- Every mechanism described in prose also appears in code in the same lesson. Every theorem has a demo (Section 6.4, 8.6) and every card has examples (Section 6.5).
- Introduce a symbol, a technical word, or a C++ construct before using it. If a sentence needs a term from a later part of the page, move the definition up or rewrite the sentence.
- Cross-references to other topics appear only as links to **earlier** lessons (or inside "What this topic does not cover"). Never show an internal id such as a card slug or a file name to the reader; show the card's or lesson's title.
- Copyright: no copied statements or editorials; summaries are one line in your own words; never quote more than a few words from any source.

---

## 8. Lesson code and testing

### 8.1 Compiler and style
- C++17; compile with `g++ -std=c++17 -O2 -Wall -Wextra -Werror`.
- `#include <bits/stdc++.h>` and `using namespace std;` allowed; Topic 0.1 explains both.
- 4-space indentation, braces on the same line, descriptive names (conventional `n`, `m`, `k`, `l`, `r`, loop indices allowed).
- `long long` wherever values can exceed about 2·10⁹, with a comment saying why.
- No CP macros in templates. A macro used anywhere must have been explained in an earlier lesson.
- Problem statements written as code comments use a multi-line block without a leading asterisk on each line:
  ```cpp
  /*
  Problem: longest contiguous segment with sum at most K.
  Input: n K, then n positive integers.
  Output: the maximum length.
  */
  ```

### 8.2 Code units
A code unit is a folder in `code/{topic}/` containing:
- `solution.cpp`: complete program, standard input to standard output.
- `tests/k.in` and `tests/k.out`: at least 3 pairs for template and worked-example units, including edge cases (smallest n, all equal values, maximum values for overflow). Theorem demo units and card example units (Section 8.6) need at least 1 pair. Expected outputs come from `brute.cpp` or careful hand calculation, never from `solution.cpp` alone.
- For templates, also `brute.cpp` (slow, obviously correct) and `gen.cpp` (random small inputs, seed from `argv[1]`).

Generator skeleton (the `argc` check is required, or `-Werror` rejects the unused parameter):
```cpp
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    // random integer in [lo, hi]
    auto randInt = [&](int lo, int hi) {
        return (int)(rng() % (unsigned)(hi - lo + 1)) + lo;
    };
    int n = randInt(1, 8);
    // ... print a random small input, sometimes forcing edge cases
}
```

### 8.3 `scripts/stress.sh` (use exactly; tested)
```bash
#!/usr/bin/env bash
set -euo pipefail
DIR="${1:?usage: stress.sh <code-dir> [iterations]}"
N="${2:-2000}"
BUILD="$DIR/.build"
mkdir -p "$BUILD"
for f in solution brute gen; do
  g++ -std=c++17 -O2 -Wall -Wextra -Werror -o "$BUILD/$f" "$DIR/$f.cpp"
done
for ((i = 1; i <= N; i++)); do
  "$BUILD/gen" "$i" > "$BUILD/in.txt"
  "$BUILD/solution" < "$BUILD/in.txt" > "$BUILD/out_solution.txt"
  "$BUILD/brute"    < "$BUILD/in.txt" > "$BUILD/out_brute.txt"
  if ! cmp -s "$BUILD/out_solution.txt" "$BUILD/out_brute.txt"; then
    echo "MISMATCH on seed $i"
    echo "--- input ---";    cat "$BUILD/in.txt"
    echo "--- solution ---"; cat "$BUILD/out_solution.txt"
    echo "--- brute ---";    cat "$BUILD/out_brute.txt"
    exit 1
  fi
done
echo "OK: $N random cases matched"
```

### 8.4 `scripts/test_units.sh` (use exactly; tested)
Compiles every unit, checks its fixed tests, and stress-tests every unit that has `brute.cpp` and `gen.cpp` with 5000 cases.
```bash
#!/usr/bin/env bash
set -euo pipefail
ROOT="${1:-code}"
fail=0
while IFS= read -r unit; do
  mkdir -p "$unit/.build"
  g++ -std=c++17 -O2 -Wall -Wextra -Werror -o "$unit/.build/solution" "$unit/solution.cpp"
  for in_file in "$unit"/tests/*.in; do
    [ -e "$in_file" ] || continue
    expected="${in_file%.in}.out"
    actual="$unit/.build/actual.out"
    "$unit/.build/solution" < "$in_file" > "$actual"
    if ! diff -q -Z "$actual" "$expected" > /dev/null; then
      echo "FAIL: $in_file"; fail=1
    fi
  done
  if [ -f "$unit/brute.cpp" ] && [ -f "$unit/gen.cpp" ]; then
    bash "$(dirname "$0")/stress.sh" "$unit" 5000 > /dev/null || { echo "STRESS FAIL: $unit"; fail=1; }
  fi
done < <(find "$ROOT" -name solution.cpp -exec dirname {} \; | sort)
[ "$fail" -eq 0 ] && echo "All code units passed" || exit 1
```
Add `**/.build/` to `.gitignore`. If a problem allows several correct outputs, write a `checker.cpp` for that unit and document how to run it in the unit folder.

### 8.5 Rules for stress testing
- Templates must pass 5000 iterations. Never lower the count to make a test pass.
- Inputs small enough for brute force (typically n ≤ 8–10, values ≤ 10–20), with forced edge cases (n = 1, all equal values, values at the condition's boundary).
- **If a deliberately introduced bug passes the stress test, investigate before discarding it.** Either the generator is too weak (strengthen it and rerun) or the variant is actually correct, in which case it becomes an "Alternative formulation" with a proof. (Real example found while testing this plan: in the longest-window-with-sum-at-most-K template, replacing the inner `while` with `if` still returns the correct maximum length, because the window then never shrinks below the best length found so far. That is the known "non-shrinking window" variant.)

### 8.6 Theorem demos and card example units

Both kinds are ordinary code units (a folder with `solution.cpp` and `tests/`), so `test_units.sh` already compiles and checks them. They differ only in what they are for.

**Theorem demo** (`code/{topic}/thm-{n}/`), one per numbered theorem:
- `solution.cpp` is **5–30 lines** in total and written for reading, not speed. It runs the theorem's claim on a fixed tiny input, and prints the quantities the theorem is about, one labelled line per step (for example, for window validity: the window, its sum, and "valid" or "invalid" after each removal).
- Where the theorem says "for every", the program checks the claim over all small inputs it can enumerate (e.g., every window of the tiny array) and prints one summary line ("all 6 windows: closed under shrinking: yes").
- `tests/1.in` is the tiny input (may be empty) and `tests/1.out` the expected output, **calculated by hand from the proof first** and then compared with the program's output. If they disagree, one of them is wrong: investigate, never copy the program's output into the test.
- It uses only constructs explained in earlier lessons; any new construct is explained under the demo.
- Shown in the lesson by `<TheoremDemo unit="{topic}/thm-{n}" />`: the component loads `solution.cpp` and `tests/1.out` with `import.meta.glob('/code/**/{solution.cpp,tests/1.out}', { query: '?raw', eager: true })` and displays the code, then a block titled "Output". The output shown is therefore always the tested expected output.
- After the output, 1–3 sentences connect the printed lines to the proof's steps ("line 3 is step 2 of the proof").

**Card example unit** (`code/{topic}/card-{card-id}/`), one per card that has `inline` examples:
- `solution.cpp` computes, for every inline example of that card, the correct answer by brute force and the answer of the card's method (and, for negatives, shows that they differ), and prints them in the order the examples appear in the data file, e.g. `N1 brute=3 method=2`.
- `tests/1.out` contains those lines. The numbers in the card's `inline.answer` and `method_gives` fields must equal them; build-time validation (Section 12, item 12) parses the `tests/1.out` lines and compares.
- It is allowed to be longer than a theorem demo (no display limit) because it is not shown, only run.

**Which program a learner sees:** the Theorem demo only. Card example units are checks behind the scenes. In the lesson, an inline example shows the input, the answers, and the `why` text.

---

## 9. Problem selection and link checking

### 9.1 Id and URL formats
| Source | Id | URL |
|---|---|---|
| Codeforces | `cf-{contestId}{index}`, e.g. `cf-1234A`, `cf-1520B1` | `https://codeforces.com/problemset/problem/{contestId}/{index}` |
| AtCoder | `ac-{task_id}`, e.g. `ac-abc300_c` | `https://atcoder.jp/contests/{contest_id}/tasks/{task_id}` |
| CSES | `cses-{number}`, e.g. `cses-1640` | `https://cses.fi/problemset/task/{number}` |
| LeetCode | `lc-{title-slug}`, e.g. `lc-two-sum` | `https://leetcode.com/problems/{title-slug}/` |

Do not use Codeforces EDU or Gym problems (they need a login) or LeetCode premium problems.

### 9.2 Where to look
Site tags and categories only help you find candidates; they are never evidence of purity.

| Phase | Warm-up | Core | Stretch |
|---|---|---|---|
| 0 | CSES Introductory Problems; LeetCode Easy | AtCoder ABC A–C | Codeforces Div. 3/4 A–C (≤ 1100) |
| 1 | CSES Sorting and Searching; LeetCode Easy/Medium | AtCoder ABC C–D; Codeforces 1000–1400 | Codeforces 1400–1700 |
| 2 | CSES Mathematics | AtCoder ABC C–E; Codeforces 1400–1700 | Codeforces 1700–2000 |
| 3 | CSES Dynamic Programming; AtCoder Educational DP Contest early tasks; LeetCode Medium | AtCoder ABC D–E; Codeforces 1500–1900 | Codeforces 1900–2200 |
| 4 | CSES Graph Algorithms, Tree Algorithms | AtCoder ABC D–E; Codeforces 1600–2000 | Codeforces 2000–2300 |
| 5 | CSES Range Queries | AtCoder ABC E–F; Codeforces 1800–2100 | Codeforces 2100–2400 |
| 6 | CSES String Algorithms | AtCoder ABC E–F; Codeforces 1900–2200 | Codeforces 2200–2500 |
| 7 | AtCoder Educational DP Contest later tasks; CSES Tree Algorithms | AtCoder ABC E–G; Codeforces 2000–2400 | Codeforces 2400–2600 |

Prefer well-known problems with many solves. Gather about twice as many candidates as you need and keep the cleanest.

### 9.3 Link checking (manual, for every problem)
1. Open the URL with your web or fetch tool.
2. Confirm the page title matches exactly; copy it into `title`.
3. Take difficulty from the source: Codeforces shows the rating as a `*1400`-style tag on the problem page; for AtCoder, use the AtCoder Problems difficulty (you may fetch `https://kenkoooo.com/atcoder/resources/problem-models.json` once per session as a one-off command; do not commit it); LeetCode shows Easy/Medium/Hard; CSES has none (`"—"`).
4. Read the full statement and constraints.
5. Set `checked_on` to today.
If a page can't be opened after three tries spread over a few minutes, drop the problem and note it under "Blocked" in `PROGRESS.md`. Never fill any field from memory.

### 9.4 Solution notes (`notes/{topic}.md`, not rendered)
For every problem in the topic, before adding it to the data file:
```markdown
## cf-1234A Exact Title (role: ladder, card: shrinkable-window, rung 3)
- Budget: n ≤ 2·10^5 → O(n log n) or better.
- Idea: (2–5 lines: the full solution, precise enough to implement)
- Techniques: 1.3, 0.6
- Why this card: (one line)
- Twist vs previous rung: (one line)
```
And at the end of the file, a `## Dropped candidates` list: id, title, reason (e.g., "needs binary search, topic 1.4, later").

Purity rule: if `Techniques` contains anything later than the current topic, drop the problem. If the most natural solution uses a later technique but a natural allowed solution exists, you may keep it and say in Hint 1 that the later technique isn't needed.

---

## 10. Site features

All learner data stays in the browser. Use a single module `src/lib/storage.ts` with versioned keys:

| Key | Contents |
|---|---|
| `cp:v1:problems` | `{ [problemId]: { status, hintsOpened, minutes, mistake, budget, candidates, property, date, note } }` |
| `cp:v1:topics` | `{ [topicId]: { started, checkpointPassedOn } }` |
| `cp:v1:drills` | `{ [problemId]: { chosenCard, property, revealed } }` |
| `cp:v1:contests` | `[ { date, platform, name, solved, upsolved: [ids], note } ]` |
| `cp:v1:settings` | `{ currentTopic }` |

Wrap every read and write in try/catch; the site must render correctly when storage is empty.

### 10.1 Dashboard (home page)
- **Current topic** with progress (ladder problems solved / total).
- **Due today:** review sets due (Section 10.4) and re-solves due (Section 10.5), each linking to the problem.
- **Mistake summary:** counts by mistake category for the last 30 days, and the three cards with the most Recognition misses.
- **Next step:** one line, e.g., "Finish rung 4 of Shrinkable window" or "Take the 1.3 checkpoint".

### 10.2 Ladder component
For each problem: title, platform badge, difficulty, twist, summary, link (opens in a new tab), and:
- three hint buttons revealed one at a time, each showing a reminder of the struggle budget before revealing; the number opened is recorded;
- a **log panel**: before marking as attempted, fields for budget, candidate tools, and property verified (encouraged, not forced), then status (Attempted / Solved / Solved with hints / Read editorial), minutes spent, mistake category (Recognition miss, Property error, Implementation bug, Edge case, Complexity misjudgement), and a free-text note.
- Status colours on each row; a progress bar per card group.

### 10.3 Drill component
For each item: summary and link; a dropdown of tool cards learned so far (all cards from topics with `order` ≤ current page's topic); a text box for the verified property; a Reveal button showing answer card, property, and why other tools fail. The chosen card is marked right or wrong after reveal. Results are saved.

### 10.4 Checkpoint and spaced reviews
- Checkpoint component: the 3 problems with a start button and a countdown timer of the topic's time limit; after time ends, a form to mark each solved/unsolved. If the pass rule is met (Section 6.13; drill results come from storage), record `checkpointPassedOn`.
- Review schedule: review set 1 due 3 days after `checkpointPassedOn`, set 2 after 14 days, set 3 after 60 days. Review pages show problems with summary and link plus the three-line pre-coding fields; answers (tool and property) behind a reveal; no hints.

### 10.5 Re-solve list
Any problem logged as "Solved with hints" with hint 2 or 3 opened, or "Read editorial", is due for a re-solve 7 days later. The dashboard lists it until it's logged as Solved without hints.

### 10.6 Progress page (`/progress`)
- Export all `cp:v1:*` data as a downloaded JSON file; import from a JSON file (validate, then replace). This is how Saurabh moves progress between his phone and laptop.
- **Feedback export:** a button that builds a Markdown snippet in the `FEEDBACK.md` format (Section 16.3) from logged mistakes grouped by card and topic, and copies it to the clipboard.
- Reset button with confirmation.

### 10.7 Navigation
Starlight sidebar: Home, Method, then Phase 0–7 (each phase: intro, lessons in `order`, exam), then Handbook, Glossary, Problems, Contest log, Progress. Topics after the current topic show a "later" badge but remain clickable.

### 10.8 Look and feel
Starlight defaults with small changes: readable prose width, KaTeX styled for both themes, clear platform badges (Codeforces, AtCoder, CSES, LeetCode), mobile-friendly tables (horizontal scroll inside their container). Light and dark themes both checked.

### 10.9 Lesson content components

- `TopicHeader`: title, phase, estimated hours, and "Builds on" from the topic's `uses` list (links with their one-line `what`).
- `WhatYouNeed`: the same `uses` list, rendered as a list for Section 2 of the lesson. Both components import one helper, `getUses(topicId)`, so they cannot diverge.
- `Cards`: renders each card in the order given in Section 6.5, with the labels given there. Examples are shown as small "Works" (positive) and "Does not work" (negative) panels, each with the input, answers, and `why`. The `in_action` block is shown as a short numbered procedure. Card references from `correct_tool` and `lookalikes` are rendered through `cardLabel({topic, card})`, which returns the card's name and a link to its lesson. If the reference cannot be resolved, the build fails (Section 12).
- `TheoremDemo`: Section 8.6.
- `LookalikePairs`: Section 6.11, using `cardLabel` for both tools.
- Add a "Copy" button to every `<Code>` block (HTTPS makes the Clipboard API available, Section 14.2; use the same selectable-text fallback).

---

## 11. Other pages and documents

### 11.1 Method page (`method.mdx`)
1. Why this programme is ordered the way it is (strict dependencies; pure ladders; mixing only in exams and Phase 7).
2. The three-layer recognition procedure: constraints → budget; question form → candidates (weak signals); structural property → decision (strong signal).
3. Per-problem routine: write budget, candidates, property before coding; struggle budget before Hint 1 (20 minutes in Phases 0–1, 30–45 minutes from Phase 2), at least 10 minutes between hints; log the outcome and mistake category.
4. Mistake categories with one example each.
5. Weekly rhythm (~15 hours): 4 days current topic; 1 day reviews and re-solves; 1 day live contest (AtCoder ABC or Codeforces Div. 3/4, from Phase 1) and upsolving; 1 day rest.
6. Upsolving rule: after each contest, solve every missed problem up to 300 rating points above your current rating.
7. Advancement rules for topics and phases.
8. How to send feedback (export button, `FEEDBACK.md`).

### 11.2 Phase intro (`phase-{n}/index.mdx`)
Goal, target rating band, topic list with one-line descriptions, estimated hours, how the exam works.

### 11.3 Phase exam (`phase-{n}/exam.mdx`)
- 6–10 fresh problems (role `exam`, stored in the data file of the phase's last topic) covering every topic in the phase, shuffled, with topics hidden.
- Timer: 3 hours for Phases 0–1; 4 hours for Phases 2–7 (two sittings allowed).
- Remediation map behind a reveal: problem → topic → card → lesson section to reread.
- Pass rule: at least 60% solved in time, with no Recognition misses on solved problems.
- An introduction explaining that this is deliberately mixed, because contests never name the topic.

### 11.4 Generated pages
- **Recognition Handbook** (`/handbook`): (a) by weak signal: every `decision_map` group across all topics, with cards to choose, when, and over which alternatives; (b) by topic: every card in curriculum order. A filter "as of topic X" shows only cards from topics up to X. A flashcard mode: front shows weak signals and a problem summary, back shows card and decisive property.
- **Glossary** (`/glossary`): alphabetical; term, expansion, definition, link to the introducing lesson.
- **Problems** (`/problems`): table of every problem across topics with platform, difficulty, topic, role, card, and the learner's status; filterable and sortable. Checkpoint, review, and exam problems are hidden here until their topic's checkpoint is passed (so they stay unseen).
- **Contest log** (`/contests`): add a contest entry; list upsolve targets.

---

## 12. Build-time validation

Implement in `src/content.config.ts` (Zod schemas) and `src/lib/data.ts` (cross-file checks that throw during `npm run build`). Each failure message names the file and the problem or card id.

1. Every topic YAML matches the schema; required fields present per role.
2. Problem ids are unique across all topics; every id matches its platform format and its URL matches the format in Section 9.1.
3. Counts: cards 3–6; per card: weak signals 2–4 (each with `form` and `shape`), constraint shapes 1–3, kill signals ≥ 1, positive examples ≥ 2, negative examples ≥ 2, at least one `inline` positive and one `inline` negative, `in_action` present with ≥ 2 candidates and exactly one `chosen`; ladder 12–20 with ≥ 3 per card; drill 8–12 with ≥ 3 earlier-topic answers; look-alike pairs 2–4; self-test 5–8; checkpoint exactly 3; each review set 3–4.
4. Every `techniques` entry has `order` ≤ the problem's topic order. For Phase 7 topics, `techniques` includes the combined topics.
5. Every ladder problem's `card` is a card of the same topic; drill `answer` (a `{topic, card}` reference) resolves to a card in the same or an earlier topic.
6. Ladder rungs are 1..k with no gaps per card; difficulty is non-decreasing within each card for problems on the same platform.
7. Every glossary term in `glossary_added` exists in `glossary.yaml` with the same topic.
8. Every lesson MDX has the required headings in order (parse headings from the raw file).
9. **References resolve and respect order.** Every `{topic, card}` reference (in `answer`, `a_tool`, `b_tool`, `correct_tool`, `lookalikes[].tool`, `decision_map`) points to an existing card whose topic has `order` ≤ the current topic's `order`. Free-text fields `needs` and `flipping_difference` may not contain a topic id of a later topic or any later topic's keyword (Section 4). Rendered pages must not contain any card id (search built HTML for the ids of cards in the same file).
10. **`uses` is complete.** `uses` contains every id in this topic's `requires`; every topic id that appears in a link to another lesson, in a "Theorem x.y.z" citation, in `techniques` of this topic's problems, or in a card reference is in `uses` or is the current topic; every id in `uses` has `order` less than the current topic's. `WhatYouNeed` and `TopicHeader` both render from `uses` only; no other hand-written prerequisite list is allowed (fail if the lesson's Section 2 contains a bullet list under "What you need").
11. **Theorems have demos and plain words.** Every `Theorem {topic}.{n}` heading in the lesson has a `theorems` entry, a `:::tip[In plain words]` block, a `:::note[This proof needs]` block, and a `<TheoremDemo>` whose `unit` is the entry's `demo`; that code unit exists, its `solution.cpp` has at most 30 lines, and it has `tests/1.out`. Each proof has at most 8 numbered steps (count the numbered list items between the plain-words block and the preconditions box).
12. **Inline example numbers match their code unit.** For each card with `inline` examples, the unit `code/{topic}/card-{card-id}/tests/1.out` has lines `P1 …`, `P2 …`, `N1 …`, `N2 …` (P = positive in data-file order, N = negative); the `answer` field of each example contains the `brute` value, and each negative's `method_gives` equals the printed `method` value and differs from `brute`.
13. **Examples do not spoil.** Positive examples that name a problem use a problem whose role is `worked_example` in the same topic or any role in an earlier topic; negative examples that name a problem use any problem from this or an earlier topic with role other than `drill`, `checkpoint`, `review`, `exam`, or `ladder` (of this topic).

The agent also runs, by hand before each merge, the keyword search from Section 4 and the self-review in Section 17. Items 9–13 are the guards against the five weaknesses listed in Revision 2; if one is hard to implement exactly, implement a stricter check, never a looser one.

---

## 13. Per-topic pipeline

Run these steps in order. After each: update `PROGRESS.md` and commit.

1. **Scope.** Create the branch, empty lesson from the template, empty data file, `notes/{topic}.md`, code folder. Record in `PROGRESS.md`: allowed topics, new tools, forbidden keywords, glossary terms already defined.
2. **Theory.** Lesson Sections 1–4; glossary entries. Write each theorem in the Section 6.4 layout: plain words, tiny instance, numbered proof steps, preconditions box. Fill `uses` and `theorems` in the data file. Then write each theorem demo unit (Section 8.6): compute the expected output by hand from the proof first, then run it.
3. **Recognition Cards.** Cards in the data file; decisive property = preconditions in problem language. Write constraint shapes with arithmetic. Write each `in_action` on an invented problem and check the numbers. Write the inline positive and negative examples, then the card example unit (Section 8.6) that computes their numbers; copy the numbers into the data file from that output. Weak signals, kill signals, and non-inline examples are provisional until Step 6.
4. **Templates.** Code units with brute and generator; `stress.sh` passes 5000; lesson Section 6.
5. **Bug catalogue.** Break copies of templates, find failing inputs with `stress.sh`, write Section 7. Delete scratch copies.
6. **Problems.** Gather candidates (Section 9.2), check links (9.3), write solution notes (9.4), then choose: worked examples, ladder, drill, look-alike pairs, checkpoint, three review sets. Revise card weak and kill signals from what real statements looked like, and add the problem-based examples (worked examples of this topic; problems of earlier topics) in line with Section 6.5.
7. **Worked examples.** Section 8 in the six-step format; code units tested.
8. **Drill, look-alikes, self-test, checkpoint, reviews.** Fill the data file; review set pages render from it.
9. **Decision map.** Add entries; check the Handbook page renders them in the right groups. Resolve every look-alike and negative-example reference against the card list; replace any that would need a later topic (Section 6.11).
10. **Self-review and merge.** `npm run build` and `bash scripts/test_units.sh code` pass; keyword search clean; read the whole lesson in the browser as a beginner would against Section 17.1; fix anything unclear; merge.

---

## 14. Git workflow and deployment

### 14.0 Branches, commits, merges

- `main` holds only finished work. Topic work on `topic/{id}-{slug}`; infrastructure on `setup/m0`; feedback fixes on `feedback/{date}-{topic}`.
- One commit per pipeline step: `topic(1.3): step 4 templates and stress tests`, with test results in the body (e.g., "stress: 5000/5000 window-sum").
- Merge with `git merge --no-ff`; the merge message lists problem counts by role and card, dropped candidates with reasons, stress-test counts, and open doubts. Tag `topic-{id}`; tag `phase-{n}` after the phase exam merges.
- Never force-push or rewrite `main`.

### 14.1 Continuous integration
A GitHub Actions workflow (if the repository is on GitHub) that, on every push and pull request, installs dependencies, runs `bash scripts/test_units.sh code` (g++ is preinstalled on Ubuntu runners), and runs `npm run build`. It does not deploy unless Section 14.3 is enabled.

### 14.2 Self-hosted serving
The site is static: `npm run build` produces `dist/`, which any web server can serve. No Node.js process runs on the server.

- **Config, not code:** server details live in a gitignored `.env.deploy` file, with a committed `.env.deploy.example`:
  ```
  DEPLOY_HOST=user@example.com
  DEPLOY_PATH=/var/www/cp-training
  SITE_URL=https://cp.example.com
  ```
  Set Astro's `site` option from `SITE_URL` at build time. Never commit hostnames, keys, or passwords.
- **`scripts/deploy.sh`:** loads `.env.deploy`, runs `bash scripts/test_units.sh code` and `npm run build`, then `rsync -az --delete dist/ "$DEPLOY_HOST:$DEPLOY_PATH/"`. It aborts before uploading if either check fails. The upload is a single rsync, so a failed build never replaces a working site.
- **Web server configs:** commit both as examples in `deploy/`, with placeholders matching `.env.deploy.example`:
  - `deploy/Caddyfile.example` (recommended: Caddy obtains and renews HTTPS certificates automatically). Serve `DEPLOY_PATH` with `file_server`, enable `encode gzip zstd`, and set long cache headers for `/_astro/*` (hashed asset files) and no-cache for `*.html`.
  - `deploy/nginx.conf.example`: `root` at `DEPLOY_PATH`, `try_files $uri $uri/ $uri.html =404;`, gzip on, the same cache rules, and a note that HTTPS needs certbot (`certbot --nginx -d <domain>`).
  - Both: a custom 404 page using Astro's `404.html`.
- **HTTPS is required, not optional.** The "copy feedback to clipboard" button uses the browser Clipboard API, which only works on secure (HTTPS) pages or `localhost`. Make the button fall back to a selectable text box when the API is unavailable.
- **Optional password protection:** if Saurabh wants the site private, document HTTP basic auth in both example configs (`basic_auth` in Caddy; `auth_basic` with an `htpasswd` file in nginx), commented out by default.
- **Progress is tied to the exact address.** Browser storage belongs to one origin (protocol + domain + port). Moving the site to a new domain, or switching between `http` and `https`, starts with empty progress. `README.md` and the Progress page must say: export progress before changing the address, then import it on the new one.

### 14.3 Optional automatic deployment
If Saurabh wants deploy-on-merge: a separate GitHub Actions job on push to `main` that runs the same checks and rsyncs `dist/` using an SSH deploy key stored in repository secrets (`DEPLOY_SSH_KEY`, `DEPLOY_HOST`, `DEPLOY_PATH`). Off by default; document how to enable it in `README.md`. Recommend a dedicated server user with write access only to `DEPLOY_PATH`.

### 14.4 Local preview
`npm run dev` for live editing; `npm run build && npm run preview` to check the production build before deploying.

---

## 15. Milestones and review gates

| Milestone | Work | Gate |
|---|---|---|
| **M0** | Astro + Starlight project, KaTeX, React, schemas and validation, storage module, all components (Section 10) working on a small placeholder topic, all custom pages, method page, curriculum data, `stress.sh` and `test_units.sh`, CI, self-hosted deployment files (Section 14.2) with one successful test deploy to Saurabh's server once he fills in `.env.deploy`, `PROGRESS.md`, `FEEDBACK.md`, `README.md`. Delete the placeholder topic at the end. | None |
| **B0–B7** | Problem bank, per `PROBLEM_BANK_PLAN.md` Section 8 (B0–B1 before M1; B2–B7 before M2 unless Saurabh chooses otherwise at the B1 gate) | See that file |
| **R1** | **Quality retrofit** of every topic merged before Revision 2 (this runs first if topics are already live; otherwise skip). Order: 1.6 as the reference topic, then the rest in curriculum order. For each topic, on a `retrofit/{id}` branch: (a) add `uses` and `theorems`, switch to `WhatYouNeed`, fix header/list mismatches; (b) rewrite proofs into the Section 6.4 layout and add theorem demo units; (c) rewrite every card to the Section 5 and 6.5 schema with `in_action` and examples, with card example units; (d) fix look-alike pairs and drill references to structured, order-respecting references and card names. No problem is added, removed, or moved in this milestone (the bank is out of scope). `npm run build` and `test_units.sh` must pass. | ⏸ After 1.6 is retrofitted: set "R1 reference review" to `waiting`; continue with the remaining topics only when Saurabh sets it to `approved`. |
| **M1** | **Topic 1.3 as the exemplar**, all 10 steps, plus its review sets. Missing 1.1 and 1.2 lessons appear as "coming soon" links. | ⏸ Stop. Set "M1 exemplar review" to `waiting` in `PROGRESS.md`; continue only when Saurabh sets it to `approved` (apply any requested changes from `FEEDBACK.md` first). |
| **M2** | Phase 0 (0.1–0.6), phase intro, Phase 0 exam | ⏸ |
| **M3** | 1.1, 1.2; then revise 1.3 to match what 1.1/1.2 taught (links, terms, theorem citations); then 1.4–1.7; Phase 1 exam | ⏸ |
| **M4** | Phase 2 | ⏸ |
| **M5** | Phase 3 | ⏸ |
| **M6** | Phase 4 | ⏸ |
| **M7** | Phase 5 | ⏸ |
| **M8** | Phase 6 | ⏸ |
| **M9** | Phase 7 | ⏸ Final review |

**Pacing:** if the topic Saurabh is studying (in `PROGRESS.md`) is more than 3 topics behind the latest finished topic, pause new topics and work only on feedback and quality passes until he catches up.

---

## 16. Progress, resuming, and feedback

### 16.1 `PROGRESS.md` format (exact headings)
```markdown
# Progress

## Now
- Milestone:
- Topic:
- Branch:
- Last completed step:
- Next action:

## Gates
| Gate | Status | Date |
|---|---|---|

## Saurabh is studying
- Topic:

## Topics
| id | status | merged commit |
|---|---|---|

## Scope notes for current topic
- Allowed:
- New:
- Forbidden keywords:

## Blocked
-

## Questions for Saurabh
-
```

### 16.2 Resuming after interruption
At the start of every session: `git status` and `git log -5`; read `FEEDBACK.md`; read `PROGRESS.md`; continue from "Next action". Finish any partially done step before starting another.

### 16.3 `FEEDBACK.md` format and handling
```markdown
## 2026-10-12 — topic 1.3
- Type: confusing | error | wrong link | misplaced problem | too hard | too easy | missing | other
- Where: section 4, Theorem 1.3.1  (or problem id)
- What: …
- Status: open
```
Handle every `open` item before new topic work, on a `feedback/…` branch; set `Status: fixed in {commit}`. Repeated Recognition misses on one card mean: rewrite that card's weak signals, kill signals, and look-alikes, and add a drill item for it. A "misplaced problem" report means: recheck the solution note; if the problem needs a later technique, replace it and add it to "Dropped candidates".

---

## 17. Definition of Done

### 17.1 Topic
- [ ] `npm run build` and `bash scripts/test_units.sh code` pass.
- [ ] All 14 lesson sections complete and rendering; review sets render.
- [ ] Every proof has a preconditions box; every card's decisive property restates it.
- [ ] Every theorem follows the Section 6.4 layout: plain-words block, tiny instance, ≤ 8 numbered steps, preconditions box, `<TheoremDemo>` with hand-computed expected output.
- [ ] Every card has constraint shapes with arithmetic, weak signals as form + shape, an `in_action` block, ≥ 2 positive and ≥ 2 negative examples (inline ones backed by a card example unit), and look-alikes shown by card name.
- [ ] No look-alike, drill answer, example, or decision-map reference points to a later topic; no internal id (card slug, file name) is visible in the rendered page.
- [ ] The page header "Builds on" and the "What you need" list are identical (both from `uses`) and cover every earlier topic the lesson links or cites.
- [ ] Every problem has a solution note with techniques; every link opened and title confirmed with `checked_on`.
- [ ] Keyword search shows no later-topic terms outside "What this topic does not cover".
- [ ] Every abbreviation expanded on first use on the page; every term defined before use; every C++ construct explained.
- [ ] Every rung names its twist; difficulty non-decreasing within each card.
- [ ] Drill has ≥ 3 earlier-topic answers; each look-alike pair names its flipping difference.
- [ ] Decision map entries render in the Handbook; glossary entries render.
- [ ] Hints, logging, drill reveal, checkpoint timer, and review due dates work on this topic in the browser (desktop and a narrow mobile width).
- [ ] Beginner read-through done, including the proof reading test in Section 6.4 (every proof step followable with Phase 0 knowledge plus this page); `PROGRESS.md` updated; merged and tagged.

### 17.2 Phase
- [ ] All topics done; phase intro and exam complete with remediation map.
- [ ] "Coming soon" links in earlier lessons now point to real lessons.
- [ ] Tagged `phase-{n}`; gate set to `waiting`.

---

## 18. Failure handling

| Situation | Action |
|---|---|
| Stress mismatch on a template | Fix the template or brute; rerun 5000. Never reduce iterations. |
| Deliberate bug passes stress | Strengthen the generator; if it still passes, prove the variant and document it as an alternative (Section 8.5). |
| Not enough pure problems for a card | Search more sources from Section 9.2; if still short, merge the card with a related one or reduce to minimum counts. Never relax purity. |
| Page title differs from your expectation | Use the page's title, and re-read the statement to make sure it's the problem you meant. |
| Page cannot be opened | Drop the problem; note it under "Blocked". |
| A card has no honest negative example from this or earlier topics | Use an inline counterexample with real numbers and name an earlier-topic tool; if the only correct tool is taught later, write the negative as an inline instance whose `correct_tool` is `brute force (topic 0.5)`, or drop the card from the topic and note it under "Blocked". Never name a later topic. |
| A look-alike's other side is taught later | Remove it from this lesson. The later topic's lesson adds the pair (it may reference this card). Add a note in `PROGRESS.md` under the later topic's scope notes. |
| Theorem demo output disagrees with the hand-computed expected output | Treat it as a possible error in the theorem, the proof, or the program. Resolve it before anything else; never overwrite `tests/1.out` with the program's output. |
| A proof cannot fit in 8 steps | Split it into lemmas, each with its own plain words and preconditions box, and give each lemma a demo or a shared demo covering them. |
| Unsure a proof is right | Write a small exhaustive check of the theorem's claim on small inputs; if still unsure, note it in the merge message and "Questions for Saurabh". |
| A teaching decision not covered here | Choose what best serves Section 1.2's priorities, note it in the merge message, continue. |
