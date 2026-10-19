# L0.0/ladder/rung-5: A small value that is copied freely

## Task
Implement `midpoint(Point, Point)` for the plain value type `Point`: each coordinate is the integer average of the two inputs, truncating toward zero. `Point` must stay a plain value that is freely copied.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- copies are independent
- passing by value leaves the arguments alone
- midpoint truncates toward zero, including for negative numbers
- a default point is the origin
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.0/ladder/rung-5
    # edit work/L0.0/ladder/rung-5/kit.hpp
    bash exercises/L0.0/ladder/rung-5/test.sh work/L0.0/ladder/rung-5
Commit after each rung and tag it (`rung-5`).
On the lab server: `bash scripts/labserver.sh kit L0.0/ladder/rung-5 work/L0.0/ladder/rung-5`
