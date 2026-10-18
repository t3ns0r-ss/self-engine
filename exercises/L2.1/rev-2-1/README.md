# L2.1/rev-2-1: Replace the type code with channels

## Task
`Notifier::send(Kind, to, text)` switches on a type code, so a new channel means editing the `switch`. Refactor so that channels are objects that implement `Channel`, stored by name: `add_channel(name, channel)` adds one (or replaces an existing one of that name), and `send(name, to, text)` uses it. The built-in names EMAIL, SMS and PUSH must give exactly the same messages as before. A null channel is rejected. The caller in the tests defines its own `Channel` and adds it, without editing your code.

## Public interface
`Channel`, `Notifier::add_channel(name, std::unique_ptr<Channel>)` and `Notifier::send(name, to, text) const` in `starter/notifier.hpp`.

## Acceptance tests (in words)
- EMAIL, SMS (cut at 160 characters) and PUSH (cut at 60) give the same messages as before
- an unknown channel name throws
- a channel class defined in the test can be added and used, and the built-ins still work
- adding an existing name replaces the channel
- a null channel throws

## How to work
    bash scripts/new_attempt.sh L2.1/rev-2-1
    # edit work/L2.1/rev-2-1/
    bash exercises/L2.1/rev-2-1/test.sh work/L2.1/rev-2-1
On the lab server: `bash scripts/labserver.sh kit L2.1/rev-2-1 work/L2.1/rev-2-1`
