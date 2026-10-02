# Progress

## Now
- Milestone: M0 done; B0 done and approved. Next: B1
- Topic: —
- Branch: claude/problemset-implementation-yja039
- Last completed step: M0. All components, pages, method page, validation, test scripts, CI, and deploy files; placeholder topic removed from the site (kept only as a test fixture in `tests/placeholder/`)
- Next action: B1 (Phase 0 and 1 banks) as soon as the problem sites are reachable (see Blocked). First GitHub Pages publish once Saurabh sets Settings → Pages → Source to "GitHub Actions"

## Gates
| Gate | Status | Date |
|---|---|---|
| B0 pattern lists review | approved | 2026-10-02 |
| M0 test deploy | changed to GitHub Pages (server unreachable); waiting for Pages to be enabled in repo settings | 2026-10-02 |
| B1 spot-check | not started | |

## Saurabh is studying
- Topic: —

## Topics
| id | status | merged commit |
|---|---|---|

## Bank
| topic | status | practice | reserved |
|---|---|---|---|
| all 48 | patterns written, no problems yet | 0 | 0 |

## Scope notes for current topic
- Allowed: —
- New: —
- Forbidden keywords: —

## Blocked
- B1 problem collection: this cloud environment's network policy denies codeforces.com, atcoder.jp, cses.fi, leetcode.com and kenkoooo.com (checked with curl and WebFetch on 2026-10-02). PLAN.md Section 0.1 and bank plan Section 7.3 forbid filling any problem field from memory, so no problems were added. Fix: allow those hosts in the environment's network settings, or run B1 somewhere they're reachable.

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
  - Count and composition rules (bank plan Sections 10.3–10.5) apply only to `status: complete`. `in_progress` files must pass every rule for each problem but may be below the counts.
  - Codeforces tier ranges include both ends, so a rating exactly on a boundary (e.g. 1400 in Phase 1) may sit in either tier. Phase 0 tier 1 is rating 800.
  - Pattern files are also checked for later-topic keywords (PLAN.md Section 4).
  - Topic 7.8 has an empty pattern file, since its problems use `{topic}:{pattern-id}`.
  - Bank pages use `/bank/1-3/` (dash, not dot) so `.3` isn't read as a file extension by web servers.
