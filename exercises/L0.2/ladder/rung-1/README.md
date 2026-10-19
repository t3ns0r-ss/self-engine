# L0.2/ladder/rung-1: An interface with two shapes

## Task
Implement `Shape` as an interface (no Shape object can be made) with `Rect` and `Square` deriving from it, and `total_area` that adds up a list of shapes through the Shape interface only.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- a call through a base reference runs the derived function
- a mixed list is summed through the interface
- `Shape` is abstract
- a shape defined by the caller works with `total_area`

## How to work
    bash scripts/new_attempt.sh L0.2/ladder/rung-1
    # edit work/L0.2/ladder/rung-1/kit.hpp
    bash exercises/L0.2/ladder/rung-1/test.sh work/L0.2/ladder/rung-1
Commit after each rung and tag it (`rung-1`).
On the lab server: `bash scripts/labserver.sh kit L0.2/ladder/rung-1 work/L0.2/ladder/rung-1`
