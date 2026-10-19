# L0.0/ladder/rung-4: A function that only reads an object

## Task
Implement `name_length(const Image&)`: it returns the number of characters in the image's name, takes no ownership, and makes no copy. It must accept a temporary and a `const` image.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- reading a shared image changes no use count
- a temporary is accepted and gone afterwards
- a const image is accepted
- an empty name has length 0
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.0/ladder/rung-4
    # edit work/L0.0/ladder/rung-4/kit.hpp
    bash exercises/L0.0/ladder/rung-4/test.sh work/L0.0/ladder/rung-4
Commit after each rung and tag it (`rung-4`).
On the lab server: `bash scripts/labserver.sh kit L0.0/ladder/rung-4 work/L0.0/ladder/rung-4`
