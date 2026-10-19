# L0.2/ladder/rung-3: The same promise at compile time

## Task
Implement `STriangle::area`, `area_of` and `total_of` so that any type with an `area()` member works without a base class. A type the tests define themselves must work without editing your functions.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- the triangle rounds down
- `area_of` and `total_of` work for any type with `area()`
- a type defined in the test works unchanged
- a type with no `area()` does not satisfy `HasArea`
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.2/ladder/rung-3
    # edit work/L0.2/ladder/rung-3/kit.hpp
    bash exercises/L0.2/ladder/rung-3/test.sh work/L0.2/ladder/rung-3
Commit after each rung and tag it (`rung-3`).
On the lab server: `bash scripts/labserver.sh kit L0.2/ladder/rung-3 work/L0.2/ladder/rung-3`
