# L2.1/rev-1-3: Shipping rates without the if chain

## Task
`ShippingRates::cost` is a chain of `if` statements over four carriers, and `add` is not implemented. Refactor so that carriers are stored by name together with their rate function (a `std::function`), `add` adds a carrier or replaces an existing one's rate, an empty function is rejected with an exception, and the four built-in carriers keep exactly their fees. Do not change the public interface.

## Public interface
`ShippingRates::cost(carrier, grams) const` and `ShippingRates::add(carrier, rate)` in `starter/shipping.hpp`.

## Acceptance tests (in words)
- STANDARD, EXPRESS, FREIGHT and PICKUP give the same fees as before
- an unknown carrier throws
- a carrier added with `add` is priced, and the others are unchanged
- adding an existing name replaces its rate
- an empty `std::function` throws from `add`

## How to work
    bash scripts/new_attempt.sh L2.1/rev-1-3
    # edit work/L2.1/rev-1-3/
    bash exercises/L2.1/rev-1-3/test.sh work/L2.1/rev-1-3
On the lab server: `bash scripts/labserver.sh kit L2.1/rev-1-3 work/L2.1/rev-1-3`
