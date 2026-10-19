# L0.4/cp-1: Draw and verify the diagrams of a room-booking codebase

## Task
Time-box: 40 minutes. The code in `tests/booking.hpp` books meeting rooms. Draw its class diagram in `diagram.mmd` (the six relationships between the seven classes) and the sequence diagram of `Scheduler::book` in `sequence.mmd`, with the booked run and the conflict run as the two paths of an `alt`. Add `DECISIONS.md`: two sentences on which relationships you drew as ownership and why, and one on what the sequence shows that the class diagram cannot.

## Files
`starter/` has the first line of each diagram. The test runs `tests/model.cpp`, which uses the real code, and records the calls it makes in two runs.

## Acceptance tests (in words)
- every class is in the class diagram, with every relationship of the code (`*--`, `o--`, `<|..`) and none other
- the booked run (free, add, send) is an allowed path of the sequence
- the conflict run (free, then the failure) is an allowed path of the sequence
- the sequence allows no call that neither run made

## How to work
    bash scripts/new_attempt.sh L0.4/cp-1
    # edit work/L0.4/cp-1/diagram.mmd sequence.mmd DECISIONS.md
    bash exercises/L0.4/cp-1/test.sh work/L0.4/cp-1
The checker prints one line for each difference between your drawing and the code. Preview a diagram at mermaid.live or in any Mermaid-aware editor.
On the lab server: `bash scripts/labserver.sh kit L0.4/cp-1 work/L0.4/cp-1`
