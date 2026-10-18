# L2.1/ladder/rung-3: Choose the plan at run time from a setting

## Task
Add a class Parking that is created from a plan name, for example read from a configuration file, and prices a stay with fee(minutes). An unknown plan name must be rejected when the Parking is created, not when it is first used. FeeService stays as it is.

## Public interface
a new class `Parking` with `explicit Parking(const std::string& plan)` and `long long fee(long long minutes) const` (already declared as a stub in `starter/parking.hpp`). Your own helper classes and files are up to you: put them in the same folder, as headers or `.cpp` files. The tests include `parking.hpp` only.

## Acceptance tests (in words)
- Parking("HOURLY"), Parking("DAILY") and Parking("WEEKEND") charge like the same plan in FeeService
- Parking("MONTHLY") throws when constructed
- a negative number of minutes throws from fee
- everything the earlier tests check still passes

## How to work
    bash scripts/new_attempt.sh L2.1/ladder/rung-3
    # edit work/L2.1/ladder/rung-3/
    bash exercises/L2.1/ladder/rung-3/test.sh work/L2.1/ladder/rung-3
Commit after each rung and tag it (`rung-3`). To see your own edit cost: `git diff --numstat rung-2 rung-3`.
On the lab server: `bash scripts/labserver.sh kit L2.1/ladder/rung-3 work/L2.1/ladder/rung-3`
