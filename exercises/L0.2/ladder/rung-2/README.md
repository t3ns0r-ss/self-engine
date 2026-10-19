# L0.2/ladder/rung-2: Deleting through a base pointer

## Task
`BufferedHandler` owns a buffer and counts itself in `live_buffers`. Deleting one through a `Handler*` must run its destructor. Fix `Handler` so that it does; the tests fail to compile until you do.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- `Handler` has a virtual destructor
- deleting through the base, and through a `unique_ptr<Handler>`, runs the derived destructor
- the live count returns to 0
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.2/ladder/rung-2
    # edit work/L0.2/ladder/rung-2/kit.hpp
    bash exercises/L0.2/ladder/rung-2/test.sh work/L0.2/ladder/rung-2
Commit after each rung and tag it (`rung-2`).
On the lab server: `bash scripts/labserver.sh kit L0.2/ladder/rung-2 work/L0.2/ladder/rung-2`
