# L0.1/cp-1: Build a Percentage and a Discount that cannot hold bad values

## Task
Implement `Percentage` and `Discount` (see `starter/discount.hpp`) so that neither can ever hold a bad value: a percentage is 0 to 100, a minimum spend is not negative, and a negative amount is refused. Discounts round down. Time: 45 minutes.

## Public interface
The classes `Percentage` and `Discount` in `starter/discount.hpp`. Add private helpers as you like. The tests include `discount.hpp` only.

## Acceptance tests (in words)
- a percentage from 0 to 100 is valid and 101 or -1 throws
- `of` rounds down and refuses a negative amount
- a discount applies from its minimum spend (inclusive) and not below it
- a negative minimum spend or total throws
- `none()` changes nothing
- neither class is a plain struct

## How to work
    bash scripts/new_attempt.sh L0.1/cp-1
    # edit work/L0.1/cp-1/discount.hpp
    bash exercises/L0.1/cp-1/test.sh work/L0.1/cp-1
On the lab server: `bash scripts/labserver.sh kit L0.1/cp-1 work/L0.1/cp-1`
