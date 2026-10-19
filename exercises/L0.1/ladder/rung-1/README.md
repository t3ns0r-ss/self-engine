# L0.1/ladder/rung-1: A Money that can never hold a bad value

## Task
Implement `Money(cents, currency)` so that no Money can ever hold a negative amount or a currency that is not exactly three capital letters. The constructor throws `std::invalid_argument`. Keep the fields private: the tests fail if Money is a plain struct.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- valid amounts and currencies are kept
- a negative amount, and a currency that is not three capital letters, throw
- the largest amount is allowed
- `Money` is not a plain struct

## How to work
    bash scripts/new_attempt.sh L0.1/ladder/rung-1
    # edit work/L0.1/ladder/rung-1/kit.hpp
    bash exercises/L0.1/ladder/rung-1/test.sh work/L0.1/ladder/rung-1
Commit after each rung and tag it (`rung-1`).
On the lab server: `bash scripts/labserver.sh kit L0.1/ladder/rung-1 work/L0.1/ladder/rung-1`
