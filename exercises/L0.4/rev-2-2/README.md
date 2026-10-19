# L0.4/rev-2-2: Spot the wrong arrow in a class diagram

## Task
`diagram.mmd` was drawn from the code in `tests/chat.hpp`, but three of its arrows are wrong. Find them by reading the member declarations, and correct the diagram.

## Files
`starter/diagram.mmd` is the diagram with three wrong arrows.

## Acceptance tests (in words)
- each arrow is the one the member declaration gives
- no arrow is missing and none is extra

## How to work
    bash scripts/new_attempt.sh L0.4/rev-2-2
    # edit work/L0.4/rev-2-2/diagram.mmd
    bash exercises/L0.4/rev-2-2/test.sh work/L0.4/rev-2-2
The checker prints one line for each difference between your drawing and the code. Preview a diagram at mermaid.live or in any Mermaid-aware editor.
On the lab server: `bash scripts/labserver.sh kit L0.4/rev-2-2 work/L0.4/rev-2-2`
