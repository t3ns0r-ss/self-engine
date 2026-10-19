# L0.3/ladder/rung-4: Three classes, one logger

## Task
Finish `Cart`, `Checkout` and `Mailer`: each is built with a `Logger&` that it refers to and does not own, and logs the exact text given in the header.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- three classes share one logger and write in order
- a refused payment logs nothing
- a logger written by the test works unchanged
- none of the classes can be built without a logger
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.3/ladder/rung-4
    # edit work/L0.3/ladder/rung-4/kit.hpp
    bash exercises/L0.3/ladder/rung-4/test.sh work/L0.3/ladder/rung-4
Commit after each rung and tag it (`rung-4`).
On the lab server: `bash scripts/labserver.sh kit L0.3/ladder/rung-4 work/L0.3/ladder/rung-4`
