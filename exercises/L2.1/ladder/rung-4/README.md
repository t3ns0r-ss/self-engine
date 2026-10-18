# L2.1/ladder/rung-4: A plan needs an extra input the others do not

## Task
Add the plan MEMBER: the hourly fee with a percentage taken off, rounded down. The percentage is given when the Parking is created. Parking(plan, discount) takes it as a second argument with default 0; it must be between 0 and 100; plans other than MEMBER ignore it. Keep the one-argument fee(minutes) shared by all plans.

## Public interface
`Parking(const std::string& plan, int member_discount_percent = 0)` (a stub constructor is in `starter/parking.hpp`) and the plan name "MEMBER". Your own helper classes and files are up to you: put them in the same folder, as headers or `.cpp` files. The tests include `parking.hpp` only.

## Acceptance tests (in words)
- Parking("MEMBER", 25).fee(61) is 30: the hourly fee 40, with 25 per cent off
- the discount is rounded down: 33 per cent off 40 gives 26
- a discount below 0 or above 100 throws when constructed
- HOURLY, DAILY and WEEKEND ignore the discount argument
- everything the earlier tests check still passes

## How to work
    bash scripts/new_attempt.sh L2.1/ladder/rung-4
    # edit work/L2.1/ladder/rung-4/
    bash exercises/L2.1/ladder/rung-4/test.sh work/L2.1/ladder/rung-4
Commit after each rung and tag it (`rung-4`). To see your own edit cost: `git diff --numstat rung-3 rung-4`.
On the lab server: `bash scripts/labserver.sh kit L2.1/ladder/rung-4 work/L2.1/ladder/rung-4`
