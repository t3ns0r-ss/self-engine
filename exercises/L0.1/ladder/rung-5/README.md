# L0.1/ladder/rung-5: A bag of independent settings

## Task
Implement `describe(const Settings&)` for the plain struct `Settings` (four independent fields). Do not turn Settings into a class: this rung has no rule to protect, so a struct is the right size.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- defaults, direct field writes, aggregate initialisation
- copies are independent
- `Settings` is still a plain aggregate
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.1/ladder/rung-5
    # edit work/L0.1/ladder/rung-5/kit.hpp
    bash exercises/L0.1/ladder/rung-5/test.sh work/L0.1/ladder/rung-5
Commit after each rung and tag it (`rung-5`).
On the lab server: `bash scripts/labserver.sh kit L0.1/ladder/rung-5 work/L0.1/ladder/rung-5`
