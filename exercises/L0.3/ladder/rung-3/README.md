# L0.3/ladder/rung-3: A square is not a rectangle

## Task
Implement `Square` so that it keeps every promise of a square without deriving from `Rect`: `scaled` builds a new square and `as_rect` converts when a `Rect` is needed.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- side, area and scaling
- `Square` is not derived from `Rect`
- `as_rect` gives a `Rect` that keeps the `Rect` promise
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.3/ladder/rung-3
    # edit work/L0.3/ladder/rung-3/kit.hpp
    bash exercises/L0.3/ladder/rung-3/test.sh work/L0.3/ladder/rung-3
Commit after each rung and tag it (`rung-3`).
On the lab server: `bash scripts/labserver.sh kit L0.3/ladder/rung-3 work/L0.3/ladder/rung-3`
