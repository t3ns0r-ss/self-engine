# Phase 5 brief: independent verification (read-only, one or two lessons per agent)

You did NOT write these lessons. Your job is to find mistakes. Write ONLY your report file `docs/restore/verify/<topic-id>.md` (create the folder if missing). Do NOT edit lessons, YAML, bank, notes or code. Do NOT run git or `npm run build`. Other verifiers run at the same time.

Read first: LESSON_RESTORE_PLAN.md Section 6 "Phase 5".
Inputs per lesson `<id>` (e.g. 1.4): current lesson `src/content/docs/phase-*/<id>-*.mdx`; inventory `docs/restore/<id with dash>.md`; old lesson `git show 1d76f35:<path>` (for 3.1 use `git show e5d3412:src/content/docs/phase-3/3-1-backtracking.mdx`); Phase 2 version of the lesson `git show <commit before Phase 3>`: find it with `git log --oneline -- <path>`, the commit just before the first "Phase 3" commit; data `src/data/topics/<id>.yaml`, `src/data/bank/<id>.yaml`, `notes/bank/`; code `code/<id>/`.

## Checks
1. **Added rows.** For every inventory row with status `added`: the idea is really on the page where the last column says, it is correct, and it is not repeated elsewhere on the page.
2. **Theorems.** For every theorem: statement correct; recompute the small example numbers by hand or with a quick script (scratch files in your own `mktemp -d`, never in the repo); each proof step follows; the "needs" list is right and does not name a later topic.
3. **Maths.** Pick 30 random formulas on the page. Compare each with the Phase 2 version: meaning unchanged, delimiters correct (`$...$`, `$$...$$`), no raw `^`, `_`, `\le` outside maths, terms formatted consistently. Also run `node scripts/check_math.mjs <mdx>` (must be 0).
4. **Problems.** For each ladder rung and each bank entry: open the statement with `node scripts/fetch_problem.mjs --full <bank id>` (Codeforces: `--brief` only, note it as unread), and check title, link, difficulty, the summary, the twist and every hint. Hints must lead to a solution; the last hint names the property or theorem. The problem must fit this topic and earlier ones only. Check the solution note is correct.
5. **Code.** `node scripts/check_code_unchanged.mjs dd5a440` for his code (report only). Any code added by us (Phase 2 additions under `code/<id>/`): compile with `g++ -std=c++17 -O2` in a temp dir, run, and compare printed output with what the lesson shows.
6. **Figures.** For every image/figure next to a restored or reformatted passage: open the file with the Read tool and compare with the numbers in the text.
7. **Voice.** Plain global English, no Hinglish; his wording kept; no model names; no maang.in.

## Report format (short, factual)
Per check: PASS, or a numbered list of defects with `file:line`, the wrong text, what is right, and a severity (wrong maths / wrong fact / wrong problem / cosmetic). Then "Questions for Saurabh" for anything that is his to decide (contradiction with his notes, unreadable hand drawing). Do not pad: a PASS needs one line.
