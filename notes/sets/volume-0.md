# Volume set: solution notes (private, not rendered)

One line per problem: the whole solution, and why the tagged topic is the earliest that gives it. Codeforces statements could not be opened
(`source_check: api`), so those lines are recalled and marked †; the other problems were opened and read on 2026-11-16.
None of these problems is in a topic bank (checked by `src/lib/validate-sets.mjs`).

## Codeforces (†)
- cf-231A Team †: for each line of three 0/1 values add 1 when the sum is at least 2. 0.3: loops and conditions only.
- cf-282A Bit++ †: for each statement check whether it contains `++` or `--` and change x by 1. 0.3.
- cf-158A Next Round †: read k-th score, count scores that are at least it and positive. 0.3.
- cf-50A Domino piling †: answer is floor(M*N/2). 0.4: integer division, parity.
- cf-112A Petya and Strings †: lower-case both words and compare. 0.6: `std::string` operations.
- cf-339A Helpful Maths †: collect the digits, sort, print joined by `+`. 1.1: sorting.
- cf-266A Stones on the Table †: count positions i with s[i] == s[i-1]. 0.3.
- cf-546A Soldier and Bananas †: k * w(w+1)/2 minus n, at least 0. 0.4: formula, small numbers.
- cf-977A Wrong Subtraction †: loop k times, divide by 10 if the last digit is 0, else subtract 1. 0.3.
- cf-734A Anton and Danik †: count 'A' and 'D', compare. 0.3.
- cf-1352A Sum of Round Numbers †: for each non-zero digit print digit times its power of ten. 0.3.
- cf-1760A Medium Number †: print a + b + c - max - min (or sort). 0.3.
- cf-160A Twins †: sort coins descending, take until the taken sum exceeds the rest. 1.5: greedy by largest, after 1.1.
- cf-405A Gravity Flip †: sort the heights ascending. 1.1.
- cf-579A Raising Bacteria †: popcount of x. 1.7.
- cf-1669B Triple †: count values in an array of size n+1 or sort; print a value seen 3 times. 0.6: counting with containers.
- cf-702A Maximum Increase †: one pass keeping the current run length. 0.3.

## AtCoder (read)
- ac-abc300_b: for every (s, t) with s < H and t < W compare A shifted by (s, t) with B; 30 x 30 x 900 is tiny. 0.3.
- ac-abc312_b: slide a 9 x 9 window over the grid and check the 18 + 14 cells; output in row-major order. 0.3.
- ac-abc404_b: try 0 to 3 rotations of S, count cells that differ, add the number of rotations; take the minimum. 0.3.
- ac-abc406_b: product can reach about 10^36 before the check, so use `__int128` or test `product > limit / a`; K up to 18. 0.1: types and overflow.
- ac-abc336_c: write N-1 in base 5 and double every digit. 0.4: base conversion by repeated division.
- ac-abc348_c: map colour to its minimum A, take the maximum over colours. 0.6: `std::map`.
- ac-abc391_c: keep count[nest] and a counter of nests with count >= 2, update on every move. 0.3: arrays.
- ac-abc402_c: for each dish keep how many ingredients are still disliked, for each ingredient the list of dishes using it; decrement and count dishes reaching 0. 0.6: vector of vectors.
- ac-abc385_c: try every first index and every step (harmonic sum over steps), extend while the heights match; about N^2 log N. 0.2: budget from constraints.
- ac-abc390_c: bounding box of the `#` cells must contain no `.`; also all `#` inside it. 0.3.
- ac-abc383_b: H x W <= 100 floor cells, try every pair of cells, count covered floor cells: about 100^3. 0.5: brute force over pairs.
- ac-abc386_c: |len S - len T| > 1 means no; equal lengths allow one mismatch; otherwise skip one character of the longer string and compare. 0.3.

## LeetCode Easy (read)
- lc-fizz-buzz: loop, test 15, 3, 5 in that order. 0.3.
- lc-palindrome-number: negative is false; reverse digits with `% 10` and `/ 10` (use `long long` or compare half). 0.4.
- lc-roman-to-integer: subtract a value when the next symbol is larger, else add. 0.3.
- lc-plus-one: add from the end with a carry; if a carry is left insert a leading 1. 0.3.
- lc-valid-palindrome: two indices skipping non-alphanumerics, compare lower-case. 0.3.
- lc-first-unique-character-in-a-string: count letters in an array of 26, scan for the first count of 1. 0.6.
- lc-relative-ranks: sort indices by score descending and assign the three medals then the place number. 1.1.
- lc-number-of-1-bits: loop `n &= n - 1`. 1.7.

## CSES (read)
- cses-2216 Collecting Numbers: pos[v] = index of v; rounds = 1 + number of v with pos[v] < pos[v-1]. 0.3: arrays.
- cses-2205 Gray Code: print `i ^ (i >> 1)` as an n-bit string for i in 0 .. 2^n - 1. 1.7: XOR and shifts.
- cses-3311 Grid Coloring I: cell (i, j) takes one of two letters chosen by parity of i and j, taking whichever differs from the old letter. 0.3: grids, one pass.
