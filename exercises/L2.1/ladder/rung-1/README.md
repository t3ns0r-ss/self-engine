# L2.1/ladder/rung-1: Two parking plans behind one fee function

## Task
Build a FeeService that prices a parking stay for the plans HOURLY (20 for each started hour) and DAILY (100 for each started day). Minutes below 0 and unknown plan names are rejected with an exception. Design it so that more plans can be added later without rewriting the existing ones.

## Public interface
the class `FeeService` in `starter/parking.hpp`: `long long fee(const std::string& plan, long long minutes) const`. Your own helper classes and files are up to you: put them in the same folder, as headers or `.cpp` files. The tests include `parking.hpp` only.

## Acceptance tests (in words)
- hourly: 1 to 60 minutes cost 20, 61 to 120 cost 40, and so on; DAILY: 1 to 1440 cost 100, 1441 to 2880 cost 200
- 0 minutes cost nothing on both plans
- an unknown plan name, or one with different capital letters, throws
- negative minutes throw

## How to work
    bash scripts/new_attempt.sh L2.1/ladder/rung-1
    # edit work/L2.1/ladder/rung-1/
    bash exercises/L2.1/ladder/rung-1/test.sh work/L2.1/ladder/rung-1
Commit after each rung and tag it (`rung-1`). To see your own edit cost: `git diff --numstat rung-1 rung-1`.
On the lab server: `bash scripts/labserver.sh kit L2.1/ladder/rung-1 work/L2.1/ladder/rung-1`
