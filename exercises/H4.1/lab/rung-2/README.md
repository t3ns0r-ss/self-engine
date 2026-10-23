# H4.1/lab/rung-2: Detect concurrent events

## Task
Add vector clocks: type `VC` with `Copy` and `Inc`, `Merge`, and `Compare` returning `Equal`, `Before`, `After` or `Concurrent`. `Stamp` and `Msg` gain a field `V`. A receive merges the message's clock into the process's clock and then counts the receive. Clocks handed out must not change later.

## Public interface
Package `clk`. Add `VC`, `Order` with its four constants, `Merge`, `Compare`, and the field `V` on `Stamp` and `Msg`. Do not change the signatures that already exist. The tests bring everything else they need, so you only edit the files in `starter/`.

## Acceptance tests (in words)
- `Compare` on eleven pairs, including `{A:3}` against `{B:1}`, which are concurrent although the sums differ
- `Merge` and `Inc` leave their inputs unchanged
- two writes without a message are concurrent; after a message the earlier is before the later
- each process's own clocks only go forward, even for a late old message
- editing a received or returned clock does not change any process
- 20 goroutines at once (race detector)
- everything from the earlier rungs, with the race detector on

## How to work
    bash scripts/new_attempt.sh H4.1/lab/rung-2
    # edit work/H4.1/lab/rung-2/
    bash exercises/H4.1/lab/rung-2/test.sh work/H4.1/lab/rung-2
On the lab server: `bash scripts/labserver.sh kit H4.1/lab/rung-2 work/H4.1/lab/rung-2`
