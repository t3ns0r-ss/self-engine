# L0.0/ladder/rung-1: A connection that closes itself

## Task
Implement `Connection` so that creating one counts an open in the `Log` it is given, and destroying it counts one close, on every way out of the scope: normal end, early return and exception. A `Connection` cannot be copied but can be moved; a moved-from one closes nothing.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- a connection counts one open when created and one close when its scope ends
- an early return and a thrown exception also close it, once
- moving transfers the closing; the moved-from object closes nothing
- five connections held in a `std::vector` close once each
- copying does not compile

## How to work
    bash scripts/new_attempt.sh L0.0/ladder/rung-1
    # edit work/L0.0/ladder/rung-1/kit.hpp
    bash exercises/L0.0/ladder/rung-1/test.sh work/L0.0/ladder/rung-1
Commit after each rung and tag it (`rung-1`).
On the lab server: `bash scripts/labserver.sh kit L0.0/ladder/rung-1 work/L0.0/ladder/rung-1`
