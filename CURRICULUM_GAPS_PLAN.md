# CURRICULUM_GAPS_PLAN.md: Fill the Missing Topics and Add Contest Practice

**Audience:** an autonomous coding agent working in the `t3ns0r-ss/self-engine` repository.
**Owner:** Saurabh. He reviews every PR and replies "merge" or asks for changes. Do not merge without him.
**Start condition:** start only after the work in `LESSON_RESTORE_PLAN.md` is fully merged, including Phase 5, and `main` is quiet (no open PR or branch still touching lessons). Check `PROGRESS.md` and the open PRs first.

Read these first, in order:
1. `PLAN.md`. Section 13 (per-topic pipeline) and Sections 6 to 9 (lesson template, writing rules, code, problems) apply to every new topic.
2. `PROBLEM_BANK_PLAN.md`. Every new problem follows its collecting rules.
3. `DEVELOPER_GUIDE.md`.
4. `docs/LESSON_STYLE_GUIDE.md`. It applies to the notes-format lessons (0.1 to 2.4 and 3.1).

Every rule there still applies unless this file says otherwise. The most important ones:
- Never write a problem link, title or rating from memory. Open the page and read the statement.
- Strict topic order. A lesson uses only itself and earlier topics, and later topics are named only under "What this topic does not cover".
- Every problem needs a solution note.
- All lesson code is tested.
- Plain global English, terms defined before use, abbreviations expanded on first use.
- Saurabh's own text and code in the notes lessons are never changed.

---

## 0. What Saurabh asked for

1. **Add the topics that are missing.** A review compared the 48 CP topics with what a student needs to reach Codeforces Expert. It found ten gaps.
   - Each of these is listed as "not part of this course" in an existing lesson today:
     - geometry;
     - interactive problems;
     - Eulerian paths;
     - 2-SAT;
     - flow and matching;
     - the convex hull trick and other DP speed-ups;
     - the Chinese remainder theorem (CRT);
     - Lucas's theorem.
   - Divide and conquer is named in 3.1 but has no code. Basic string handling has only the "one-pass string processing" card in 0.3.
   - Probability DP has a single problem in 3.5 (Knight Probability in Chessboard) and no card.
2. **Add the useful parts of an outside "curriculum upgrade" plan** that Saurabh reviewed on 2026-11-13. Keep only:
   - implementation drills;
   - a volume set;
   - a bridge set;
   - a contest strategy page;
   - a "read one accepted solution" prompt.

   Leave out its "grammar" labels, signpost banners, phase gates and shorter struggle budgets (Section 7).

---

## 1. What exists today (checked on 2026-11-13)

| Gap | Today | Evidence |
|---|---|---|
| Geometry | nothing | no lesson mentions cross product or orientation |
| Interactive problems | named as out of scope | 7.5 line 45, 7.7 line 44 |
| Eulerian path or circuit | "not part of this course" | 4.7 line 41 ("Network flow, matchings and Eulerian circuits") |
| 2-SAT | "a Phase 7 idea" | 4.7 line 38 |
| Flow, min cut, matching | "not part of this course" | 4.7 line 41 |
| Convex hull trick, D&C DP | "a different family, not in this course" | 7.3 line 47 |
| Divide and conquer as a method | named, "no code here" | 3.1 lines ~185–189 |
| CRT | "not part of this course" | 2.1 line 46, 2.2 line 49 |
| Lucas's theorem | "not part of this course" | 2.3 line 47 |
| Probability DP | one ladder problem, no card | `3-5.yaml` (`lc-knight-probability-in-chessboard`) |
| Basic strings | "one-pass string processing" card only | 0.3 Section 4.3. 0.6 barely covers `std::string` |

Facts about the data:
- **Topic order comes from the `order` field in `src/data/curriculum.yaml`, not from the id.** The validator checks "later topic" by `order`.
- Learner progress is stored in the browser by topic id. **Never rename or renumber an existing topic id.**
- `48` appears in `PLAN.md` (Section 4 title, registry table), `DEVELOPER_GUIDE.md` (lines 9, 13, 39) and phase index pages. The LLD (low-level design) count of 48 in `validate-design.mjs` is a different track. Do not touch it.
- Topic keywords drive the "later topic" keyword scan. New keywords can create false hits in earlier lessons. Run `node scripts/keyword_collisions.mjs` after adding any.

---

## 2. Decisions (list them in the Phase 0 PR so Saurabh can overrule them)

The review's suggested placements were checked against the repository. Four of them change:

1. **Interactive problems become new topic 1.8, not "1.0".** Most interactive problems at this level are binary search with a query budget, so the topic needs 1.4. An id "1.0" placed before 1.1 could not use it. 1.8 goes at the end of Phase 1, with `requires: ["1.4"]`. Its rating band is Phase 1's band. Problems up to 1800 can go in the bank as "More practice", tagged with a higher tier.
2. **Eulerian path goes into 4.2 (graph structure), not "4.2 graph traversal".** In this repository, 4.1 is traversal and 4.2 is bipartiteness, cycles and topological sort. Degree conditions and Hierholzer's algorithm fit 4.2, which already needs 4.1's depth-first search (DFS).
3. **Divide and conquer is split by level:**
   - The plain method (split, solve halves, merge, with counting inversions by merge sort as the main example) goes into **3.1**. Saurabh's note already names it there and says there is no code.
   - D&C DP optimisation and CDQ (offline divide and conquer over time, which needs a Fenwick tree) go into **7.3**, with the convex hull trick.
   - Nothing goes into 1.4. Binary search is not divide and conquer in the sense taught here.
4. **Basic strings go into 0.6 and 0.3, not a new page:**
   - a `std::string` section in 0.6 (STL toolbox): `substr`, `find`, `reverse`, `+=` cost, comparing, `stoi` and `to_string`, and frequency arrays `cnt[26]`;
   - 2 or 3 ladder rungs on the existing "one-pass string processing" card in 0.3.

   Palindrome checks with two indices belong in 0.3 too.

These placements stay as the review suggested:

5. **Geometry is new topic 4.8**, at the end of Phase 4, band 1600–2000, `requires: ["0.4", "1.1"]` (integer maths and sorting; no graphs needed).
6. **2-SAT extends 4.7**, which already has strongly connected components (SCC).
7. **CRT extends 2.2** (it needs extended Euclid from 2.1 and inverses from 2.2). **Lucas's theorem extends 2.3.**
8. **Probability DP extends 3.5** as a new card. Add `"2.4"` to 3.5's `requires`, because expected value is 2.4.
9. **Convex hull trick extends 7.3.** 7.3's title becomes "DP speed-ups: Fenwick and segment trees, convex hull trick, divide and conquer". Add `"1.6"` to `requires` (the monotone deque version).
10. **Flow and matching is new topic 7.9.**
    - Its `order` is just before 7.8 (Technique recognition), so the mixed recognition set can use its cards.
    - Its band is the Phase 7 band (2000–2400). Problems from 1900 can sit in its first rungs.
    - It requires 4.1 (breadth-first search, BFS) and 4.4 (the cut idea).
    - The order of all later topics shifts by one. Ids do not change.

Result: **51 CP topics** (48 + 1.8, 4.8, 7.9). New topics use the template format (PLAN.md Section 6), because there is no notebook for them. If Saurabh later writes notes for one, it can be converted the way 3.1 was.

---

## 3. How to extend an existing topic

An extension is a **new card with everything a card needs**, added the same way the topic's other cards were added.

**Template-format topics** (0.3, 3.5, 4.2, 4.7, 7.3):
- Section 3: new definitions, also added to `glossary.yaml` and `glossary_added`.
- Section 4: a numbered theorem in the Section 6.4 layout (statement, plain words, tiny instance, proof of at most 8 steps, "This proof needs"), with a tested `TheoremCode` unit.
- Section 5: a new card in the data file (decisive property, constraint shapes with arithmetic, "Recognition in action", positive and negative examples).
- Section 6: a template code unit with a brute force and a generator. `stress.sh` passes 5000 runs.
- Section 7: at least 2 bug catalogue entries for the new card.
- Ladder: at least 4 rungs on the new card, each adding one twist, from the bank.
- Data: 2 drill items, 1 look-alike pair, 2 self-test questions, 1 checkpoint item and 1 decision-map line.
- **Delete the "not part of this course" line** that named it, in this lesson and in any other lesson (Section 1 table). In a lesson that comes **before** this topic, keep the line but change it to "covered in topic X.Y".
- If the topic's ladder and drill counts change, check them against the validator's per-topic rules.

**Notes-format topics** (0.6, 2.2, 2.3, 3.1):
- Add a new `##` section in the notes voice of `docs/LESSON_STYLE_GUIDE.md`, written as Saurabh explains:
  - his kind of small example first;
  - brute force, then the better way;
  - a dry run;
  - functions-only code;
  - cost with the reason;
  - a common mistake.
- The theorem goes inside that section, in the format of `LESSON_RESTORE_PLAN.md` Section 4.2, with maths formatted per its Section 4.3.
- Add the card, rungs and check-yourself data exactly as for template topics. They render through the existing components.
- **Do not change any of Saurabh's existing lines or code.** Only insert. `node scripts/check_code_unchanged.mjs <base> <file>` must pass.
- `check_english --tone`, `check_math` and `check_numbers` must pass.

---

## 4. Content of each addition

The lists below give scope. They do not give problems: collect problems from the platforms under the bank rules. CSES has a Geometry section and graph-flow problems that fit 4.8 and 7.9. Check each one.

### 4.1 Extensions

| Topic | New card | Must teach | Out of scope (name the later topic or say "not in this course") |
|---|---|---|---|
| 0.6 | Strings in C++ | `std::string` operations and their costs (`substr` is $O(k)$, `s = s + c` copies the whole string, `+=` does not), `find` returning `npos`, comparing strings, `cnt[26]` frequency, `stoi` and `to_string` overflow | hashing (6.1), prefix function (6.2) |
| 0.3 | rungs only, on "One-pass string processing" | palindrome check with two indices, counting runs, case conversion | — |
| 2.2 | Chinese remainder theorem | two congruences merged with extended Euclid; coprime and non-coprime moduli (no solution when residues disagree mod the gcd); overflow of the merged modulus (`__int128` or reduce first) | Garner's algorithm for many moduli: not in this course |
| 2.3 | Lucas's theorem | $\binom{n}{r} \bmod p$ for small prime $p$ and huge $n$, by base-$p$ digits; proof sketch via $(1+x)^p \equiv 1 + x^p$; when to use it instead of factorial tables ($n \ge p$) | prime powers (Granville): not in this course |
| 3.1 | Divide and conquer | split, solve halves, merge; recurrence $T(n) = 2T(n/2) + O(n)$ giving $O(n \log n)$ (from 0.2); counting inversions by merge sort; maximum subarray by D&C as a second example | closest pair of points: 4.8 |
| 3.5 | Probability DP | states holding probabilities, transitions multiplied by step probabilities, "forward" and "backward" expectation DP, modular probabilities ($p \cdot q^{-1} \bmod M$, from 2.2) | Markov chains with cycles (Gaussian elimination): not in this course |
| 4.2 | Eulerian path and circuit | degree conditions (undirected: 0 or 2 odd vertices; directed: in/out balance) plus connectivity of the edges; Hierholzer's algorithm, iterative to avoid deep recursion; the "use each edge once" recognition signal and why the Euler tour of a tree (4.5) is a different idea | de Bruijn sequences as a bonus rung only if a fitting problem exists |
| 4.7 | 2-SAT | implication graph ($a \lor b$ gives $\lnot a \to b$ and $\lnot b \to a$); unsatisfiable exactly when $x$ and $\lnot x$ share an SCC; assignment from the SCC topological order; recognising "each item has two options and pairwise conflicts" | — |
| 7.3 | Convex hull trick; D&C optimisation | lines $y = m x + c$ and querying the min over them; monotone slopes and queries with a deque ($O(n)$); Li Chao tree for the general case ($O(n \log n)$, uses 5.3); D&C optimisation when the best split point is monotone; CDQ for offline 3-dimensional counting with a Fenwick tree | Knuth's optimisation and Aliens trick (Lagrangian relaxation): not in this course |

### 4.2 New topic 1.8: Interactive problems

- **Title:** "Interactive problems: flushing, query budgets, adaptive judges". **Requires:** `["1.4"]`.
- **Why this topic exists:** a guessing game where a full scan costs $n = 10^9$ queries but the budget is 30. $\lceil \log_2 10^9 \rceil = 30$ is exactly the budget, so the format tests whether you see the binary search.
- **Teach:**
  - how the format works: your output is the judge's input;
  - flushing (`endl`, `cout.flush()`, `fflush(stdout)`) and why `sync_with_stdio(false)` alone is not a problem but a missing flush gives "Idleness limit exceeded";
  - reading `-1` and exiting at once;
  - counting the query budget against the limit before coding;
  - adaptive judges, where the answer may change as long as it stays consistent with every reply so far, and why that makes randomised guessing fail;
  - testing locally with a small hand-written interactor (a function that plays the judge), so the lesson code is still testable.
- **Theorems:**
  - the adversary lower bound: any strategy needs at least $\lceil \log_2 n \rceil$ yes/no queries for $n$ possible answers;
  - binary search meets it (citing Theorem 1.4.1).
- **Cards:**
  - binary search under a budget;
  - halving with comparisons, where the reply is a comparison rather than yes/no;
  - "ask about pairs" constructive queries, only if the problems found are within Phase 1 topics.
- **Code units:** the interactor pattern needs a test harness. Add a unit format where `tests/` holds a judge function, or test the solution function against a simulated judge in the same file. Document the choice in `DEVELOPER_GUIDE.md`.
- **Platforms:** Codeforces marks interactive problems with the `interactive` tag. Use the API to find candidates, then open and read each one.

### 4.3 New topic 4.8: Basic geometry

- **Title:** "Basic geometry: cross product, orientation, segments, polygons". **Requires:** `["0.4", "1.1"]`.
- **Teach, integers first** (use `long long`, never `double`, unless a problem forces it):
  - vectors and points as pairs;
  - dot product;
  - cross product and its sign as orientation;
  - collinear checks;
  - segment intersection, including touching and collinear overlapping cases;
  - polygon area by the shoelace formula, keeping $2 \times$ area as an integer;
  - point in polygon (ray casting, with the boundary case first);
  - lattice points by Pick's theorem;
  - convex hull by Andrew's monotone chain, which uses sorting from 1.1;
  - closest pair of points as a sweep with a `set`.
- **Bug catalogue:**
  - overflow of the cross product (coordinates $10^9$ give products $10^{18}$, so stay within `long long` and do not add three such products without checking);
  - comparing doubles with `==`;
  - forgetting collinear points on the hull;
  - the boundary case in point-in-polygon.
- **Theorems:**
  - the sign of the cross product gives the turn;
  - two segments intersect if and only if the orientation conditions hold or a collinear overlap exists;
  - the shoelace formula;
  - monotone chain gives the hull in $O(n \log n)$.
- **Out of scope:** half-plane intersection, rotating calipers beyond the diameter of a hull, 3D geometry and circle geometry. Say "not in this course".

### 4.4 New topic 7.9: Flow and matching

- **Title:** "Maximum flow, minimum cut, bipartite matching". **Requires:** `["4.1", "4.4"]`.
- **Teach:**
  - flow networks;
  - residual graph and augmenting paths;
  - Edmonds–Karp first, because it is easiest to prove;
  - then Dinic for speed, with its usual bound stated and the unit-capacity bound noted;
  - the max-flow min-cut theorem, with proof by the residual graph after the last augmentation;
  - recovering the min cut;
  - bipartite matching as unit-capacity flow, and Kuhn's algorithm as the short version;
  - König's theorem: in a bipartite graph, minimum vertex cover equals maximum matching;
  - edge-disjoint and vertex-disjoint paths by splitting vertices.
- **Recognition is the main skill.** Signals and kill signals for "this is a min cut in disguise" (choose a side for each item, pay for separated pairs) and "this is a matching" (assign items to slots, one each). The look-alike pairs must include greedy assignment (7.4) and DP over subsets (3.7).
- **Out of scope:** min-cost flow, flow with lower bounds, general (non-bipartite) matching (blossom), and Hungarian algorithm. Say "not in this course".

### 4.5 For all three new topics

Follow `PLAN.md` Section 13 exactly:
1. scope;
2. theory;
3. cards;
4. templates;
5. bug catalogue;
6. worked examples (6 steps);
7. ladder;
8. drill;
9. look-alike pairs;
10. self-test, checkpoint and decision map;
11. review gate.

Bank first (PROBLEM_BANK_PLAN.md): each new topic needs a bank file in `src/data/bank/` that meets the bank's minimum counts. If a topic falls short after an honest search, mark it `status: short` as the bank plan allows, and say so in the PR.

Also update:
- `PLAN.md` Section 4 registry and title count, and `DEVELOPER_GUIDE.md` counts (48 → 51);
- the phase index pages of Phases 1, 4 and 7, which list their topics;
- the phase exams of Phases 1, 4 and 7: add exam problems for the new cards under the existing exam rules;
- 7.8 Technique recognition: add mixed-set problems using the new cards (7.8 comes after all three by `order`);
- the decision map (handbook) entries for the new cards.

---

## 5. Contest practice additions (from the outside plan, corrected)

Put these in their own data files and pages. **Do not add them as fake topics in `curriculum.yaml`.** The dashboard, exams, sync, validation and keyword scan all loop over topics and expect a lesson and topic data for each.

1. **Implementation drills.**
   - 8 to 12 drills, each a 3- to 5-minute task with a tested code unit in the repository's unit format (`code/<topic>/<unit>/solution.cpp` plus `tests/`, compiled with `-Wall -Wextra -Werror`, passing `bash scripts/test_units.sh code`).
   - Attach each drill to the earliest topic whose ideas it needs, never earlier. Examples:
     - read until end of file (0.1);
     - many test cases with no reset bug (0.1);
     - overflow-safe midpoint (1.4);
     - prefix sums in under 5 minutes (1.2);
     - sort by several keys (1.1);
     - a grid BFS skeleton (4.1, **not** Phase 0).
   - Show them on the topic page under "Check yourself" and on a "Drills" page. Link the Method page's "Implementation bug" mistake category to the Drills page.
2. **Volume set (800–1000).**
   - `src/data/sets/volume-0.yaml` and a page that renders it as a table.
   - Problems are mixed and tagged with the earliest topic they need. Each one is opened and read under the bank rules, with `checked_on` set.
   - Target 40, honest count if fewer. Page text: the aim is speed and clean code, not new ideas.
   - The problem bank validation must cover these files too, so no duplicate collides with a reserved exam problem.
3. **Bridge set, Phase 4 to 5 (1900–2100).**
   - `src/data/sets/bridge-4-5.yaml` with 10 to 15 problems.
   - Each has `have` (the known tool from Phases 0–4) and `new_idea` (the one small new idea, in one line).
   - Every `new_idea` claim is checked by reading the problem and a solution approach. Do not copy editorials.
4. **Contest strategy page.**
   - `src/content/docs/contest-strategy.mdx`, linked from the Method page.
   - Each rule is concrete and has a one-line reason tied to a failure:
     - read every problem before coding;
     - an order for A to D;
     - when to skip (no plan after a fixed number of minutes for the problem's rating);
     - re-read the constraints before submitting;
     - when to upsolve versus re-solve.
   - Check that it does not repeat the existing contests page (`ContestsIsland`). Link to that page instead of copying it.
5. **"Read one accepted solution" prompt.**
   - An optional field in topic data, rendered by the component that shows after a problem is marked solved. Find it first. Add one only if none exists, with an e2e test.
   - Three questions: what is shorter or different, why it is correct, and what you would reuse.
   - Turn it on for Phase 3 onwards.

---

## 6. Phases and PRs

| PR | Content | Notes |
|---|---|---|
| **0** | CI green on `main`; decisions from Section 2 recorded in `PROGRESS.md`; curriculum entries for 1.8, 4.8 and 7.9 added as `draft: true` (if the schema's `draft` flag hides them from navigation) | Check the CI `browser` job first. It failed on `H4-2.yaml` and `L2-1.yaml` before. If it still fails, fix it here as its own commit. |
| **1** | Extensions: number theory (2.2 CRT, 2.3 Lucas) | Notes format, so insert only |
| **2** | Extensions: strings and D&C (0.6, 0.3, 3.1) | 0.6 and 3.1 are notes format |
| **3** | Extensions: DP (3.5 probability, 7.3 convex hull trick and D&C optimisation) | 7.3 title and `requires` change |
| **4** | Extensions: graphs (4.2 Eulerian, 4.7 2-SAT) | Remove the 4.7 "not part of this course" lines |
| **5** | Bank files for 1.8, 4.8 and 7.9 | Bank first, per PROBLEM_BANK_PLAN |
| **6, 7, 8** | Topic 1.8, then 4.8, then 7.9, one PR each, through PLAN.md Section 13 including its review gate | Remove `draft: true` when the topic passes its gate |
| **9** | Exams, 7.8 recognition set, decision map and count updates for the new cards | |
| **10** | Contest practice additions (Section 5) | Separate PRs for drills and sets if large |
| **11** | Independent verification | Fresh agents that did not write the work check every proof, every code unit and every problem link and summary |

PRs 1 to 4 can be prepared in parallel by sub-agents. Merge them one at a time and rebase in between, because they touch shared files (`glossary.yaml`, bank lists).

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
- new theorems and cards;
- problems added, with source and `checked_on`;
- problems that could not be opened (they are left out);
- "not part of this course" lines changed;
- any count below its floor, with the reason.

---

## 7. Left out on purpose (from the outside plan)

Do not add these. Each one either duplicates something the site has or contradicts the Method. Saurabh can bring any of them back.
- **"Grammar" labels** (invariant-first or derivation-first), the signpost banner and the style audit. The difference they measured is the notes format versus the template format, not two kinds of teaching.
- **Phase gates.** The phase exams already have a pass rule (at least 60%) and a remediation map.
- **Shorter struggle budgets** (8 or 10 minutes in Phases 0–1). The Method sets 20 minutes, and 30 to 45 from Phase 2. Changing this is Saurabh's call, not part of this plan.
- **Sprint sets with hidden topics mid-course.** The Method mixes topics only in exams and in 7.8. Timed practice is covered by the exams and the volume set.
- **Near-miss case studies** as a separate library. The look-alike pairs and kill signals on every card already do this. Add better look-alike pairs if a topic is thin.

## 8. Definition of done

- [ ] 51 CP topics. 1.8, 4.8 and 7.9 pass their PLAN.md review gates and are not drafts.
- [ ] Each extension has a theorem with proof and tested code, a card, at least 4 ladder rungs, drill and check-yourself items.
- [ ] No "not part of this course" line names something now taught. Earlier lessons point to the new topic instead.
- [ ] Saurabh's text and code in the notes lessons are unchanged (insertions only).
- [ ] Drills, volume set, bridge set, contest strategy page and the solution-reading prompt are live, and every problem in them was opened and read.
- [ ] Every gate in Section 6 is green, and CI is green on `main`.

## 9. When to stop and ask

Stop and write to "Questions for Saurabh" in `PROGRESS.md` when:
- a placement in Section 2 turns out to break topic order (a needed idea is in a later topic);
- a new topic cannot reach its bank minimum;
- an extension would need a change to his text or code;
- a site cannot be opened from any route.

Continue with other PRs in the meantime.
