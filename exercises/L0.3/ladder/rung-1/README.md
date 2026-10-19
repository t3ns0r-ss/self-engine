# L0.3/ladder/rung-1: A car owns its engine

## Task
Finish `Car`: it holds its `Engine` as a member by value, records `car built` and `car destroyed`, and starts and asks its own engine. The tests check the order of events and that the car is the size of its engine.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- the engine is built before the car and destroyed after it
- each car starts its own engine
- the car is the size of its engine (no pointer)
- a car held by `unique_ptr` destroys its engine

## How to work
    bash scripts/new_attempt.sh L0.3/ladder/rung-1
    # edit work/L0.3/ladder/rung-1/kit.hpp
    bash exercises/L0.3/ladder/rung-1/test.sh work/L0.3/ladder/rung-1
Commit after each rung and tag it (`rung-1`).
On the lab server: `bash scripts/labserver.sh kit L0.3/ladder/rung-1 work/L0.3/ladder/rung-1`
