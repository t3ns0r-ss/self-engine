# L0.2/rev-2-1: A pipeline of steps chosen at run time

## Task
Implement `Step` (interface), `AddStep`, `MulStep` and `Pipeline` (see `starter/pipeline.hpp`). A pipeline owns its steps, runs them in the order they were added and works with a Step subclass the caller defines.

## Public interface
The classes in `starter/pipeline.hpp`. The tests include `pipeline.hpp` only.

## Acceptance tests (in words)
- steps apply in the order added
- an empty pipeline returns its input
- a null step throws `std::invalid_argument`
- a step defined by the test works and is destroyed with the pipeline
- `Step` is abstract and has a virtual destructor

## How to work
    bash scripts/new_attempt.sh L0.2/rev-2-1
    # edit work/L0.2/rev-2-1/pipeline.hpp
    bash exercises/L0.2/rev-2-1/test.sh work/L0.2/rev-2-1
On the lab server: `bash scripts/labserver.sh kit L0.2/rev-2-1 work/L0.2/rev-2-1`
