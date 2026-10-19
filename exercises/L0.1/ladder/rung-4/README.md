# L0.1/ladder/rung-4: A value shared by two orders

## Task
Implement `Address::with_street` and `Order`. An Order holds a `std::shared_ptr<const Address>`; two orders can share one Address object, and replacing the address of one order never shows in the other.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- two orders can share one address object
- changing one order leaves the other alone
- `with_street` builds a new value
- an empty street is refused
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.1/ladder/rung-4
    # edit work/L0.1/ladder/rung-4/kit.hpp
    bash exercises/L0.1/ladder/rung-4/test.sh work/L0.1/ladder/rung-4
Commit after each rung and tag it (`rung-4`).
On the lab server: `bash scripts/labserver.sh kit L0.1/ladder/rung-4 work/L0.1/ladder/rung-4`
