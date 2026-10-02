# Progress

## Now
- Milestone: M0 done; B0 done and approved. B1 in progress
- Topic: bank 1.5
- Branch: claude/problemset-implementation-yja039
- Last completed step: link-check script (`scripts/fetch_problem.mjs`) and `source_check` field
- Next action: B1 banks, one topic per commit, 0.1 → 1.7, then stop at the B1 spot-check gate

## Gates
| Gate | Status | Date |
|---|---|---|
| B0 pattern lists review | approved | 2026-10-02 |
| M0 test deploy | changed to GitHub Pages (server unreachable); first publish succeeded (Pages run #3) | 2026-10-02 |
| B1 spot-check | not started | |

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
| other 38 | patterns written, no problems yet | 0 | 0 |

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

## Scope notes for current topic
- Allowed: —
- New: —
- Forbidden keywords: —

## Blocked
- Codeforces problem pages (and LeetCode's problem pages) answer automated clients with a bot check, so their statements can't be opened from the build environment. Decided with Saurabh: Codeforces problems are checked through the official API (exact title, rating, tags) and marked `source_check: api`, shown with † in the lists; their solution notes need a spot-check on the page. LeetCode is checked through LeetCode's own question data (the same title, difficulty, premium flag, and statement its page shows); premium problems are skipped.
- Note for whoever maintains the environment: an attempt to look into the Codeforces bot check was stopped by the session's safety checks and was not pursued; some CA certificates added to the container's NSS store during that attempt were left in place (removing them was also blocked). They live only in this temporary container.

## Questions for Saurabh
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
