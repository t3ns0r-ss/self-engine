# L0.4/ladder/rung-5: A two-class design needs no diagram

## Task
A `Clock` owns the `TimeZone` it was built with; the zone is built with the clock and destroyed with it. Decide whether a diagram is worth drawing, and write `decision.txt` with two lines: `diagram needed: yes` or `no`, and `sentence:` followed by one sentence (25 words at most) that names both classes and says the relationship.

## Files
`starter/decision.txt` has the two labels and no answers.

## Acceptance tests (in words)
- the answer is `no`: two classes with one relationship are described by one sentence
- the sentence names both `Clock` and `TimeZone`
- the sentence has at most 25 words

## How to work
    bash scripts/new_attempt.sh L0.4/ladder/rung-5
    # edit work/L0.4/ladder/rung-5/decision.txt
    bash exercises/L0.4/ladder/rung-5/test.sh work/L0.4/ladder/rung-5
The checker prints one line for each difference between your drawing and the code. Preview a diagram at mermaid.live or in any Mermaid-aware editor.
On the lab server: `bash scripts/labserver.sh kit L0.4/ladder/rung-5 work/L0.4/ladder/rung-5`
