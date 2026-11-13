# CURRICULUM_GAPS_PLAN.md: Missing Topics, Topic Splits, and Contest Practice

**Audience:** an autonomous coding agent working in the `t3ns0r-ss/self-engine` repository.
**Owner:** Saurabh. He reviews every PR and replies "merge" or asks for changes. Do not merge without him.
**Start condition:** start only after the work in `LESSON_RESTORE_PLAN.md` is fully merged, including Phase 5, and `main` is quiet (no open PR or branch still touching lessons). Check `PROGRESS.md` and the open PRs first.

Read these first, in order:
1. `PLAN.md`. Section 13 (per-topic pipeline) and Sections 6 to 9 (lesson template, writing rules, code, problems) apply to every new topic.
2. `PROBLEM_BANK_PLAN.md` and `FILL_SHORT_TOPICS_PLAN.md`. Every new problem follows their rules.
3. `DEVELOPER_GUIDE.md`.
4. `docs/LESSON_STYLE_GUIDE.md`. It applies to the notes-format lessons (0.1 to 2.4 and 3.1).

Every rule there still applies unless this file says otherwise:
- never write a problem link, title or rating from memory, but open and read it;
- strict topic order, where later topics are named only under "What this topic does not cover";
- a solution note for every problem;
- all lesson code tested;
- plain global English, terms defined before use, abbreviations expanded on first use;
- Saurabh's own text and code in the notes lessons are never changed.

---

## 0. What Saurabh asked for

1. **Add the missing topics.** A review against the Codeforces Expert target found ten gaps (Section 1.1).
2. **Split topics that bundle two techniques**, and **make every split topic deeper** than it is today. Two reviews proposed the splits (Section 1.2). Saurabh asked to apply them and to increase the depth of each split topic.
3. **Add contest practice.** Take the useful parts of an outside "curriculum upgrade" plan reviewed on 2026-11-13:
   - implementation drills;
   - a volume set;
   - a bridge set;
   - a contest strategy page;
   - a "read one accepted solution" prompt.

   Leave out the rest (Section 9).

---

## 1. What exists today (checked on 2026-11-13)

### 1.1 Gaps

| Gap | Today | Evidence |
|---|---|---|
| Geometry | nothing | no lesson mentions cross product or orientation |
| Interactive problems | named as out of scope | 7.5 line 45, 7.7 line 44 |
| Eulerian path or circuit | "not part of this course" | 4.7 line 41 |
| 2-SAT | "a Phase 7 idea" | 4.7 line 38 |
| Flow, min cut, matching | "not part of this course" | 4.7 line 41 |
| Convex hull trick, D&C DP | "a different family, not in this course" | 7.3 line 47 |
| Divide and conquer as a method | named, "no code here" | 3.1 lines ~185–189 |
| Chinese remainder theorem (CRT) | "not part of this course" | 2.1 line 46, 2.2 line 49 |
| Lucas's theorem | "not part of this course" | 2.3 line 47 |
| Probability DP | one ladder problem, no card | `3-5.yaml` (`lc-knight-probability-in-chessboard`) |
| Basic strings | "one-pass string processing" card only | 0.3 Section 4.3; 0.6 barely covers `std::string` |

### 1.2 Proposed splits: what is really there

Every proposed split **already has its own recognition card**. What is thin is the depth (3 to 6 rungs, few theorems, variants marked "not in this course") and where the card sits.

| Proposed split | Today | Rungs today |
|---|---|---|
| Sweep line, data-structure tier | 1.5 has Saurabh's "Sweepline" section (his text, around line 1414) **with no card**. Rectangle union and sweep with a segment tree appear nowhere. | 0 |
| Meet in the middle (MITM) | card `meet-in-middle` in 3.1, Theorem 3.1.4 | 5 |
| Mo's algorithm | card `mo-offline` in 5.4; "Mo's with changes" and "Mo's on a tree" are "not in this course" | 6 |
| Binary trie | card `binary-xor` in 6.3 (strings phase) | 6 |
| Rerooting | card `rerooting` in 7.1 | 4 |
| State-space search | card `state-graph` in 4.1 and card `extra-state` in 4.3 | 3 + 3 |
| Extended Euclid and linear Diophantine equations | card `bezout` in 2.1 (Saurabh's notes lesson) | 4 |
| LIS in $O(n \log n)$ | card `lis` in 3.4 | 5 |
| Contribution technique | card `per-bit-contribution` in 1.7, **and 2.4 is already "Linearity of expectation, contribution technique"** with card `contribution-total` | 3 + 4 |
| Topological sort | card `dependency-order` in 4.2 | 4 |

### 1.3 Validator limits a split must respect

These are in `src/lib/validate-topics.mjs` and `src/lib/validate.mjs`.

| Rule | Limit |
|---|---|
| Recognition cards per topic | 3 to 6 (7.8 excepted) |
| Ladder size per topic | 12 to 20 |
| Rungs per card | at least 3 |
| Bank practice set per topic | at least 20 problems |
| Bank reserved set per topic | at least 24 problems |
| 7.8 Technique recognition | at least 40 problems, at least 2 from every phase |

What this means:
- A parent that loses a card must keep 3 cards and a ladder of 12 or more. 5.4 and 6.3 would drop to 2 cards, so each gets a new card (Section 5).
- A new topic needs 3 to 6 cards and 44 bank problems. If an honest search finds fewer, use `status: short` as `FILL_SHORT_TOPICS_PLAN.md` allows, and say so in the PR.

### 1.4 Other facts

- **Topic order comes from `order` in `src/data/curriculum.yaml`.** The id is only a label, and the validator checks "later topic" by `order`.
- **Never rename or renumber an existing topic id.** Learner topic state is stored in the browser by topic id (`KEYS.topics` in `src/lib/storage.ts`). Problem progress is stored by problem id, so moving a problem to another topic keeps its progress.
- **Two-digit ids such as `7.10` break theorem numbering.** `src/lib/validate-r2.mjs` lines 33 and 170 match theorems with `\d\.\d\.\d+`, so `Theorem 7.10.1` does not match. Phase 0 changes these to `\d\.\d+\.\d+`. Search for other one-digit assumptions (`grep -rnE '\\d\\.\\d' src scripts`).
- `48` appears in `PLAN.md` (Section 4 title and registry), `DEVELOPER_GUIDE.md` (lines 9, 13, 39) and the phase index pages. The LLD (low-level design) 48 in `validate-design.mjs` is a different track. Do not touch it.
- New keywords can cause false "later topic" hits in earlier lessons. Run `node scripts/keyword_collisions.mjs` after adding any.

---

## 2. Decisions (list them in the Phase 0 PR so Saurabh can overrule them)

### 2.1 Gaps

1. **Interactive problems: new topic 1.8**, last in Phase 1, `requires: ["1.4"]`. At this level they are mostly binary search under a query budget, so the topic needs 1.4. The suggested "1.0" before 1.1 could not use it.
2. **Eulerian path: into 4.2 (graph structure).** 4.1 is traversal. 4.2 already uses 4.1's depth-first search (DFS).
3. **Divide and conquer, split by level:**
   - the plain method (merge sort inversion counting) goes into 3.1, where Saurabh's note already names it without code;
   - D&C DP optimisation and CDQ (offline divide and conquer over time) go into 7.3 with the convex hull trick;
   - nothing goes into 1.4.
4. **Basic strings:**
   - a `std::string` section in 0.6;
   - 2 or 3 rungs on 0.3's existing string card.
5. **Geometry: new topic 4.8**, last in Phase 4, `requires: ["0.4", "1.1"]`.
6. **2-SAT: into 4.7.**
7. **CRT moves into the new topic 2.5** (Section 2.2), not into 2.2. **Lucas's theorem goes into 2.3.**
8. **Probability DP: new card in 3.5**, adding `"2.4"` to `requires`.
9. **Convex hull trick: into 7.3.**
   - New title: "DP speed-ups: Fenwick and segment trees, convex hull trick, divide and conquer".
   - Add `"1.6"` to `requires`.
10. **Flow and matching: new topic 7.9**, placed by `order` just before 7.8, so the recognition set can use it. `requires: ["4.1", "4.4"]`.

### 2.2 Splits

| # | New topic | id | Placed after (by `order`) | Requires | Band | Takes from |
|---|---|---|---|---|---|---|
| S1 | Sweep line with a segment tree | 5.5 | 5.3 | 1.1, 1.5, 5.2, 5.3 | 1800–2100 | nothing (new card); 1.5 keeps its sweep tier |
| S2 | Meet in the middle | 3.9 | 3.1 | 3.1, 1.3, 1.4 | 1500–1900 | card `meet-in-middle`, Theorem 3.1.4 and its units from 3.1 |
| S3 | Mo's algorithm | 5.6 | 5.4 | 5.4, 4.5, 4.6 | 1800–2100 | card `mo-offline` from 5.4 |
| S4 | Binary trie and XOR | 5.7 | 5.6 | 1.7, 4.4 | 1800–2100 | card `binary-xor` from 6.3 |
| S5 | State-space search | 4.9 | 4.3 | 4.3, 1.7 | 1600–2000 | cards `state-graph` (4.1) and `extra-state` (4.3) |
| S6 | Rerooting | 7.10 | 7.1 | 7.1 | 2000–2400 | card `rerooting` from 7.1 |
| S7 | Linear Diophantine equations and CRT | 2.5 | 2.2 | 2.1, 2.2 | 1300–1700 (Phase 2 band) | card `bezout` from 2.1; CRT from Section 2.1 item 7 |

Reasons for the choices that differ from the reviews:
- **S4 goes to Phase 5, not Phase 6.** The review's own argument is that a strings phase hides it. Phase 5 (range data structures) has exactly the suggested band, 1800–2100, while Phase 6 is 1900–2200. It needs only 1.7, plus 4.4 for XOR-MST.
- **S2 has no breadth-first search (BFS).** The review asked for a "MITM on graphs, BFS each half" rung, but BFS is topic 4.1, after 3.9, so the rung would break topic order. Use the same idea with recursion from 3.1 instead (split a grid path of length $n$ into two halves of $n/2$ steps, enumerate each half by recursion, and merge on the middle cell). Mention MITM with BFS on a state graph as a rung in 4.9 (S5), which comes later.
- **S2 and bitmask DP side by side.** 3.9 comes before 3.7, so 3.9 may only name bitmask DP under "does not cover". The comparison ("$n \le 20$: bitmask DP or $2^n$; $n \le 40$: MITM") goes in **3.7's** look-alike pairs and decision map, which can see both.
- **S7 includes CRT.** Extended Euclid, linear Diophantine equations, linear congruences and CRT share one tool and form one clean topic. 2.1 keeps Saurabh's extended Euclid section (it is his notes text), and 2.5 builds on it.

### 2.3 Moderate splits: deepen in place, do not split

- **LIS (3.4):** keep in 3.4. LIS opens the topic, and splitting it would leave 3.4 short. Deepen the `lis` card to 7 or more rungs (Section 5).
- **Contribution (1.7):** do not split. The general method already has its own topic, 2.4 ("contribution technique"). Deepen 1.7's per-bit card. Make 2.4's lesson link back to 1.7's per-bit card as the first use of the idea.
- **Topological sort (4.2):** keep in 4.2, which is tied to cycle detection. Deepen to 6 rungs.

### 2.4 Keep as subsections, as the review recommends

Prefix function with Z-function (6.2), suffix array with LCP array (6.4), 2D prefix sums (1.2), bitset knapsack (3.3) and segment-tree descent (5.3) stay where they are.

### 2.5 Result

**58 CP topics**: the 48, plus 1.8, 4.8 and 7.9 (gaps), plus 2.5, 3.9, 4.9, 5.5, 5.6, 5.7 and 7.10 (splits).

New topics use the template format (PLAN.md Section 6), because no notebook exists for them. If Saurabh writes notes for one later, it is converted the way 3.1 was.

Final order where it changes (new topics in **bold**):
- Phase 1: 1.1 … 1.7, **1.8**
- Phase 2: 2.1, 2.2, **2.5**, 2.3, 2.4
- Phase 3: 3.1, **3.9**, 3.2 … 3.8
- Phase 4: 4.1, 4.2, 4.3, **4.9**, 4.4 … 4.7, **4.8**
- Phase 5: 5.1, 5.2, 5.3, **5.5**, 5.4, **5.6**, **5.7**
- Phase 7: 7.1, **7.10**, 7.2 … 7.7, **7.9**, 7.8

Ids that do not follow `order` (3.9 second in Phase 3, for example) are a cost of keeping existing ids. Check that every page lists topics by `order`, never by sorting ids as strings.

---

## 3. How to move a card out of a topic (splits)

1. Move these from the parent to the new topic's data file, without rewording:
   - the card;
   - its ladder rungs;
   - its drill items, look-alike pairs, self-test and checkpoint items, and decision-map lines;
   - its theorems (renumbered `Theorem <new id>.<n>`, and every citation updated);
   - its code units (`code/<old>/<unit>` → `code/<new>/<unit>`);
   - its bank entries (`src/data/bank/<old>.yaml` → `<new>.yaml`, with `techniques` updated).

   Then deepen them (Section 5).
2. In the parent lesson:
   - **template format:** remove the moved theorem, template and bugs. Under "What this topic does not cover", add one line: "…: covered in topic X.Y".
   - **notes format (2.1, 3.1, 1.5):** never move or change Saurabh's own text. Only text added by the restore work may move. In 3.1 the meet-in-the-middle section and Theorem 3.1.4 came from the restore, so they move, and one pointer line stays. In 2.1, Saurabh's extended Euclid section stays as it is, and the new 2.5 starts from it. Run `check_code_unchanged.mjs` on the parent.
3. Re-check the parent against Section 1.3 (3 to 6 cards, ladder 12 to 20, at least 3 rungs per card). Refill the parent's ladder from its bank when it drops below 12.
4. Re-check every lesson that cited a moved theorem or card. Run `validate` and search for the old theorem number.

## 4. How to extend an existing topic (gaps and deepening)

An extension is a new card, or new rungs, added the same way the topic's other cards were added.

**Template-format topics:**
- definitions, also added to `glossary.yaml` and `glossary_added`;
- a numbered theorem in the PLAN.md 6.4 layout (statement, plain words, tiny instance, proof of at most 8 steps, "This proof needs"), with a tested `TheoremCode` unit;
- the card (decisive property, constraint shapes with arithmetic, "Recognition in action", positive and negative examples);
- a template unit with a brute force and a generator, passing `stress.sh` with 5000 runs;
- at least 2 bug catalogue entries;
- at least 4 rungs;
- 2 drill items, 1 look-alike pair, 2 self-test questions, 1 checkpoint item and 1 decision-map line.
- **Delete the "not part of this course" line** that named it. In a lesson that comes before this topic, keep the line but change it to "covered in topic X.Y".

**Notes-format topics** (0.6, 1.5, 1.7, 2.2, 2.3, 3.1):
- add a new `##` section in the notes voice of `docs/LESSON_STYLE_GUIDE.md`, in this order: a small example, brute force then the better way, a dry run, functions-only code, cost with the reason, a common mistake;
- write the theorem in the format of `LESSON_RESTORE_PLAN.md` Section 4.2, with maths formatted per its Section 4.3;
- add the data items exactly as for template topics;
- **insert only:** never change his lines or code.

If a ladder would go above 20, move the weakest rungs to "More practice" in the bank. Do not delete them.

---

## 5. Content and depth

The tables give scope and depth. They do not give problems: collect problems from the platforms under the bank rules. CSES has Geometry, Graph and Advanced Techniques sections that fit several of these topics. Codeforces tags (`meet-in-the-middle`, `interactive`, `flows`, `2-sat`, `geometry`) help find candidates through the API. Open and read every candidate.

### 5.1 Split topics (new pages): each at least 4 cards and at least 16 ladder rungs

**S1. 5.5 Sweep line with a segment tree**

| Card | Must teach | Rungs (minimum) |
|---|---|---|
| Area of a union of rectangles | coordinate compression as its own first step (from 1.1); events at $x$ with $+1/-1$ on a $y$-range; a segment tree over compressed $y$ storing "covered length" with a count instead of lazy push-down (why push-down is not needed here); area $= \sum (\text{covered length}) \cdot \Delta x$ | 4 |
| Perimeter of a union | horizontal part from the change in covered length; vertical part from the number of separate covered pieces (store "pieces", "left end covered", "right end covered" in a node) | 3 |
| Point covered by the most rectangles | lazy range-add with range-max; recovering where the maximum happens | 3 |
| Counting with a Fenwick sweep | points inside rectangles answered offline; horizontal and vertical segment intersections counted (uses 5.2) | 3 |
| Ties at one coordinate (rung inside every card, plus one rung of its own) | closing before opening for half-open $[l, r)$, opening before closing for closed $[l, r]$, with the proof of why each order is right and a failing input for the wrong one | 1 + inside others |

- **Theorems:** union area by sweep; the counted-cover node is correct without push-down; Fenwick sweep counts each pair once.
- **Bugs:** wrong tie order; compressing without the end coordinates; a segment-tree leaf meaning a point instead of a gap between neighbours; `int` overflow of the area.
- **Out of scope:** Klee's measure in more dimensions, and Bentley–Ottmann for general segment intersections. Say "not in this course".
- **In 1.5 (sweep tier 1):** add a card "Events sorted and scanned" to 1.5 with 4 rungs:
  - coverage at least $k$;
  - half-open versus closed intervals, as its own drill item and rung;
  - three running states compared on one input ("number of active intervals", "most overlap", "sum over active");
  - ties at one coordinate in the plain case.

  Saurabh's sweep section stays as it is. Add the card's theorem and code after his section, in notes voice. 1.5 then has 6 cards (the maximum). Keep its ladder at 20 or fewer by moving weak rungs to "More practice".

**S2. 3.9 Meet in the middle**

| Card | Must teach | Rungs |
|---|---|---|
| The size band | read $n$ first: $2^{20} \approx 10^6$ is fine, $2^{40} \approx 10^{12}$ is not, and $2 \cdot 2^{20}$ with a sort is; the band is a range, not one number ($n \le 20$: plain $2^n$; $n \le 40$: MITM; larger: needs structure, named only) | 3 (including one where plain $2^n$ is the right answer) |
| Merge by sort and binary search | subset sums of each half; sort one half; for each sum of the other half, `lower_bound` (1.4) for "count with sum $\le T$", "closest to $T$", "exactly $T$" | 4 |
| Merge by two pointers | when the merge test is monotone in both lists, two pointers (1.3) replace binary search; the rule for when it works | 3 |
| Pairs instead of subsets | 4-sum and "choose items in pairs" as MITM over pairs with a hash map or sorting; memory cost of storing $n^2$ pairs | 3 |
| Paths split in the middle | a grid path of $2k$ steps split at step $k$, each half enumerated by recursion (3.1), merged per middle cell with a map per cell | 2 |
| When the halves are not independent | one problem where choices interact across the split, so naive MITM counts wrong; how to carry the shared part in the state, or why MITM does not apply | 2 |

- **Theorems:** Theorem 3.1.4 (moved and renumbered); cost $O(2^{n/2} \cdot n)$ with its proof; correctness of the two-pointer merge under monotonicity.
- **Bugs:** generating half-sums in $O(2^{n/2} \cdot n)$ instead of $O(2^{n/2})$ by building on the previous half; overflow of sums; an odd $n$ split unevenly.
- In **3.7** (bitmask DP), add a look-alike pair and a decision-map line: "$n \le 20$ and the answer depends on the set: bitmask DP or $2^n$" versus "$n \le 40$ and the set splits into halves: MITM (3.9)".

**S3. 5.6 Mo's algorithm**

| Card | Must teach | Rungs |
|---|---|---|
| Offline range queries with cheap add and remove | block size $B \approx n/\sqrt{q}$; query order by block of $l$, then $r$; proof of $O((n+q)\sqrt n)$ moves; the odd-even trick | 4 (moved 6, keep the best 4, rest to "More practice") |
| Mo with changes | time as a third coordinate; $B \approx n^{2/3}$; $O(n^{5/3})$ with its derivation | 3 |
| Mo on a tree | path queries through an Euler tour of in and out times (4.5), the LCA (lowest common ancestor) fix (4.6), and a vertex seen twice cancelling | 3 |
| Add only (rollback Mo) | when remove is expensive (for example a maximum): per block, extend right only and undo the left part | 3 |
| Order of the queries | Hilbert curve order as a faster sort, measured, not assumed | 1 |

- **Theorems:** the movement bound for each variant.
- **Bugs:** moving pointers in the wrong order (remove before add can produce an empty, broken window); a block size from $n$ alone when $q \ll n$; forgetting to restore after rollback.
- **5.4 keeps 2 cards and gains a third:** "rebuild every $\sqrt{q}$ changes" (keep a list of recent changes, answer queries by the last rebuild plus a scan of the list, and rebuild when it grows past $\sqrt q$), with 3 rungs and a theorem for the cost. Remove 5.4's "not in this course" line about Mo with changes and Mo on a tree, and point to 5.6.

**S4. 5.7 Binary trie and XOR**

| Card | Must teach | Rungs |
|---|---|---|
| Largest XOR with a set | walk bits from the highest down, taking the opposite bit when present; largest XOR pair; largest XOR subarray through prefix XOR (1.7) | 4 |
| Counting and k-th | counts in nodes; number of pairs with XOR below $K$; k-th smallest XOR with a value | 3 |
| Changing sets | insert and delete with counts; queries limited to elements up to a bound answered offline by sorting | 3 |
| XOR-MST | Borůvka's algorithm or recursive split by the highest bit, with a trie to find the cheapest cross edge (uses 4.4) | 2 |
| Choosing the tool | trie versus sorting plus high-bit-first greedy (1.7 card `high-bit-first`) versus a linear basis (named only) | 2 (look-alike rungs) |

- **Theorems:** greedy by highest bit gives the maximum XOR; counting below $K$ by walking the bits of $K$.
- **Bugs:** too few bits ($2^{30}$ versus $2^{31}$ values); memory as nodes $=$ (number of values) $\times$ (bits); deleting without counts.
- **6.3 keeps 2 cards and gains a third** string card: "a trie with counts for prefix questions and deletions" (count words with a prefix, remove a word), with 3 rungs.
- **Out of scope:** XOR linear basis and persistent tries. Say "not in this course".

**S5. 4.9 State-space search**

| Card | Must teach | Rungs |
|---|---|---|
| Invent the node | the graph is not given: the node is (place, extra information); writing the state, its size and the edges before coding; state count times edges against the budget | 4 (from `state-graph`) |
| BFS over (place, mask) | keys and doors, visiting every target ($n \le 16$); `dist[place][mask]` | 3 |
| Dijkstra over (place, resource) | fuel, a coupon used at most $k$ times, (cell, direction) with turn costs; layered graphs | 4 (from `extra-state`) |
| 0-1 BFS over states | free and paid moves over states (uses 4.3) | 2 |
| Meeting in the middle on states | bidirectional BFS on a huge implicit graph (puzzle states), the MITM idea from 3.9 with BFS | 2 |
| Too many states | when the state count is too big, which part of the state can be dropped (a dominance argument) | 2 |

- **Theorems:** BFS and Dijkstra stay correct on any graph whose nodes are states (cited from 4.1 and 4.3); the state-count budget rule.
- **Bugs:** marking visited by place only; forgetting the mask in the visited array; memory of `dist` with large states.
- 4.1 and 4.3 each keep 4 cards. Refill their ladders to 12 or more from their banks.

**S6. 7.10 Rerooting**

| Card | Must teach | Rungs |
|---|---|---|
| Answer for every root, combine can be undone | two passes; moving the root across an edge; sum of distances to all vertices | 4 (from `rerooting`) |
| Combine cannot be undone | prefix and suffix results over each vertex's children (maximum, GCD); the cost stays $O(n)$ | 3 |
| Farthest vertex from every vertex | top two downward heights plus the upward value | 2 |
| Edges with a direction | the fewest reversals to reach every vertex, and edge costs depending on direction | 2 |
| Counting from every root | ways modulo a prime, with inverses (2.2) or prefix and suffix products | 2 |
| Is rerooting needed? | one root is enough versus all roots, as a look-alike rung against 7.1 | 1 |

- **Theorems:** the reroot transition is correct; prefix and suffix exclusion gives each child's "all except me" in $O(\deg)$.
- **Bugs:** recursion depth on a path of $2 \cdot 10^5$ vertices (iterate in BFS order); double counting the parent; dividing modulo a prime by zero.
- 7.1 keeps 3 cards. Refill its ladder.

**S7. 2.5 Linear Diophantine equations and CRT**

| Card | Must teach | Rungs |
|---|---|---|
| $ax + by = c$ | solvable exactly when $\gcd(a, b)$ divides $c$; one solution from extended Euclid (Saurabh's 2.1 section) | 3 (from `bezout`) |
| All solutions and the best one | $x = x_0 + k \cdot b/g$, $y = y_0 - k \cdot a/g$; solutions in a range, smallest non-negative $x$, minimising $x + y$ | 3 |
| $ax \equiv b \pmod m$ | solvable exactly when $g$ divides $b$; $g$ solutions modulo $m$ | 2 |
| CRT | two congruences merged; non-coprime moduli (no solution when residues disagree modulo the gcd); many congruences one by one; overflow (`__int128` or reduce first) | 4 |
| Counting in a range | how many $x$ in $[L, R]$ meet the conditions, using the merged modulus | 2 |

- **Theorems:** Bezout's identity (cited from 2.1); the general solution; CRT existence and uniqueness modulo the least common multiple (lcm).
- **Bugs:** negative $x_0$ handled with `%` in C++; the lcm overflowing; dividing by $g$ in the wrong place.
- 2.1 keeps 4 cards. Refill its ladder. In 2.2, change the CRT "not part of this course" line to point to 2.5.

### 5.2 Deepened in place (no split)

| Topic, card | Add | Rungs after |
|---|---|---|
| 3.4 `lis` | non-strict LIS; recovering one LIS; count of LIS in $O(n^2)$; the "tails" array proof as a numbered theorem if missing | 7 or more |
| 1.7 `per-bit-contribution` | sum of pairwise XOR, AND and OR; sum over subarrays bit by bit; a link forward to 2.4 under "does not cover" | 5 or more |
| 2.4 `contribution-total` | a link back to 1.7's per-bit card in the lesson text; one rung that mixes both | 5 or more |
| 4.2 `dependency-order` | lexicographically smallest order (priority queue in Kahn's algorithm); is the order unique; counting levels | 6 or more |

### 5.3 Gap extensions

| Topic | New card | Must teach | Out of scope |
|---|---|---|---|
| 0.6 | Strings in C++ | `substr` is $O(k)$; `s = s + c` copies, `+=` does not; `find` and `npos`; comparing; `cnt[26]`; `stoi` and `to_string` overflow | hashing (6.1), prefix function (6.2) |
| 0.3 | rungs on "One-pass string processing" | palindrome check with two indices, counting runs, case conversion | — |
| 2.3 | Lucas's theorem | $\binom{n}{r} \bmod p$ for small prime $p$ by base-$p$ digits; proof via $(1+x)^p \equiv 1 + x^p$; when to use it ($n \ge p$) | prime powers: not in this course |
| 3.1 | Divide and conquer | split, solve, merge; $T(n) = 2T(n/2) + O(n)$; counting inversions by merge sort; maximum subarray by D&C | closest pair: 4.8 |
| 3.5 | Probability DP | probabilities as states; forward and backward expectation DP; $p \cdot q^{-1} \bmod M$ (2.2) | Markov chains with cycles: not in this course |
| 4.2 | Eulerian path and circuit | degree conditions and connectivity of the edges; Hierholzer's algorithm, iterative; why the Euler tour of a tree (4.5) is different | — |
| 4.7 | 2-SAT | implication graph; unsatisfiable when $x$ and $\lnot x$ share a strongly connected component (SCC); assignment from the SCC order; "two options per item, pairwise conflicts" | — |
| 7.3 | Convex hull trick; D&C optimisation | lines and min queries; monotone slopes with a deque; Li Chao tree (5.3); D&C optimisation when the best split is monotone; CDQ with a Fenwick tree | Knuth's optimisation, Aliens trick: not in this course |

### 5.4 Gap topics (new pages)

**1.8 Interactive problems.** Title: "Interactive problems: flushing, query budgets, adaptive judges".
- **Teach:**
  - your output is the judge's input;
  - flushing (`endl`, `cout.flush()`, `fflush(stdout)`), and "Idleness limit exceeded" when you forget;
  - reading `-1` and exiting;
  - counting the query budget before coding;
  - adaptive judges (answers stay consistent with all replies so far);
  - testing locally with a small interactor function, so the lesson code is still testable.
- **Theorems:** any strategy needs $\lceil \log_2 n \rceil$ yes/no queries for $n$ answers; binary search meets this (Theorem 1.4.1).
- **Cards:**
  - binary search under a budget;
  - halving with comparison replies;
  - constructive queries, only if the problems found stay within Phase 1 topics.
- **Code units need a judge.** Add a unit format with a judge function in `tests/`, and document it in `DEVELOPER_GUIDE.md`.

**4.8 Basic geometry.** Title: "Basic geometry: cross product, orientation, segments, polygons". Integers first (`long long`).
- **Teach:**
  - dot and cross product, and orientation;
  - collinear checks;
  - segment intersection with touching and overlapping cases;
  - shoelace area kept as $2 \times$ area;
  - point in polygon, boundary case first;
  - Pick's theorem;
  - Andrew's monotone chain hull;
  - closest pair by a sweep with a `set`.
- **Bugs:**
  - cross-product overflow at $10^9$ coordinates;
  - `==` on doubles;
  - collinear hull points;
  - the boundary case.
- **Out of scope:** half-plane intersection, 3D and circles. Say "not in this course".

**7.9 Flow and matching.** Title: "Maximum flow, minimum cut, bipartite matching".
- **Teach:**
  - residual graphs;
  - Edmonds–Karp, then Dinic;
  - the max-flow min-cut theorem with proof;
  - recovering the cut;
  - bipartite matching (as flow, and Kuhn's algorithm);
  - König's theorem;
  - disjoint paths by vertex splitting.
- **Recognition is the main skill:** "choose a side per item and pay for separated pairs" means min cut, and "assign items to slots" means matching. The look-alike pairs must include greedy assignment (7.4) and bitmask DP (3.7).
- **Out of scope:** min-cost flow, lower bounds, general matching (blossom) and the Hungarian algorithm. Say "not in this course".

### 5.5 For every new topic

Follow `PLAN.md` Section 13 exactly:
1. scope;
2. theory;
3. cards;
4. templates;
5. bugs;
6. worked examples (6 steps);
7. ladder;
8. drill;
9. look-alike pairs;
10. self-test, checkpoint and decision map;
11. review gate.

Build the bank first.

Also update:
- `PLAN.md` Section 4 (registry, count 58) and `DEVELOPER_GUIDE.md` counts;
- phase index pages;
- phase exams for every phase that gains a topic (under the existing exam rules);
- 7.8 Technique recognition (mixed-set problems using the new cards, at least 2 per phase still);
- the handbook decision map.

---

## 6. Contest practice additions

Put these in their own data files and pages. **Do not add them as fake topics in `curriculum.yaml`.** Dashboard, exams, sync, validation and the keyword scan all loop over topics.

1. **Implementation drills.**
   - 8 to 12 drills, 3 to 5 minutes each, with tested units in the repository's format (`code/<topic>/<unit>/solution.cpp` plus `tests/`, compiled with `-Wall -Wextra -Werror`).
   - Each drill sits in the earliest topic it needs:
     - read until end of file (0.1);
     - many test cases with no reset bug (0.1);
     - sort by several keys (1.1);
     - prefix sums in 5 minutes (1.2);
     - overflow-safe midpoint (1.4);
     - half-open versus closed events (1.5);
     - grid BFS skeleton (4.1, **not** Phase 0).
   - Show them under "Check yourself" and on a "Drills" page. Link the Method page's "Implementation bug" category to that page.
2. **Volume set (800–1000).**
   - `src/data/sets/volume-0.yaml` and a page rendering it as a table.
   - Each problem is opened, read, tagged with the earliest topic it needs, and has `checked_on`.
   - Target 40, with an honest count if fewer. Page text: speed and clean code, not new ideas.
   - Bank validation must cover these files (no duplicates of reserved exam problems).
3. **Bridge set, Phase 4 to 5 (1900–2100).**
   - `src/data/sets/bridge-4-5.yaml` with 10 to 15 problems, each with `have` (known tool) and `new_idea` (one line).
   - Check every `new_idea` by reading the problem.
4. **Contest strategy page** (`src/content/docs/contest-strategy.mdx`, linked from the Method page).
   - Each rule is concrete and has a one-line reason:
     - read all problems first;
     - an order for A to D;
     - when to skip;
     - re-read the constraints before submitting;
     - upsolve versus re-solve.
   - Do not repeat the contests page (`ContestsIsland`). Link to it.
5. **"Read one accepted solution" prompt.**
   - An optional topic-data field, rendered where a problem is marked solved. Find that component first.
   - Three questions: what is different, why it is correct, what you would reuse.
   - Phase 3 onwards.

---

## 7. Phases and PRs

| PR | Content | Notes |
|---|---|---|
| **0** | CI green on `main`; theorem-number regex fixed for two-digit ids; decisions (Section 2) recorded in `PROGRESS.md`; all 10 new curriculum entries added as `draft: true` with their `order` | If the CI `browser` job still fails (`H4-2.yaml`, `L2-1.yaml`), fix it here first, as its own commit. Check that drafts are hidden from navigation and do not break exams or 7.8. |
| **1** | Number theory: new 2.5 (S7, moving `bezout`), Lucas in 2.3 | 2.1 and 2.3 are notes format: insert only |
| **2** | Strings and D&C: 0.6, 0.3, 3.1 (D&C) | notes format for 0.6 and 3.1 |
| **3** | New 3.9 MITM (S2, moving out of 3.1), with the 3.7 look-alike pair | |
| **4** | DP: 3.5 probability, 3.4 LIS deepening, 7.3 convex hull trick and D&C | |
| **5** | Graphs: 4.2 Eulerian and toposort deepening, 4.7 2-SAT, new 4.9 state space (S5) | 4.1 and 4.3 ladders refilled |
| **6** | Bits: 1.7 per-bit deepening, 2.4 cross-link; 1.5 sweep card | notes format: insert only |
| **7** | Phase 5: new 5.5 sweep (S1), new 5.6 Mo (S3) with 5.4's new card, new 5.7 binary trie (S4) with 6.3's new card | one PR per topic if large |
| **8** | New 7.10 rerooting (S6) | 7.1 ladder refilled |
| **9, 10, 11** | New 1.8, 4.8, 7.9 | bank first; Section 13 pipeline and review gate each |
| **12** | Exams, 7.8 recognition set, decision map, counts (58) | |
| **13** | Contest practice (Section 6) | separate PRs for drills and sets if large |
| **14** | Independent verification | fresh agents check every moved and new theorem, unit, card and problem |

Remove `draft: true` from a topic only when it passes its review gate. Each split PR moves the card and deepens it in the same PR, so no topic is left below the limits in Section 1.3.

PRs 1 to 6 can be prepared in parallel by sub-agents, but merge them one at a time and rebase in between, because they touch `glossary.yaml`, bank lists and exams.

### Gate for every PR

```bash
node scripts/validate.mjs
node scripts/keyword_collisions.mjs
node scripts/check_links.mjs
node scripts/check_english.mjs --tone <changed lessons>
node scripts/check_math.mjs <changed lessons>
node scripts/check_code_unchanged.mjs <base> <changed notes lessons>
bash scripts/test_units.sh code
npm test
npm run build
npx astro preview --port 4321 &   # then:
node tests/e2e/render_check.cjs
node tests/e2e/lessons.cjs
```

The PR body lists the following, and ends with the attribution lines your session gives you:
- files changed;
- cards moved (from → to);
- theorems renumbered;
- new theorems and cards;
- problems added, with source and `checked_on`;
- problems that could not be opened (left out);
- "not part of this course" lines changed;
- every count below its floor, with the reason.

---

## 8. Definition of done

- [ ] 58 CP topics; every new topic passed its PLAN.md review gate and is not a draft.
- [ ] Every split topic has at least 4 cards and at least 16 ladder rungs, with theorems, tested units and bugs as in Section 5.1. Every parent still meets Section 1.3.
- [ ] Every deepened card meets its rung count in Section 5.2. Every gap extension has a theorem, tested code, a card and at least 4 rungs.
- [ ] No "not part of this course" line names something now taught. Earlier lessons point forward with "covered in topic X.Y".
- [ ] Saurabh's text and code in the notes lessons are unchanged (insertions only).
- [ ] Drills, volume set, bridge set, contest strategy page and the solution-reading prompt are live, with every problem opened and read.
- [ ] Every gate is green, and CI is green on `main`.

## 9. Left out on purpose (from the outside plan)

Saurabh can bring any of these back.
- **"Grammar" labels, signpost banners and the style audit.** They measure notes format versus template format, not two ways of teaching.
- **Phase gates.** The phase exams already have a pass rule (at least 60%) and a remediation map.
- **Shorter struggle budgets** (8 or 10 minutes in Phases 0–1). This is Saurabh's decision, so it is not in this plan.
- **Mid-course sprint sets with hidden topics.** The Method mixes topics only in exams and 7.8.
- **A separate near-miss case-study library.** Look-alike pairs and kill signals already do this. Each split topic above adds its own look-alike rungs instead.

## 10. When to stop and ask

Stop and write to "Questions for Saurabh" in `PROGRESS.md` when:
- a placement in Section 2 breaks topic order;
- a new topic cannot reach its bank minimum after the search in `FILL_SHORT_TOPICS_PLAN.md`;
- a move would require changing Saurabh's text or code;
- a site cannot be opened from any route.

Continue with other PRs in the meantime.
