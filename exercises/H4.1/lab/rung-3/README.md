# H4.1/lab/rung-3: Wall-clock timestamps contradict the causal order

## Task
Add type `Write {Node, TS, V}` and three functions. `Inversions(ws)` lists every pair (i, j) where write i happened before write j by their vector clocks but `TS` of i is not smaller than `TS` of j. `WallWinner(ws)` is the index with the highest `TS` (lowest index among ties, -1 for none). `WinnerIsStale(ws)` is true when the winner happened before another write.

## Public interface
Package `clk`. Add `Write`, `Inversions`, `WallWinner`, `WinnerIsStale` in a new file. Do not change the signatures that already exist. The tests bring everything else they need, so you only edit the files in `starter/`.

## Acceptance tests (in words)
- a write made after reading another but stamped 10 ms earlier is found
- no inversion when the clocks agree
- equal timestamps count as an inversion
- concurrent writes are never inversions
- pairs are returned ordered by i then j
- the wall-clock winner is stale when it is causally before another write
- empty and tied inputs
- everything from the earlier rungs, with the race detector on

## How to work
    bash scripts/new_attempt.sh H4.1/lab/rung-3
    # edit work/H4.1/lab/rung-3/
    bash exercises/H4.1/lab/rung-3/test.sh work/H4.1/lab/rung-3
On the lab server: `bash scripts/labserver.sh kit H4.1/lab/rung-3 work/H4.1/lab/rung-3`
