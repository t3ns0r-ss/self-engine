# L0.0/ladder/rung-2: A function that returns a heap object

## Task
Implement `make_report(n)`: it returns a `std::unique_ptr<Report>` whose total is 1 + 2 + ... + n, owned by the caller, and throws `std::invalid_argument` for n below 1 without leaving any `Report` alive.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- the returned report is owned by the caller and is gone when the caller's pointer goes
- n below 1 throws and leaves no report alive
- totals are 1, 55 and 5050 for n = 1, 10 and 100
- reports can be moved into a container
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.0/ladder/rung-2
    # edit work/L0.0/ladder/rung-2/kit.hpp
    bash exercises/L0.0/ladder/rung-2/test.sh work/L0.0/ladder/rung-2
Commit after each rung and tag it (`rung-2`).
On the lab server: `bash scripts/labserver.sh kit L0.0/ladder/rung-2 work/L0.0/ladder/rung-2`
