# FILL_SHORT_TOPICS_PLAN.md: Complete Every Topic Marked `short`

**Audience:** the same coding agent, in the same repository.
**Situation:** all 48 topic banks exist. Some have `status: short` because not enough problems met the rules in `PROBLEM_BANK_PLAN.md`.
**Goal:** bring every short topic up to at least its minimum counts, and as close to its targets as possible, using additional sources Saurabh has now allowed.

Read `PROBLEM_BANK_PLAN.md` again before starting. Every rule there still applies (link checking, solution notes, the "needs this topic" rule, uniqueness, reserved-set secrecy) except where this file explicitly changes it.

---

## 1. Sources

### 1.1 Newly allowed (in addition to all sources already allowed)
| Platform | Newly allowed |
|---|---|
| Codeforces | All divisions and contest types: Div. 1, Div. 2, Div. 1 + 2 combined, Educational rounds, Global rounds, and any other rated round in the problemset |
| AtCoder | ARC (AtCoder Regular Contest), AGC (AtCoder Grand Contest), and all ABC (AtCoder Beginner Contest) problems including F and G |
| LeetCode | Hard problems (non-premium only) |

Notes:
- LeetCode labels problems only Easy, Medium, or Hard; there is no "very hard" label. Treat "very hard" as the upper end of Hard. For ordering Hard problems you may use the community difficulty ratings published in the `zerotrac/leetcode_problem_rating` repository on GitHub. They are unofficial; record `tier_basis: judgement` and mention the rating in the solution note.
- Still excluded: Codeforces EDU and Gym problems (need a login), LeetCode premium problems, and AtCoder contests other than ABC, ARC, AGC that were not already allowed.

### 1.2 Rating ceiling per phase
Harder sources make it tempting to add problems far above the learner's level. A problem may be added to a topic only if its difficulty fits that topic's tiers (`PROBLEM_BANK_PLAN.md` Section 4), which caps it at the top of tier 5:

| Phase | Band [L, H] | Highest Codeforces rating allowed (H + 400) |
|---|---|---|
| 0 | 800–1000 | 1400 |
| 1 | 1000–1400 | 1800 |
| 2 | 1400–1700 | 2100 |
| 3 | 1500–1900 | 2300 |
| 4 | 1600–2000 | 2400 |
| 5 | 1800–2100 | 2500 |
| 6 | 1900–2200 | 2600 |
| 7 | 2000–2400 | 2800 |

What this means in practice:
- **Codeforces Div. 1:** mostly Div. 1 A–C, depending on phase.
- **AtCoder ARC:** mostly A–C. **AGC:** mostly A, occasionally B, and mainly for later phases and topic 7.7 (constructive), since AGC problems are often constructive rather than technique-based.
- **LeetCode Hard:** usually tiers 3–5 from Phase 2 onward.
- A problem above the ceiling is never added, even if it fits the topic perfectly.

### 1.3 Tiers for the new sources
- **Codeforces:** tier from the rating, as before.
- **AtCoder ARC and AGC:** contest letters don't map to tiers the way ABC letters do. Use judgement informed by the AtCoder Problems difficulty value and the solution note's complexity; record `tier_basis: judgement` and one line of reasoning in the note. When unsure, choose the higher tier.
- **ABC F and G:** tier 5 for the phases where they fit the ceiling; never below tier 4.
- **LeetCode Hard:** judgement, never below tier 3.

---

## 2. Duplicate traps with the new sources

These are new risks; check every candidate against them.

1. **Codeforces shared rounds.** In parallel Div. 1 / Div. 2 rounds, the same problem appears in both contests under different ids (e.g., Div. 1 A is often Div. 2 C, with the two contests having adjacent ids). Before adding a Div. 1 or Div. 2 problem, open the sibling contest's problem list (adjacent contest id, same date) and check for the same title. If the problem exists under another id anywhere in the bank, skip it. If both ids are new, use the Div. 2 id (it is usually the one learners find) and note the other id in the solution note.
2. **AtCoder shared tasks.** Some older ABC and ARC contests ran together and shared tasks under different task ids (e.g., an ABC C that is also an ARC A). Check titles across ABC/ARC contests held on the same date. Same handling as above.
3. **Same problem, different platforms.** A few classic problems appear on several platforms. Search the bank for the title before adding.

Record every duplicate found in the topic's `## Dropped candidates` list with reason "duplicate of {id}".

---

## 3. Procedure

### Step 1: Shortfall report
Create `bank-fill/SHORTFALL.md` (committed). For every topic with `status: short`, a section:

```markdown
## 3.8 Digit DP (status: short)
| Measure | Now | Minimum | Target | Gap to min | Gap to target |
|---|---|---|---|---|---|
| Practice total | 14 | 20 | 30 | 6 | 16 |
| Reserved total | 17 | 24 | 30 | 7 | 13 |

Practice by tier: T1 2, T2 4, T3 5, T4 3, T5 0 (wanted ≈ T1 15%, T2 25%, T3 30%, T4 20%, T5 10%)
Practice by pattern: count-up-to-n 6, digit-sum-constraint 5, divisibility-mod-state 3 (each needs ≥ 4 over ≥ 3 tiers)
Platforms: codeforces 9, atcoder 5
Reserved by purpose: drill 6/8, later_drill 0/4, lookalike 2/4, checkpoint 3/3, review 6/10, exam 0/2
Reductions applied earlier (PROBLEM_BANK_PLAN.md Section 11): exam 2→0, later_drill 4→0, review 10→6
Original reason marked short: (copy from PROGRESS.md "Questions for Saurabh")
```
Then a summary table at the top listing all short topics and their total gaps. Commit: `bank-fill: shortfall report`.

### Step 2: Priorities
Fill gaps in this order, topic by topic in curriculum `order`:
1. Practice set up to its **minimum**, with every pattern reaching ≥ 4 problems over ≥ 3 tiers.
2. Reserved set up to its **minimum**, restoring purposes that were reduced earlier, in this order: `review` (back to 10), `checkpoint` (must be 3), `drill` (8), `lookalike`, `later_drill`, `exam`.
3. Practice set toward its **target**.
4. Reserved set toward its **target**.

The new sources are mostly harder, so they will mostly fill tiers 3–5. Gaps in tiers 1–2 should be filled from the previously allowed sources (CSES, LeetCode Easy/Medium, ABC A–D, Codeforces Div. 2/3/4 low-rated problems), searched again with fresh queries. If tiers 1–2 genuinely cannot be filled, record that in the topic's report section; do not fill them with harder problems placed in a lower tier.

### Step 3: Search the new sources systematically
For each short topic, and for each pattern with a gap:
- **Codeforces:** problemset filtered by the most relevant tags and by the rating range of the tier you need (never above the phase ceiling). Look through Educational rounds specifically: they often contain clean, single-technique problems in the 1600–2200 range, which suit Phases 3–6. Then Div. 1 + 2 combined, Global, and Div. 1 rounds.
- **AtCoder:** ABC F–G for later phases; ARC A–C; AGC A for later phases and constructive topics.
- **LeetCode:** Hard problems under the topic's tag pages; skip premium.

For every candidate, follow `PROBLEM_BANK_PLAN.md` Section 7 exactly:
1. Check duplicates (Section 2 above) and global uniqueness.
2. Open the page, copy the exact title, take the platform's difficulty, read the full statement and constraints, set `checked_on`.
3. Write the solution note, including "Needs this topic because" and tier reasoning.
4. Apply both ownership conditions: only allowed techniques, and needs this topic. Harder problems usually combine several techniques, so expect to drop most candidates; that is normal and correct.
5. Add to the bank with `set` and `reserved_for` according to the current gaps.

**Candidates that fit a different topic:** if a candidate is pure but belongs to another topic, and that topic is also short, add it there (following all rules). If that topic is not short, list it in `bank-fill/SPARE.md` (id, title, url, owning topic, tier, one-line idea) without adding it. Spare candidates can be used later if lessons need replacements.

### Step 4: Moving problems between sets within a topic
- A practice problem may move to reserved only if Saurabh has **not** logged it. He tracks progress in his browser, so you can't see it: ask in `PROGRESS.md` "Questions for Saurabh" with the list of proposed moves, and wait for his answer before moving any practice problem into reserved.
- A reserved problem may move to practice freely (making a hidden problem visible is safe), but only if the reserved set stays at or above its minimum afterwards.

### Step 5: Pattern problems
If one pattern stays below 4 problems after an exhaustive search, the pattern may be too narrow. Do not change patterns yourself (they were approved at B0). Add a proposal under "Questions for Saurabh": merge it with which pattern, or keep it with fewer problems, and why.

### Step 6: Finish each topic
- Update the bank file and `notes/bank/{topic}.md`.
- If all minimums are met, set `status: complete`. Otherwise leave `status: short` and fill in Section 4's exhaustion record.
- Regenerate `problem-bank/` (`node scripts/bank_md.mjs`), run `npm run build`.
- Update the topic's section in `SHORTFALL.md` with the new counts, and add a line to `PROGRESS.md` under `## Bank fill`.
- Commit: `bank-fill(3.8): +9 practice, +8 reserved, status complete` with tier, pattern, and platform counts in the body.

---

## 4. When a topic is still short after an exhaustive search

A search counts as exhaustive only when, for each pattern with a gap, you have:
- gone through Codeforces problems with the relevant tags across every rating range the phase allows;
- gone through every ABC F–G, ARC A–C, and AGC A problem whose title or tags suggest the technique, or, if that's impractical, at least the 100 most recent contests of each type;
- gone through all non-premium LeetCode Hard problems in the relevant tag;
- re-searched the earlier sources for tiers 1–2.

Record this in the topic's `SHORTFALL.md` section as an **exhaustion record**: what was searched (filters, contest ranges), how many candidates were examined, how many dropped and the main drop reasons.

Then add one item per still-short topic under "Questions for Saurabh", offering these options:
1. Accept the topic as short (lesson ladder uses what exists; fewer extra practice problems).
2. Lower that topic's minimums (state the proposed numbers).
3. Merge a narrow pattern into another (state which).
4. Allow a specific additional source for that topic (name it and why it would help).

Do not apply any of these without his answer.

---

## 5. Lessons already written

If a short topic already has a lesson:
- New practice problems go under the ladder's "More practice" list. Change the ladder itself only to fill a gap in its required counts.
- New reserved problems may fill lesson parts that were below their counts (drill, look-alike pairs, review sets). Never replace a reserved problem that a lesson already shows, because Saurabh may already have seen it.
- Run the topic's full Definition of Done from `PLAN.md` Section 17.1 again after any lesson change.

---

## 6. Validation changes

In `src/lib/data.ts`:
1. Enforce the rating ceiling (Section 1.2) for every Codeforces problem in the bank, not only new ones. Any existing violation is reported in `SHORTFALL.md` for Saurabh rather than removed automatically.
2. Allow `tier_basis: judgement` for ARC, AGC, and LeetCode Hard problems; require it for ARC and AGC.
3. Keep all existing bank checks (`PROBLEM_BANK_PLAN.md` Section 10).

---

## 7. Git and progress

- Branch `bank/fill-short`. One commit per topic (Section 3, Step 6). Merge to `main` with `--no-ff` when every short topic is either complete or has an exhaustion record and a question for Saurabh. Tag `bank-filled`.
- `PROGRESS.md` gets a `## Bank fill` table: topic, status before, status after, practice before → after, reserved before → after, open question (yes/no).
- One to three topics per session; commit after each topic so work can resume.

---

## 8. Review gate

When the branch is merged, set gate "Bank fill review" to `waiting` in `PROGRESS.md`. Saurabh reviews:
- `SHORTFALL.md` summary (before/after counts);
- a sample of new problems from the harder sources, checking that their tiers feel right;
- open questions for topics still short.

Do not start new lesson milestones until the gate is `approved`, unless Saurabh says otherwise in `FEEDBACK.md`.

---

## 9. Definition of Done

- [ ] `SHORTFALL.md` created before any additions, and updated after each topic.
- [ ] Every previously short topic is `complete`, or has an exhaustion record and an open question for Saurabh.
- [ ] Every new problem: duplicate check done, link opened, exact title, platform difficulty, `checked_on`, solution note with "needs this topic because" and tier reasoning, within the phase rating ceiling.
- [ ] No practice problem moved into reserved without Saurabh's confirmation.
- [ ] `npm run build` passes; `problem-bank/` regenerated; merged and tagged `bank-filled`; gate set to `waiting`.
