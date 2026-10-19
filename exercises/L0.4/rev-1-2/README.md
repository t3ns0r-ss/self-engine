# L0.4/rev-1-2: Redraw a sequence with a failure branch

## Task
`sequence.mmd` shows the successful refund. The code also fails when the payment id is unknown. Redraw it so that it shows both runs the test records (`ok` and `not_found`).

## Files
`starter/sequence.mmd` is the happy-path diagram. The code is `tests/model.hpp`.

## Acceptance tests (in words)
- the successful refund is an allowed path
- the unknown-id run is an allowed path and stops after the lookup
- no path has a call that neither run made

## How to work
    bash scripts/new_attempt.sh L0.4/rev-1-2
    # edit work/L0.4/rev-1-2/sequence.mmd
    bash exercises/L0.4/rev-1-2/test.sh work/L0.4/rev-1-2
The checker prints one line for each difference between your drawing and the code. Preview a diagram at mermaid.live or in any Mermaid-aware editor.
On the lab server: `bash scripts/labserver.sh kit L0.4/rev-1-2 work/L0.4/rev-1-2`
