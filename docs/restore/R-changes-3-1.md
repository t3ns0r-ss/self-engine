# Phase R: lines rewritten in lesson 3.1 (plain English pass)

Each row: the line of the note as imported (start of line) => the new line.

| # | Before | After |
|---|---|---|
| 1 | Function jab khud ko hi call kare toh recursion. Us recursion se brute force karo (saare options try | A function that calls itself is recursion. Doing brute force with that recursion (try all the option |
| 2 | Bina base case ke recursion kabhi rukti nahi. | Without a base case the recursion never stops. |
| 3 | Naya call aaya toh push, return hua toh pop. Last in, first out. | A new call is pushed on the stack and a returning call is popped. Last in, first out. |
| 4 | Easy one first. `f(3)`: dekho, call stack me kya hota hai. Print `Hi, n` pehle, phir `f(n-1)`. | Easy one first. Look at `f(3)` and see what happens on the call stack. It prints `Hi, n` first and t |
| 5 | Stack bharta jaata hai, program crash (stack overflow). | The stack keeps filling up and the program crashes (stack overflow). |
| 6 | Har node = ek call, left child pehle chalega. | Every node is one call, and the left child runs first. |
| 7 | - Same subproblem again and again → that is the hint for DP (dynamic programming, remember the answe | - The same subproblem coming again and again is the hint for DP (dynamic programming: remember the a |
| 8 | Divide & Conquer ka code yaha nahi hai (problem ko aadha karo, dono half solve karo, merge karo). Ba | There is no code for Divide and Conquer here (split the problem in half, solve both halves, merge th |
| 9 | Note: tail recursion matlab recursive call ke baad kuch bhi karna baaki na ho, uska result seedha re | Note: tail recursion means nothing is left to do after the recursive call, and its result is returne |
| 10 | Isi cheez ko backtracking me "revert" ke liye use karenge (place, recurse, revert). | Backtracking uses exactly this for the "revert" step (place, recurse, revert). |
| 11 | Dekho: each call has two children, first `f(i-1)` without i, then push i and `f(i-1)` with i. | Look: each call has two children, first `f(i-1)` without i, then push i and `f(i-1)` with i. |
| 12 | Yahi tree subsets ka backtracking hai (neeche). | This same tree is the backtracking for subsets (below). |
| 13 | Dono "C" alag hain: first C = choice, second C = check. | The two "C"s are different: the first C is Choice, the second C is Check. |
| 14 | Pehle chhota example: 3 positions, 2 choices each. | A small example first: 3 positions, 2 choices each. |
| 15 | Nested loops me depth fixed hota hai (hame code me 3 loops likhne padte). Recursion me depth n input | With nested loops the depth is fixed (we have to write 3 loops in the code). With recursion the dept |
| 16 | Har leaf pe check + decide. | Each leaf costs a check and a decide. |
| 17 | Ek row me ek hi queen aa sakti hai (do aayengi toh woh same row me attack karengi). So I only decide | Only one queen fits in a row (two queens in one row attack each other). So I only decide |
| 18 | Pehla solution [1 3 0 2] second branch me milta hai. | The first solution, [1 3 0 2], is found in the second branch. |
| 19 | Pehle ek world explore karo, wapas aao (revert), phir doosra. | First explore one world, come back (revert), then explore the other. |
| 20 | Dekho: sorted order me pehle saari permutations jo A se shuru hoti hain (6), phir B wali (3), phir C | Look: in sorted order, first come all the permutations that start with A (6), then those that start  |
| 21 | Matlab at k = 3 the big square | That means at k = 3 the big square |
| 22 | n = 40 is already 33 crore calls. | n = 40 is already 331,160,281 calls (about 330 million). |
| 23 | TC: (#choices)₁ × (#choices)₂ × ...... × (#choices)ₙ × (check+decide). | T.C.: (#choices)₁ × (#choices)₂ × ...... × (#choices)ₙ × (check+decide), where #choices means the nu |
| 24 | TC: O(N^N) worst \| O(N! × N) upper bound. | T.C.: O(N^N) worst \| O(N! × N) upper bound. |
| 25 | - Backtracking and the LCCMD framework | - Backtracking and the LCCMD (Level, Choice, Check, Move, Decide) framework |
| 26 | - nCr using Pascal's triangle | - nCr (n choose r) using Pascal's triangle |
| 27 | ## T.C. of backtracking and the 4 problems | ## Time complexity of backtracking and the 4 problems |
| 28 |  |  |
| 29 | \*\* Always first decide how to represent solution & then apply this framework. | Important: always decide first how to represent the solution, and then apply this framework. |
| 30 | ** In most of the cases the choices are same for all levels. | Note: in most cases the choices are the same at every level. |
| 31 | *Recursion tree. \*\* We need to draw recursion tree for almost every problem.* | *Recursion tree. We need to draw a recursion tree for almost every problem.* |
| 32 | \*\* If there are expression that needs to be computed then always put the recursion in the end → th | If an expression has to be computed, always put the recursion at the end. This is called tail recurs |
| 33 | ``` | ![Recursion with its four uses: divide and conquer, backtracking, k-th element, fractals](../../../a |
| 34 | ``` | There are three pegs A, B and C, and n discs on A. Move the n-1 discs above the nth disc to B, then  |
| 35 | ``` | ![Table of the four problems: permutations and subsets, each with distinct or non-distinct elements] |
| 36 | ``` | ![Two queens q1 and q2 on one diagonal of a 5 by 5 board, with the slope rule](../../../assets/notes |
| 37 | ``` | ![Subsets of [3, 1, 2, 5]: for each element two choices, take or not take](../../../assets/notes/3-1 |
| 38 | ``` | The same four problems as before: subsets and permutations, each with unique elements or with duplic |
| 39 | ``` | Take one element of the array, say the third. It is unique, so it has 2 choices: take it or do not t |
| 40 | ``` | Choices for the first character: |
| 41 | ``` | Counting the permutations for the first letter again, A has 5 (tally), B has 3 and C has 3. The 2nd  |
| 42 | ``` | A has 2 permutations and C has 1. The 2nd element lies in the A block, so A must be placed first. |
| 43 | ``` | For this example the numbers of permutations are A: 5, B: 7, C: 10. |
| 44 | ``` | `rec(3,1,3,2)` is 7 moves in total. It splits into `rec(2,1,2,3)` (3 moves), the single move 1→3 (1  |
| 45 | ``` | The three parts are `rec(2,1,2,3)`, `move(1→3)` and `rec(2,2,3,1)`. The 2nd move inside the last par |
| 46 | /* | /* |
| 47 | /* | /* |

Also: `Q:` became `Question:`, `Soln` became `Solution`, 'no. of' became 'the number of', and the three maang.in URL lines inside code comments were removed (decision 3). New figures (generated by `scripts/figures/fig_3_1.py`): fig22_recursion_uses, fig23_hanoi_split, fig24_four_problems, fig25_nqueens_levels, fig26_diagonal_slope, fig27_take_slots. Their ASCII sketches were removed; sketches that only repeated a figure already on the page became one line of text.
