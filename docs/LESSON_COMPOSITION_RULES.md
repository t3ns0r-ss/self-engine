# Lesson composition rules

Applies to every lesson with `format: notes`. The notes are the author's own study aid. A lesson is a blog written **from** the notes, in the order and the voice of the notes, for a reader who has never seen them. Copying the notes is not the same as composing from them.

Check with `node scripts/check_composition.mjs [--v1 <dir>] <lesson.mdx>`. Rules marked (lint) are checked by that script; the others need a person.

## A. Say each thing once
- **R1 (lint C3, C4).** A statement appears once, where it is first needed. If the notes repeat a line for the author's memory, the lesson keeps one copy. Later places may point back ("as in the flips problem") but may not restate.
- **R2 (lint C3).** A figure caption adds something the text above it does not. If the caption is the same sentence, delete one of them.
- **R3 (lint C9).** One worked trace per idea. The same small array is not re-traced in six paragraphs.
- **R4 (lint C10).** Side paths ("Another way", "Variant") are collected under one "Going further" heading at the end of their section, not spread between the main steps.
- **R5.** Quick revision is a summary, so it is the only place a rule is allowed to be said a second time, and it says it in one line (lint C12 caps its length).

## B. One structure
- **R6 (lint C8).** The family of techniques is counted one way. If the notes have three forms, the lesson has three forms, they are named the same way in the opening, the table, the headings, and Quick revision. A fixed window is a special case of one of the forms, or a short section before the forms; it is never "form 0".
- **R7 (lint C5).** A form heading says what the form is: "Form 2: two pointers moving towards each other". No trailing colon. No skipped heading level.
- **R8 (lint C7).** Sections follow the order of the notes. If the lesson moves a section, the reason is a prerequisite, and the move is recorded in the lesson's change note.
- **R9 (lint C13).** The opening is: what the topic is, one motivating example, the terms. About 350 words at most. A second example belongs in the section where it is solved.
- **R10 (lint C6).** One list of terms, near the top. One contents list, and every item of it matches a heading.

## C. Numbers and references
- **R11 (lint C1).** Theorems are numbered 1, 2, 3 … in the order they appear on the page, with no gaps. A theorem is stated before it is cited. All theorem headings are at the same level.
- **R12.** When a lesson is renumbered, the matching `code/<topic>/<unit>/` folder, `TheoremCode unit=`, the `theorems` list in the topic YAML and every `Theorem x.y.z` mention elsewhere (other lessons, bank, cards) move together. Learner progress is keyed by topic id, so it is not affected.

## D. The reader never sees the machinery
- **R13 (lint C2).** No "his note", "the notebook", "the repository", "Fabricator", "form 0", "checked by running", "checked against a brute force", file paths the reader cannot open, or "new function (not in Fabricator)". Say the fact, not where it came from. Example: replace "Checked against a brute force: 7" with "The answer is 7."
- **R14.** The author's name, his mentor's name and the course name do not appear in prose. (Names used as data inside a problem are fine.)
- **R15.** Constants the lesson relies on are defined where they are first used in a code block, not described as "a constant of the repository".

## E. Code and correctness
- **R16 (lint C11).** A listing that the text then calls wrong ("this gives 2 but the correct answer is 3") is not shown as is. The author's code is never edited, so the options are: show it in a block labelled "A common slip" with the trace that breaks it, followed by a corrected function written beside it, or leave it out of the lesson and keep it only in `code/`. Which one is a decision for the author, once, and then it applies everywhere.
- **R17.** Every dry run in the text is produced by running the code, and the output is pasted. The lesson does not say that it was.

## F. Voice (existing rules, unchanged)
Plain English, terms defined before use, abbreviations expanded on first use, code as functions only, problem statements in multi-line comments without leading asterisks, `check_english.mjs --tone` clean.

## Order of work for a fix
1. Fix the structure (R6–R10, R8). 2. Remove repeats (R1–R5). 3. Renumber theorems (R11, R12). 4. Remove machinery talk (R13–R15). 5. Handle wrong listings (R16). 6. Re-run `check_composition.mjs`, `check_english.mjs --tone`, `check_code_unchanged.mjs`, `validate.mjs`, `check_links.mjs`, and read the result once from top to bottom.
