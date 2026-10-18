# L2.1/ladder/rung-5: A change to the fee signature itself

## Task
Every fee now depends on the vehicle. Parking::fee takes (minutes, Vehicle). Trucks pay double on HOURLY (so also on MEMBER, before the discount), 150 instead of 100 for each started day on DAILY, and the same as cars on WEEKEND. Make the change in your own code and count the files you had to edit.

## Public interface
`enum class Vehicle { Car, Truck }` and `long long Parking::fee(long long minutes, Vehicle vehicle) const` (stubs in `starter/parking.hpp`). From this rung only `Parking` is tested. Your own helper classes and files are up to you: put them in the same folder, as headers or `.cpp` files. The tests include `parking.hpp` only.

## Acceptance tests (in words)
- cars pay what they paid before on every plan
- a truck pays 80 for 61 minutes on HOURLY, 150 for 1 minute and 300 for 1441 minutes on DAILY, and the car fee on WEEKEND
- a truck on MEMBER with 25 per cent pays 60 for 61 minutes
- unknown plans, negative minutes and a discount above 100 still throw

## How to work
    bash scripts/new_attempt.sh L2.1/ladder/rung-5
    # edit work/L2.1/ladder/rung-5/
    bash exercises/L2.1/ladder/rung-5/test.sh work/L2.1/ladder/rung-5
Commit after each rung and tag it (`rung-5`). To see your own edit cost: `git diff --numstat rung-4 rung-5`.
On the lab server: `bash scripts/labserver.sh kit L2.1/ladder/rung-5 work/L2.1/ladder/rung-5`
