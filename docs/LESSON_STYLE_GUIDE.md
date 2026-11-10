# Lesson style guide (notes-format lessons)

One page. It applies to the 14 lessons converted from the handwritten notebooks. Every rule has a lint behind it where possible.

## 1. Plain global English
- Write for a reader anywhere in the world. No Hinglish. `node scripts/check_english.mjs` enforces this.
- Short sentences. One idea per sentence. Prefer "so" and "because" over arrows when the arrow hides the reason.
- Keep the author's statements. Tidy only spelling, punctuation and shorthand. Never change the meaning, a formula, a number or his code.

## 2. Rewriting note shorthand
| In the notes | In the lesson |
|---|---|
| `HW:` | "Try this yourself:" |
| `Ques:` | "Question:" |
| `# of x` | "the number of x" |
| `TC` / `SC` | "T.C. (time complexity)" / "S.C. (space complexity)" on first use, then "time" / "space" or the O(...) itself |
| `Idea is always same` | say what the idea is, in one sentence |
| `->` between steps | a sentence, unless it is a real implication in maths |
| ASCII sketch in prose | a generated figure with a one-line caption |
Run `node scripts/check_english.mjs --tone <files>` to find what is left.

## 3. When to define a term
Define it the first time it appears, in one line, before it is used. Expand every abbreviation on first use (T.C., TLE, DS, BIT, nCr). The "Terms used in this lesson" list at the top is for terms used more than once; a term used once is defined in the sentence.

## 4. Shape of a worked example
Always in this order:
1. His example, as written in the notebook.
2. The idea, in two or three sentences, why it works.
3. A trace (dry run) on a small input, step by step.
4. The code, functions only, with a source comment when it comes from the Fabricator repo.
5. Cost: T.C. and S.C. with the reason.
6. A common mistake or edge case, if one exists.
Add more examples from the first improved version only when the section is still thin against its length target.

## 5. Section shape
`## What this note covers` (with terms) → topic sections → `## Quick revision` → `## Practice problems` (last, links only, at least 8; if a topic honestly has fewer, keep the honest number and say so in the PR).

## 6. Code
- His code is never edited. A diff check proves it. Corrected versions come back as new functions with a one-line reason.
- Functions only. No `main`, no `#include`.
- Problem statements go in multi-line comment blocks, no leading asterisk on each line.

## 7. Figures
Generated figures live in `src/assets/notes/<topic-id>-<slug>/`. Every figure has alt text and a one-line caption. Verify the picture against the numbers in the text.

## Lint summary
- `node scripts/check_english.mjs [--tone] <files>`: Hinglish, shorthand, ASCII sketches.
- `node scripts/check_depth.mjs [--report]`: prose length against `scripts/lesson_targets.json`, and sections with code but no trace, cost or mistake line.
- Existing: `check_rewrite.mjs`, `validate.mjs`.
