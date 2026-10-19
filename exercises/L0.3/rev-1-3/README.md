# L0.3/rev-1-3: Replace inheritance used for reuse with composition

## Task
`starter/stack.hpp` has a Stack that inherits from `std::vector<int>`. Rewrite it so that the vector is a private member and only `push`, `pop`, `top`, `size`, `empty` and `clear` exist.

## Public interface
The class `Stack` in `starter/stack.hpp`. The tests include `stack.hpp` only.

## Acceptance tests (in words)
- pop returns the last push; top does not remove
- pop and top on an empty stack throw
- `clear` empties it
- copies are independent
- `Stack` is not derived from `std::vector<int>` and has no `erase` or `operator[]`

## How to work
    bash scripts/new_attempt.sh L0.3/rev-1-3
    # edit work/L0.3/rev-1-3/stack.hpp
    bash exercises/L0.3/rev-1-3/test.sh work/L0.3/rev-1-3
On the lab server: `bash scripts/labserver.sh kit L0.3/rev-1-3 work/L0.3/rev-1-3`
