# L0.1/ladder/rung-2: Adding must not overflow or mix currencies

## Task
Add `Money::add`. It returns a new Money, throws `std::invalid_argument` when the currencies differ and `std::overflow_error` when the sum does not fit in a `long long`. Neither operand changes.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- adding gives a new Money and changes neither operand
- different currencies throw
- an overflowing sum throws `std::overflow_error`
- the sum keeps the currency
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.1/ladder/rung-2
    # edit work/L0.1/ladder/rung-2/kit.hpp
    bash exercises/L0.1/ladder/rung-2/test.sh work/L0.1/ladder/rung-2
Commit after each rung and tag it (`rung-2`).
On the lab server: `bash scripts/labserver.sh kit L0.1/ladder/rung-2 work/L0.1/ladder/rung-2`
