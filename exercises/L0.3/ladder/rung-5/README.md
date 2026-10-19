# L0.3/ladder/rung-5: Sharing six lines without a hierarchy

## Task
Implement `format_cents`, `Invoice` and `Receipt`. Share the formatting with the free function; neither class may derive from the other or have a virtual function.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- cents are formatted with two decimals and a sign
- invoice and receipt text
- no common base, no virtual function, no hidden pointer
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.3/ladder/rung-5
    # edit work/L0.3/ladder/rung-5/kit.hpp
    bash exercises/L0.3/ladder/rung-5/test.sh work/L0.3/ladder/rung-5
Commit after each rung and tag it (`rung-5`).
On the lab server: `bash scripts/labserver.sh kit L0.3/ladder/rung-5 work/L0.3/ladder/rung-5`
