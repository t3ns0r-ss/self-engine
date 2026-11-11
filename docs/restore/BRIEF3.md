# Phase 3 brief: format maths and terms (one lesson per agent)

You format ONE lesson: its MDX file and its topic YAML (src/data/topics/<id>.yaml). Write files only. Do NOT run git, build, or any script that edits other files. Other agents work on other lessons at the same time; touch only your two files.

Read first: LESSON_RESTORE_PLAN.md Section 4.3 (the conversion table and rules).

Rules:
- Fix every finding of `node scripts/check_math.mjs <your.mdx>` and `node scripts/check_math.mjs --yaml <id>` (id like 1.4). Both must print 0.
- Convert plain maths in prose to `$...$` (KaTeX). In YAML strings `$...$` is rendered by src/lib/mathText.ts; a literal dollar is `\$`. Code names stay in backticks, never inside maths; multi-letter names inside maths use `\text{}`.
- In MDX a `<` inside `$...$` needs a space after it. No `\{` `\}` import escapes. Derivations over several lines become display maths ($$ on its own lines, blank lines before and after).
- Lines in "T.C. = O(n)" style: `T.C. = $O(n)$`. Bullet lists of cost/trace lines stay bullets.
- NEVER change a number, an operator, or the order of terms. NEVER edit code blocks, inline code, or his code in any way. Never change words other than to wrap maths. Plain global English, no Hinglish.
- Headings, figure captions and image alt text cannot render KaTeX: reword them with words (e.g. "n log n") only if check_math flags them; check_math already skips headings.
- Bold only where a term is defined; later uses plain. Library/function names in code font. Expand an abbreviation on first use per page (T.C. = time complexity, S.C. = space complexity) only if not already expanded.
- Do not make a card id, such as an id used in a YAML `card:` field, visible as page text.
- Do not touch frontmatter, imports, component tags or YAML keys that are ids (id, card, url, topic, problem, answer_*, source, difficulty, tool, role, unit, code_unit, format, pattern).
- Work in bulk with small, careful python/sed scripts where the pattern is regular (put scripts in your own scratch dir named after your lesson, not shared), then review by reading diff (`git diff -- <file>`; read only). Check with: `node scripts/check_math.mjs <mdx>`, `node scripts/check_math.mjs --yaml <id>`, `node scripts/check_code_unchanged.mjs dd5a440 2>&1 | tail -3` (must stay passing), and make sure YAML still parses (`node -e "require('yaml').parse(require('fs').readFileSync('src/data/topics/<id>.yaml','utf8'))"`).
- When done, reply with: findings before/after for mdx and yaml, anything you left on purpose and why. Keep it short.
