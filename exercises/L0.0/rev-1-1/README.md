# L0.0/rev-1-1: Spot the leak

## Task
`starter/loader.hpp` has a function that leaks an `Image` on some paths. Fix it so that no `Image` is left alive on any path, without changing what `load_and_measure` returns or when it throws. Do not touch the `Image` class.

## Public interface
`load_and_measure(const std::string&)` in `starter/loader.hpp`. The tests include `loader.hpp` only.

## Acceptance tests (in words)
- a good name gives its pixels (100 per character)
- an empty name and a name longer than 20 characters throw `std::invalid_argument`
- after every call, good or failing, `Image::live()` is 0

## How to work
    bash scripts/new_attempt.sh L0.0/rev-1-1
    # edit work/L0.0/rev-1-1/loader.hpp
    bash exercises/L0.0/rev-1-1/test.sh work/L0.0/rev-1-1
On the lab server: `bash scripts/labserver.sh kit L0.0/rev-1-1 work/L0.0/rev-1-1`
