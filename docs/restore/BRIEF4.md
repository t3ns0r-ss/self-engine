# Phase 4 brief: research the problems, remove maang.in (one or two lessons per agent)

Write files only. Do NOT run git, `npm run build`, or any script that edits other files. Other agents work on other lessons at the same time; touch only the files of YOUR lessons:
- `src/content/docs/phase-N/<lesson>.mdx` (only the `## Practice problems` section, plus maang.in mentions elsewhere in the body, plus the one maang.in URL line in the 1.3 code comment)
- `src/data/topics/<id>.yaml` (the `problems:` list: ladder rungs)
- `src/data/bank/<id>.yaml` and `notes/bank/<id>.md` (bank entries and their solution notes)
Read first: LESSON_RESTORE_PLAN.md Sections 2 (decisions 3 to 5), 4.4 and 6 "Phase 4"; PROBLEM_BANK_PLAN.md Sections 6 and 7.

## Sources (checked this session)
- Reachable: AtCoder, CSES, LeetCode, Codeforces (title, rating, tags through the official API only; the statement page is behind a bot check, so set `source_check: api` for Codeforces).
- Not reachable: poj.org. Not allowed as a bank source: SPOJ, HackerRank, POJ (the schema allows only codeforces, atcoder, cses, leetcode). A raw-list problem from another site is dropped from the lesson; list it in your report as "dropped: source not in bank".
- Open a problem with `node scripts/fetch_problem.mjs --full <id>` (ids look like `cses-1068`, `ac-abc300_c`, `lc-two-sum`, `cf-4A`; for Codeforces `--brief` only). Read the statement. Never write a title, link or difficulty from memory. Never copy statement text into the repository.

## Task per lesson
1. **maang.in.** Remove every maang.in link and mention from the lesson: the raw practice list, body text, and the URL line in his code comment (1.3 only; this is the only allowed edit to his code, and `node scripts/check_code_unchanged.mjs dd5a440` must still pass). Where body text says a file "is a problem from maang.in", reword to a plain description ("a problem about ...") without the site name; keep the rest. `grep -n maang <your files>` must print nothing.
2. **Collect his non-maang problems** from the raw link list (and from the body). Many are already in the bank (match by URL). For each one NOT yet in `src/data/bank/<id>.yaml`:
   1. Open it and read the statement (Codeforces: API brief only).
   2. Confirm it fits this topic and earlier topics only. If it needs a later topic, drop it and report which topic.
   3. Add a bank entry (copy the field layout of the neighbouring entries: id, source, title, url, difficulty, tier, tier_basis, pattern (an id from `src/data/bank/patterns/<id>.yaml`), set: practice, reserved_for: null, lookalike_of: null, techniques, checked_on = today's date 2026-11-11, and `source_check: api` for Codeforces) and a solution note in `notes/bank/<id with dot>.md` in the same format as the existing notes (budget, idea, techniques, "Needs this topic because", tier reasoning).
   4. If it adds a twist the ladder does not yet have for its card, insert it as a ladder rung in `src/data/topics/<id>.yaml` (renumber `rung` so each rung adds exactly one new twist) with `role: ladder`, `card`, `rung`, `twist`, `summary`, `hints`. Otherwise it stays in the bank as "More practice" (it shows automatically).
   Problems that his worked examples solve in the body keep their inline link in the body.
3. **Gaps left by maang.** For each removed maang problem, say what idea it practised (read the lesson text around the list). If that idea now has no problem in the ladder or bank, find ONE free problem for it (AtCoder, CSES, Codeforces or LeetCode) and process it as in step 2. Otherwise just remove it. Never invent a problem: only add one you opened.
4. **Review the existing ladder rungs** of your lessons: re-open each problem (`fetch_problem --brief` is enough for Codeforces; read the statement for the others), check the summary matches the statement, the hints lead to a solution and the last hint names the property or theorem, rung order rises one twist at a time. Fix what is wrong. Rewrite summaries and hints into the lesson voice: short sentences, maths in `$...$` (`$n \le 2 \cdot 10^5$`), code names in backticks (the YAML text goes through `src/lib/mathText.ts`; a literal dollar is `\$`). `node scripts/check_math.mjs --yaml <id>` must print 0.
5. **Replace the raw list.** In the MDX, `## Practice problems` becomes one intro line, then `<Ladder topic="<x.y>" />` (keep exactly one such component and keep this heading as the last `##` heading). Delete the `### Problem ladder` sub-heading if present, so the page does not show the ladder twice. Floors: every card at least 3 rungs; ladder plus More practice at least 12 problems (already met; do not lower). If something stays short, report the honest number.

## Rules
- Plain global English, no Hinglish. His code and his statements are never changed. No model names anywhere.
- Never delete a bank entry that a theorem, drill, lookalike, self-test or checkpoint references (`grep -rn <id> src/data`); if you must drop an entry, remove all references to it too.
- Check your work: `node scripts/check_math.mjs <mdx>`, `node scripts/check_math.mjs --yaml <id>`, `node scripts/check_english.mjs --tone <mdx>` (if it takes a path; otherwise run without args and read your lines only), `node scripts/check_code_unchanged.mjs dd5a440 2>&1 | tail -3`, and make sure YAML parses: `node -e "require('yaml').parse(require('fs').readFileSync('<file>','utf8'))"`.
- Do not run `npm run build` (the main session does). You may run `node src/lib/validate-topics.mjs` style validation only if it is read-only; if unsure, skip.
- Report (short): per lesson a table: kept from his notes (already present / added), added to fill maang gaps, dropped with reason (source, later topic), unverified (Codeforces api-only, anything you could not open), rungs rewritten or fixed, and the exact `grep maang` result.
