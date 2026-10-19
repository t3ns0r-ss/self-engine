# L0.1/ladder/rung-3: An immutable date range

## Task
Implement `DateRange`, an immutable range with start <= end. `with_start` and `with_end` return a new range; a change that would break the rule throws `std::invalid_argument`. The old range is never altered.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- a range keeps its ends and has a length
- a one-point range is allowed; start after end throws
- `with_start` and `with_end` return new ranges and leave the old one
- a refused change leaves the old range as it was
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.1/ladder/rung-3
    # edit work/L0.1/ladder/rung-3/kit.hpp
    bash exercises/L0.1/ladder/rung-3/test.sh work/L0.1/ladder/rung-3
Commit after each rung and tag it (`rung-3`).
On the lab server: `bash scripts/labserver.sh kit L0.1/ladder/rung-3 work/L0.1/ladder/rung-3`
