# PROBLEM_BANK_PLAN.md: Build the Complete Problem Bank Up Front

**Audience:** the same autonomous coding agent that follows `PLAN.md`, in the same repository.
**Purpose:** before any lessons are written, collect every problem the programme will use, for all 48 topics, organised by topic and by difficulty tier, with links checked and topic-fit proven. Lessons (PLAN.md) then draw from this bank instead of sourcing problems one topic at a time.

Read this whole file and `PLAN.md` Sections 0, 4, and 9 before starting. Where this file and `PLAN.md` overlap, this file governs problem collection; `PLAN.md` governs everything else.

---

## 1. Why a bank, and what changes because of it

**Why:** Saurabh can see the full road ahead, practise by topic and tier as soon as a phase's bank is ready, and lesson writing becomes faster and more consistent because every problem was judged against the same rules in one pass.

**What it means for the rest of the programme:**
1. **Two sets per topic.**
   - **Practice set:** visible to Saurabh immediately. Becomes the lesson's ladder, worked examples, and extra practice.
   - **Reserved set:** hidden until needed. Becomes drills, look-alike pairs, checkpoints, review sets, and phase exams. These must stay unseen, because a drill or checkpoint you've already solved tests memory, not recognition.
2. **Patterns now, cards later.** Recognition Cards are designed when a lesson is written. The bank tags each problem with a provisional **pattern** (a named sub-type of the topic's technique). When the lesson is written, patterns are mapped to cards (merged or split if needed), and twists and hints are written then.
3. **Hints and twists are not part of the bank.** They depend on the lesson's cards and ordering.

---

## 2. Output files

```
src/data/bank/
├── patterns/
│   └── 1-3.yaml             # the topic's pattern list (Section 5)
└── 1-3.yaml                 # the topic's problems (Section 3)
notes/bank/
└── 1.3.md                   # solution note for every bank problem (Section 7.4); never rendered
problem-bank/                # GENERATED readable lists (Section 9.2); never hand-edit
├── README.md                # index: every topic with counts per tier
├── phase-1/
│   └── 1.3-two-pointers.md  # practice set only, grouped by tier, then pattern
└── ...
scripts/
└── bank_md.mjs              # generates problem-bank/ from the YAML (Section 9.2)
```

The site renders the bank too (Section 9.1). The reserved set appears in the YAML only, never in `problem-bank/` and never on the site until unlocked.

---

## 3. Bank file schema: `src/data/bank/{id-dash}.yaml`

```yaml
topic: "1.3"
status: in_progress            # in_progress | complete | short (see Section 11)
problems:
  - id: cf-1234A               # formats exactly as PLAN.md Section 9.1
    source: codeforces         # codeforces | atcoder | cses | leetcode
    title: "Exact Title As Shown On The Page"
    url: "https://codeforces.com/problemset/problem/1234/A"
    difficulty: "1400"         # platform's own value (PLAN.md Section 9.3); CSES "—"
    tier: 3                    # 1–5 (Section 4)
    tier_basis: rating         # rating | contest_letter | judgement
    pattern: count-windows     # a pattern id from patterns/1-3.yaml
    set: practice              # practice | reserved
    reserved_for: null         # reserved only: drill | lookalike | checkpoint | review | exam | later_drill
    lookalike_of: null         # optional: id of a near-identical problem needing a different tool
    techniques: ["1.3", "1.1"] # topic ids the solution note uses
    checked_on: "2026-10-12"
```

Add a Zod schema for this collection in `src/content.config.ts`, alongside the existing ones.

---

## 4. Difficulty tiers

Tiers are relative to the topic's **phase band** [L, H] from `PLAN.md` Section 4 (e.g., Phase 1: L = 1000, H = 1400).

| Tier | Name | Codeforces rating | AtCoder ABC (AtCoder Beginner Contest) | CSES / LeetCode |
|---|---|---|---|---|
| 1 | Warm-up | below L − 200 (Phase 0: Div. 4 A–B, rating 800) | A–B | Easy / introductory; first problems of a CSES section |
| 2 | Easy | L − 200 to L | C | LeetCode Easy–Medium; CSES with high solve counts |
| 3 | Core | L to H | C–D | LeetCode Medium; CSES mid-section |
| 4 | Hard | H to H + 200 | D–E | LeetCode Hard; CSES with lower solve counts |
| 5 | Stretch | H + 200 to H + 400 | E–F | Rarely used |

Rules:
- **Codeforces:** tier from the rating shown on the problem page (`tier_basis: rating`). Unrated problems are not used.
- **AtCoder:** use the problem letter as the primary guide (`tier_basis: contest_letter`); use the AtCoder Problems difficulty value only to order problems within a tier. For ARC (AtCoder Regular Contest) problems, use judgement and record `tier_basis: judgement`.
- **CSES and LeetCode:** judgement based on the platform's label or solve count and on the solution note's complexity (`tier_basis: judgement`).
- When in doubt between two tiers, choose the higher one. A problem placed too early does more damage than one placed too late.
- Within a tier, the generated lists order problems by platform difficulty, then id.

---

## 5. Patterns (do this first for every topic)

Before collecting any problem for a topic, write `src/data/bank/patterns/{id-dash}.yaml`:

```yaml
topic: "1.3"
patterns:
  - id: shrinkable-window
    name: "Shrinkable window"
    description: "Longest/shortest contiguous segment where validity is closed under shrinking."
    precondition: "If [l, r] is valid, every sub-window is valid."
  - id: fixed-window
    name: "Fixed-size window"
    description: "Every window of length exactly k; update incrementally as it slides."
    precondition: "The window's value can be updated in O(1) or O(log n) when one element enters and one leaves."
  - id: count-windows
    name: "Count valid windows"
    description: "Count segments satisfying a monotone condition by counting windows ending at each r."
    precondition: "Same closure under shrinking; the count for a fixed r is r − l + 1."
  - id: opposite-ends
    name: "Opposite ends of a sorted array"
    description: "Pairs with a target sum/difference after sorting; pointers move toward each other."
    precondition: "Sorted order makes the pair condition monotone in each pointer."
```

Rules:
- 3–6 patterns per topic, covering everything the topic's lesson will teach, and nothing from later topics.
- Each pattern has a precondition: the property that makes it work. This becomes the decisive property of a Recognition Card later.
- Patterns stay provisional. Lessons may merge, split, or rename them; when they do, update the bank's `pattern` fields to match.

---

## 6. Composition per topic

### 6.1 Counts

| Set | Minimum | Target | What it feeds |
|---|---|---|---|
| Practice | 20 | 30 | ladder (12–20), worked examples (2–3), extra practice |
| Reserved | 24 | 30 | see 6.3 |

Topic 7.8 (technique recognition) is different: 40 problems, all `reserved`, drawn from across all topics (Section 6.4).

### 6.2 Practice set distribution
- By tier, approximately: tier 1: 15%, tier 2: 25%, tier 3: 30%, tier 4: 20%, tier 5: 10%.
- By pattern: every pattern has at least 4 practice problems, spread over at least 3 tiers.
- By platform: at least two platforms per topic; no single platform above 60% of the practice set. CSES and LeetCode appear mainly in tiers 1–2.
- Prefer classic, widely solved problems for tiers 1–3.

### 6.3 Reserved set allocation (`reserved_for`)
| Purpose | Count | Tiers |
|---|---|---|
| `drill`: this topic's own drill items | 8 | 2–4 |
| `later_drill`: distractors for later topics' drills | 4 | 2–3 |
| `lookalike`: one side of a look-alike pair | 4 | 2–4 |
| `checkpoint` | 3 | 3–4 |
| `review`: three review sets of 3–4 | 10 | review 1: tier 3; review 2: tier 3–4; review 3: tier 4 |
| `exam`: candidates for the phase exam | 2 | 3–4 |

Every pattern must be represented in the checkpoint or review problems at least once.

**Look-alike pairs:** whenever you find two problems with nearly identical statements that need different tools (one from this topic, the other from this or an earlier topic), record both, set `lookalike_of` on each, and put both in `reserved` with `reserved_for: lookalike`. If the partner belongs to an earlier topic, it still lives in this topic's bank file, with `techniques` showing its earlier topic.

### 6.4 Topic 7.8 bank
40 fresh problems covering every phase, with at least 2 per phase and at least 1 per Phase 1–6 topic. Each problem's `pattern` is the pattern id of the topic it actually needs (write it as `{topic}:{pattern-id}`, e.g. `1.3:count-windows`). Tiers 3–5 relative to the Phase 7 band.

---

## 7. Collecting a problem

### 7.1 Uniqueness
Every problem id appears **once** in the whole bank. Before adding, search all bank files for the id.

### 7.2 Which topic owns a problem
A problem belongs to topic T only if **both** hold:
1. **Only allowed techniques:** its solution uses only T and topics earlier than T (by `order`).
2. **Needs T:** without T's technique, no natural solution fits the constraints. A problem fully solvable with earlier topics alone belongs to that earlier topic (or isn't used), because it wouldn't train T.

Exception: a look-alike partner or `later_drill` item intentionally needs an earlier topic; condition 2 doesn't apply to those, and their `techniques` show which earlier topic.

### 7.3 Link checking (every problem)
Exactly as `PLAN.md` Section 9.3: open the page, copy the exact title, take difficulty from the platform, read the full statement and constraints, set `checked_on`. If a page can't be opened after three tries spread over a few minutes, skip it and note it under "Blocked" in `PROGRESS.md`. Never write any field from memory. Never copy statement text into the repository.

### 7.4 Solution note (every problem, before adding it)
In `notes/bank/{topic}.md`:
```markdown
## cf-1234A Exact Title (tier 3, pattern count-windows, set practice)
- Budget: n ≤ 2·10^5 → O(n log n) or better.
- Idea: (2–5 lines, precise enough to implement)
- Techniques: 1.3, 1.1
- Needs this topic because: (one line: why earlier topics alone don't fit the budget)
- Tier reasoning: (one line, especially when tier_basis is judgement)
```
At the end of the file, `## Dropped candidates`: id, title, and reason (e.g., "needs binary search, topic 1.4, later"; "solvable with prefix sums alone, belongs to 1.2"; "unrated").

### 7.5 Where to look
Use the source table in `PLAN.md` Section 9.2. Platform tags and categories help you find candidates; they are never evidence of fit. Gather about twice what you need and keep the cleanest.

Useful systematic routes:
- **Codeforces:** the problemset filtered by tag and rating range for the tier you need.
- **AtCoder:** ABC problems at the right letter; AtCoder Problems' list views help find them by difficulty.
- **CSES:** the section matching the topic, in its listed order.
- **LeetCode:** topic tag pages, Easy and Medium, non-premium only.

---

## 8. Order of work

Build the bank phase by phase, topics in curriculum `order`, because purity and "needs T" depend on what's earlier.

| Milestone | Work | Gate |
|---|---|---|
| **B0** | Bank schemas, `scripts/bank_md.mjs`, site pages (Section 9.1), and pattern files for all 48 topics. | ⏸ Saurabh reviews the pattern lists (they define what each topic teaches). |
| **B1** | Phases 0 and 1 banks | ⏸ Saurabh spot-checks a few topics |
| **B2** | Phase 2 | — |
| **B3** | Phase 3 | — |
| **B4** | Phase 4 | — |
| **B5** | Phase 5 | — |
| **B6** | Phase 6 | — |
| **B7** | Phase 7, including the 7.8 bank | ⏸ Final bank review |

**Position relative to `PLAN.md` milestones:** run B0 and B1 right after M0, and before M1 (the 1.3 exemplar). Continue B2–B7 before M2. If Saurabh prefers lessons sooner, B2–B7 may instead run one phase ahead of the lesson milestones; he decides at the B1 gate.

**Per topic:** patterns already exist from B0 → collect practice set → collect reserved set → write solution notes → check the composition rules (Section 6) → regenerate lists → commit.

**Git:** branch `bank/phase-{n}`; one commit per topic: `bank(1.3): 31 practice, 28 reserved`, with tier and pattern counts in the body. Merge each phase to `main` with `--no-ff` and tag `bank-phase-{n}`. Record progress in `PROGRESS.md` under a new heading `## Bank` (topic, status, practice count, reserved count).

**Session size:** one or two topics per session. Commit after each topic so work can resume.

---

## 9. How Saurabh sees the bank

### 9.1 On the site
- **`/bank`**: all topics with practice counts per tier and the learner's solved counts (from the same `localStorage` progress data as `PLAN.md` Section 10).
- **`/bank/{topic}`**: the practice set as a table grouped by tier, then pattern: id, title (linked), platform badge, difficulty, pattern name, and the learner's status. Status can be set from this page using the same log panel as the ladder.
- Topics without a written lesson show a note: "Lesson coming. You can practise now; pattern descriptions are below." and list the topic's patterns with their descriptions and preconditions.
- **Reserved problems never appear** on these pages. They appear only through the lesson components that use them (drill, look-alikes, checkpoint, reviews, exam), with the same unlock rules as `PLAN.md`.

### 9.2 As files: `scripts/bank_md.mjs`
Reads the bank YAML and pattern files and writes `problem-bank/`:
- `README.md`: table of all topics: phase, topic, practice count per tier, status.
- One file per topic: the topic title, its patterns (name, description, precondition), then practice problems grouped `## Tier 1 — Warm-up` … `## Tier 5 — Stretch`, each a table: id | title (linked) | platform | difficulty | pattern.
- Deterministic output (same input, same files). `npm run build` runs it with a `--check` flag that fails if committed files are out of date.

---

## 10. Validation (add to `src/lib/data.ts`; runs in `npm run build`)

1. Every bank file matches the schema; every `pattern` exists in the topic's pattern file (for 7.8: `{topic}:{pattern-id}` exists).
2. Ids unique across the entire bank and match platform formats and URL formats.
3. Counts meet minimums (Section 6.1) unless `status: short`.
4. Practice set: each pattern has ≥ 4 problems over ≥ 3 tiers; at least two platforms; no platform above 60%.
5. Reserved allocations meet Section 6.3 counts.
6. `techniques` never contains a topic later than the bank file's topic; for non-`later_drill`, non-`lookalike` problems, `techniques` contains the topic itself.
7. Every `lookalike_of` points to an existing problem whose `lookalike_of` points back.
8. Codeforces problems' `tier` matches the rating range for that tier and phase.
9. Every bank problem has a section in `notes/bank/{topic}.md` (check by heading text).

---

## 11. When a topic falls short

Some topics (for example interval DP, digit DP, suffix arrays) may have fewer pure problems than the targets.
1. Search every source in the table, including AtCoder ARC (AtCoder Regular Contest) and older Codeforces rounds.
2. Reduce reserved `exam` and `later_drill` first, then reserved `review` down to 3 per set, then practice toward the minimum.
3. Never relax purity or the "needs T" rule.
4. If still below minimum, set `status: short`, list the gaps in `PROGRESS.md` under "Questions for Saurabh", and continue with the next topic.

---

## 12. Changes to `PLAN.md` when the bank exists

Apply these once B1 is merged:
1. **Step 6 of the per-topic pipeline (PLAN.md Section 13):** choose problems from the topic's bank instead of sourcing new ones.
   - Ladder and worked examples come only from the **practice** set; extra practice problems not used in the ladder are listed under the ladder as "More practice".
   - Drill, look-alike pairs, checkpoint, review sets, and exam problems come only from the **reserved** set (earlier-topic drill items from earlier topics' `later_drill` problems).
   - Map patterns to Recognition Cards; update the bank's `pattern` fields if patterns are merged or split.
   - Write twists and hints then.
   - Add new problems only to fill a gap, following this file's rules, and add them to the bank too.
2. **Topic data files (PLAN.md Section 5)** reference bank problems by id; title, URL, difficulty, and `checked_on` are read from the bank instead of repeated, so there is one source of truth. Update the Zod schemas accordingly.
3. **Solution notes:** the bank notes replace `notes/{topic}.md` from `PLAN.md` Section 9.4.
4. **Before each lesson,** re-open the links of the problems the lesson uses if their `checked_on` is more than 6 months old.

---

## 13. Definition of Done

### 13.1 Per topic
- [ ] Pattern file exists, with preconditions, approved at B0.
- [ ] Practice and reserved sets meet the counts and distribution rules, or `status: short` with reasons recorded.
- [ ] Every problem: link opened, exact title, platform difficulty, `checked_on`, solution note with "needs this topic because".
- [ ] No duplicate ids anywhere in the bank; no later-topic techniques.
- [ ] `npm run build` passes; generated `problem-bank/` files updated; committed.

### 13.2 Whole bank
- [ ] All 48 topics complete or `short` with documented gaps.
- [ ] `problem-bank/README.md` shows every topic.
- [ ] Tagged `bank-phase-{n}` for every phase; final gate set to `waiting`.
