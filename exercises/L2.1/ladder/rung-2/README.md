# L2.1/ladder/rung-2: Add a weekend plan

## Task
The FeeService you have (or the reference of rung 1) must also price the plan WEEKEND at 40 for each started hour. Add it so that no existing plan is edited. Afterwards compare the size of your edit with what a single function holding every plan would have needed: run git diff --numstat against your rung-1 tag.

## Public interface
the same `FeeService`; only the set of plan names grows. Your own helper classes and files are up to you: put them in the same folder, as headers or `.cpp` files. The tests include `parking.hpp` only.

## Acceptance tests (in words)
- WEEKEND: 1 to 60 minutes cost 40, 61 to 120 cost 80; 0 minutes cost nothing
- HOURLY and DAILY give exactly the same fees as before
- everything the rung-1 tests check still passes

## How to work
    bash scripts/new_attempt.sh L2.1/ladder/rung-2
    # edit work/L2.1/ladder/rung-2/
    bash exercises/L2.1/ladder/rung-2/test.sh work/L2.1/ladder/rung-2
Commit after each rung and tag it (`rung-2`). To see your own edit cost: `git diff --numstat rung-1 rung-2`.
On the lab server: `bash scripts/labserver.sh kit L2.1/ladder/rung-2 work/L2.1/ladder/rung-2`
