# H4.1/lab/rung-4: A hybrid logical clock

## Task
Add the hybrid logical clock. `NewHLC` takes a `Clock`. `Now()` returns the physical time (nanoseconds) with counter 0 when the clock moved past the last stamp, otherwise the last stamp with the counter plus one. `Receive(m)` returns a stamp after both `m` and the last stamp, with a physical part equal to the largest of the last stamp, `m` and the clock. `Less` orders by physical part, then counter.

## Public interface
Package `clk`. Add `Clock`, `HLCTime` with `Less`, `HLC`, `NewHLC`, `Now`, `Receive` in a new file. Do not change the signatures that already exist. The tests bring everything else they need, so you only edit the files in `starter/`.

## Acceptance tests (in words)
- `Now` follows the physical clock
- the counter breaks ties when the clock stands still
- stamps do not go back when the physical clock is stepped back
- a receive from a faster clock is after the send
- five receive cases with exact results
- 200 random exchanges between clocks 0, -30 and +50 ms apart keep every send before its receive
- the hybrid time stays within the clock difference of real time
- 20 goroutines (race detector)
- everything from the earlier rungs, with the race detector on

## How to work
    bash scripts/new_attempt.sh H4.1/lab/rung-4
    # edit work/H4.1/lab/rung-4/
    bash exercises/H4.1/lab/rung-4/test.sh work/H4.1/lab/rung-4
On the lab server: `bash scripts/labserver.sh kit H4.1/lab/rung-4 work/H4.1/lab/rung-4`
