# L0.4/ladder/rung-3: Draw one request as a sequence

## Task
Draw the sequence diagram of one `Editor::save` call in `sequence.mmd`: the participants are `Test`, `Editor`, `Document`, `Storage` and `Notifier`. Show each call between objects once, in the order it happens, with the function name as the message. The code is in `tests/model.hpp`; the test runs it and records the calls it really made.

## Files
`starter/sequence.mmd` holds only the first line. Mermaid sequence arrows: `A->>B: name` is a call from A to B. A dashed arrow `B-->>A: text` is a return and is not compared.

## Acceptance tests (in words)
- every call in the recorded run is an arrow of the diagram, in the same order
- the arrow goes from the object that makes the call to the object that receives it
- the diagram has no call that the run did not make

## How to work
    bash scripts/new_attempt.sh L0.4/ladder/rung-3
    # edit work/L0.4/ladder/rung-3/sequence.mmd
    bash exercises/L0.4/ladder/rung-3/test.sh work/L0.4/ladder/rung-3
The checker prints one line for each difference between your drawing and the code. Preview a diagram at mermaid.live or in any Mermaid-aware editor.
On the lab server: `bash scripts/labserver.sh kit L0.4/ladder/rung-3 work/L0.4/ladder/rung-3`
