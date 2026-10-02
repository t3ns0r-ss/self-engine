# Progress

## Now
- Milestone: B0 (problem bank schemas, scripts, pages, pattern files), done ahead of M0 at Saurabh's request ("problem set first")
- Topic: —
- Branch: claude/problemset-implementation-yja039
- Last completed step: B0 complete. 48 pattern files, bank schema and validation, `scripts/bank_md.mjs`, `/bank` pages
- Next action: wait for the B0 gate (pattern review). Then B1 (Phase 0 and 1 banks), which needs network access to the problem sites (see Blocked)

## Gates
| Gate | Status | Date |
|---|---|---|
| B0 pattern lists review | approved | 2026-10-02 |

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
- Order change: B0 was built before the rest of M0, as you asked. What exists of M0: the Astro + Starlight project, the React integration, the storage module, and the log panel. Still to do for M0: KaTeX, lesson components, the dashboard and other custom pages, the method page, `stress.sh`/`test_units.sh`, CI, and deploy files.
- Git: the session works on the branch `claude/problemset-implementation-yja039`, not the `bank/phase-{n}` and `setup/m0` branches named in the plans. Should I keep that branch name or switch?
- Interpretations made (change any you disagree with):
  - Count and composition rules (bank plan Sections 10.3–10.5) apply only to `status: complete`. `in_progress` files must pass every rule for each problem but may be below the counts.
  - Codeforces tier ranges include both ends, so a rating exactly on a boundary (e.g. 1400 in Phase 1) may sit in either tier. Phase 0 tier 1 is rating 800.
  - Pattern files are also checked for later-topic keywords (PLAN.md Section 4).
  - Topic 7.8 has an empty pattern file, since its problems use `{topic}:{pattern-id}`.
  - Bank pages use `/bank/1-3/` (dash, not dot) so `.3` isn't read as a file extension by web servers.
