# L0.4/ladder/rung-2: Draw a class diagram from the code

## Task
Draw the class diagram of the four classes in `tests/recipes.hpp` in `diagram.mmd`, with the right arrow for each pair: `*--` for a part that is owned, `o--` for a part that is only referred to.

## Files
`starter/diagram.mmd` holds only the first line. Mermaid class-diagram arrows: `A *-- B` (A owns B), `A o-- B` (A refers to B), `A <|-- B` (B derives from A), `A <|.. B` (B implements the interface A).

## Acceptance tests (in words)
- every class of the header is in the diagram, and none that is not
- every owned member is drawn with the diamond on the owner's side
- every referred member is drawn with `o--`
- no relationship appears that the header does not have

## How to work
    bash scripts/new_attempt.sh L0.4/ladder/rung-2
    # edit work/L0.4/ladder/rung-2/diagram.mmd
    bash exercises/L0.4/ladder/rung-2/test.sh work/L0.4/ladder/rung-2
The checker prints one line for each difference between your drawing and the code. Preview a diagram at mermaid.live or in any Mermaid-aware editor.
On the lab server: `bash scripts/labserver.sh kit L0.4/ladder/rung-2 work/L0.4/ladder/rung-2`
