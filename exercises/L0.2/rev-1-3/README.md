# L0.2/rev-1-3: Replace a tag and a switch with an interface

## Task
`starter/channels.hpp` picks behaviour with an enum and a switch, so every new channel edits `describe`. Replace it with an interface `Channel`, with `EmailChannel` and `SmsChannel`, and `broadcast` that works with any Channel, including ones you did not write.

## Public interface
`Channel` (abstract, virtual destructor), `EmailChannel`, `SmsChannel`, `broadcast` in `starter/channels.hpp`. The tests include `channels.hpp` only.

## Acceptance tests (in words)
- each channel describes itself
- broadcast keeps the order
- a channel defined by the test works without editing broadcast
- a null channel throws `std::invalid_argument`
- `Channel` is abstract and has a virtual destructor

## How to work
    bash scripts/new_attempt.sh L0.2/rev-1-3
    # edit work/L0.2/rev-1-3/channels.hpp
    bash exercises/L0.2/rev-1-3/test.sh work/L0.2/rev-1-3
On the lab server: `bash scripts/labserver.sh kit L0.2/rev-1-3 work/L0.2/rev-1-3`
