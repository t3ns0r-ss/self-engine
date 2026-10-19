# L0.2/ladder/rung-4: A hot loop, two ways

## Task
Implement `repeat_static` (resolved at compile time) and `repeat_dynamic` (through the Shape interface). Both return the sum of n calls to `area()`; the tests run 10 million repeats.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- both loops give the same answer
- 0 and 1 repeats
- 10 million repeats
- the dynamic loop follows the derived class
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.2/ladder/rung-4
    # edit work/L0.2/ladder/rung-4/kit.hpp
    bash exercises/L0.2/ladder/rung-4/test.sh work/L0.2/ladder/rung-4
Commit after each rung and tag it (`rung-4`).
On the lab server: `bash scripts/labserver.sh kit L0.2/ladder/rung-4 work/L0.2/ladder/rung-4`
