# Proofreading report: 1.3 Two pointers

Read end to end against the raw notes. Line numbers are in `src/content/docs/phase-1/1-3-two-pointers.mdx` at main 516e231.

## What the notes do
The notes name three forms (patterns): **Form 1** variable window that only grows or shrinks one way (the two pointers chase each other), **Form 2** one pointer at each end moving towards each other (container, 3-Sum), **Form 3** two pointers over two different sequences (subsequence, inverted index, matrix min-max). The fixed-length window is a warm-up. The lesson should read in that order.

## Defects, most serious first

1. **The family is counted three ways.** Line 101 says "two patterns", lines 120 and 64 call the fixed window "form 0", line 243 says "three forms". A reader cannot tell if there are two, three or four. Fix: say three forms everywhere; the fixed window is a short warm-up section before Form 1 and is not numbered. (R6)
2. **Theorems appear as 1.3.3, 1.3.1, 1.3.2, 1.3.4, 1.3.5, 1.3.6** (lines 206, 541, 1388…). The first one a reader meets is numbered 3. The fixed window theorem was numbered last in the notes but placed first in the lesson. Fix: number by page order (R11, R12). The heading levels also differ (3 and 4).
3. **"Binary search on every start can be solved with two pointers" is said again and again**: the bullet at 93, the sentence at 95, the figure caption at 99, a note at 512, a code comment at 517 and the lesson's own summary at 1862. One statement, once, in the relation section. The notes repeat it for memory. (R1, R2)
4. **"≥ k is not monotonic" is said at 298, 306, 508, 909, 911 and 1851.** Keep the first, in the section that defines monotonic criteria; the k-distinct problem points back to it. (R1)
5. **Two lists of terms (lines 25 and 50) and a second example inside the opening (line 36).** The opening is 746 words. Keep one terms list; move the second example to the problem that uses it. (R9, R10)
6. **The lesson talks about its sources**: "his note", "the notebook", "the repository", a file path `1-Form/SubarraysWithAtmostKDistincts.cpp`, "checked by running", "checked against a brute force", "new function (not in Fabricator)" (15 errors under C2; lines 57, 120, 494, 537, 761, 1056, 1248, 1321, 1349, 1446, 517, 1328). A blog reader has none of these. (R13, R17)
7. **Headings "Form 2:" and "Form 3:"** (lines 1082, 1425) end with a colon and say nothing; Form 1's heading has a description. Also a jump from level 2 to level 4 at 1177. (R7)
8. **Two listings that the text calls wrong** (1023: gives 2, correct is 3; 1323: never prints the count). The author's code stays unedited, so this is a decision (R16).
9. **Captions that repeat the paragraph above them** at 99, 267, 376, 630, 1226, 1244, 1518. (R2)
10. **Minor**: Form 1 has four "Another way/Variant" side paths between the main problems (R4); Quick revision has 24 bullets (R5); the "common thread of the forms" at the end restates the table near the top (R1).

## What is good and stays
The theorem proofs, the dry runs, the per-form recognition cards, the code, the practice ladder.

## Suggested shape after the fix
What this note covers (one example) → Terms → Relation to binary search (once) → Warm-up: fixed window → Form 1 → Form 2 → Form 3 → Recognition cards → Quick revision → Check yourself → Practice problems.
