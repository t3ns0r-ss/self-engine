# L0.2/ladder/rung-5: Only one implementation

## Task
Implement `EventCounter` as a concrete class. Do not add a base class or a virtual function: only one implementation will ever exist, and the tests fail if the class is polymorphic.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- a new counter is 0
- `add` takes an amount and defaults to 1
- `reset` goes back to 0
- `EventCounter` is not polymorphic and has no hidden pointer
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.2/ladder/rung-5
    # edit work/L0.2/ladder/rung-5/kit.hpp
    bash exercises/L0.2/ladder/rung-5/test.sh work/L0.2/ladder/rung-5
Commit after each rung and tag it (`rung-5`).
On the lab server: `bash scripts/labserver.sh kit L0.2/ladder/rung-5 work/L0.2/ladder/rung-5`
