# L0.1/rev-2-1: A duration that stores seconds and exposes minutes

## Task
Implement `Duration` (see `starter/duration.hpp`): it stores whole seconds, is never negative, never changes after it is built, and exposes whole minutes (rounded down) and the leftover seconds.

## Public interface
The class `Duration` in `starter/duration.hpp`. The tests include `duration.hpp` only.

## Acceptance tests (in words)
- minutes and leftover seconds split correctly
- minutes round down
- `from_minutes` stores seconds
- a negative duration throws
- `plus` returns a new Duration
- `Duration` is not a plain struct

## How to work
    bash scripts/new_attempt.sh L0.1/rev-2-1
    # edit work/L0.1/rev-2-1/duration.hpp
    bash exercises/L0.1/rev-2-1/test.sh work/L0.1/rev-2-1
On the lab server: `bash scripts/labserver.sh kit L0.1/rev-2-1 work/L0.1/rev-2-1`
