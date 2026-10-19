# L0.1/rev-1-3: A stack that protects its own rule

## Task
`starter/stack.hpp` has a Stack with a public `size` field that trusts every caller. Turn it into a class that protects its rule: 0 <= size <= 4. Add `size()`; `push` on a full stack throws `std::length_error`, `pop` on an empty one throws `std::out_of_range`, and a refused call changes nothing.

## Public interface
The class `Stack` in `starter/stack.hpp`: `push(int)`, `pop()`, `size() const`. The tests include `stack.hpp` only.

## Acceptance tests (in words)
- push then pop returns the last value
- size follows the operations
- pushing onto a full stack throws `std::length_error` and changes nothing
- popping an empty stack throws `std::out_of_range` and changes nothing
- `Stack` is not a plain struct

## How to work
    bash scripts/new_attempt.sh L0.1/rev-1-3
    # edit work/L0.1/rev-1-3/stack.hpp
    bash exercises/L0.1/rev-1-3/test.sh work/L0.1/rev-1-3
On the lab server: `bash scripts/labserver.sh kit L0.1/rev-1-3 work/L0.1/rev-1-3`
