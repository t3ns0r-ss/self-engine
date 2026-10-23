# H4.1/lab/rung-1: Lamport clocks on three processes

## Task
Implement a Lamport clock and a `Process` that stamps its events. A local or send event adds 1 to the clock; a receive sets the clock to the larger of its own value and the message's value, then adds 1. There is no network: `Send` returns a message and the test delivers it to `Receive` in any order.

## Public interface
Package `clk`. Implement the types and methods declared in `starter/`: `Lamport`, `Process`, `Msg`, `Stamp`. Do not change the signatures that already exist. The tests bring everything else they need, so you only edit the files in `starter/`.

## Acceptance tests (in words)
- two ticks give 1 and 2; a receive of 10 at time 2 gives 11; a receive of 5 afterwards gives 12
- a receive is always after its send, even when the receiver is ahead or behind
- a chain A to B to C to A has increasing times
- messages delivered out of order still give increasing times at the receiver
- the log has the right labels and owner, and is a copy
- 20 goroutines using one process at once (race detector)
- everything from the earlier rungs, with the race detector on

## How to work
    bash scripts/new_attempt.sh H4.1/lab/rung-1
    # edit work/H4.1/lab/rung-1/
    bash exercises/H4.1/lab/rung-1/test.sh work/H4.1/lab/rung-1
On the lab server: `bash scripts/labserver.sh kit H4.1/lab/rung-1 work/H4.1/lab/rung-1`
