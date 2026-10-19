# L0.0/rev-2-1: A scoped timer

## Task
Implement `ScopedTimer` (see `starter/scoped_timer.hpp`) so that the elapsed time of any scope is recorded, whether the scope ends normally, with an early return, or with an exception.

## Public interface
The class `ScopedTimer` in `starter/scoped_timer.hpp`: `ScopedTimer(std::vector<long long>& out, long long (*now)())`. The tests pass a fake clock, so nothing depends on real time.

## Acceptance tests (in words)
- the elapsed time is appended when the scope ends, not before
- every return path and an exception record once
- nested timers record the inner one first
- a moved timer records once, from its new owner
- a timer that takes no time records 0
- copying does not compile

## How to work
    bash scripts/new_attempt.sh L0.0/rev-2-1
    # edit work/L0.0/rev-2-1/scoped_timer.hpp
    bash exercises/L0.0/rev-2-1/test.sh work/L0.0/rev-2-1
On the lab server: `bash scripts/labserver.sh kit L0.0/rev-2-1 work/L0.0/rev-2-1`
