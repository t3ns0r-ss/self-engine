# H4.1/lab/rung-5: One writer needs only a sequence number

## Task
Add `Seq` with `Next()` returning 1, 2, 3, ... safely from many goroutines, the type `Rec {Seq, Val}`, `InOrder(recs)` returning the records sorted by `Seq` without duplicates (the input is unchanged), and `Gaps(recs)` returning the numbers from 1 up to the highest received that are missing.

## Public interface
Package `clk`. Add `Seq`, `Rec`, `InOrder`, `Gaps` in a new file. Do not change the signatures that already exist. The tests bring everything else they need, so you only edit the files in `starter/`.

## Acceptance tests (in words)
- `Next` counts from one
- 2 000 numbers from 20 goroutines are all distinct (race detector)
- shuffled records come back in write order and the input is not changed
- duplicates are dropped
- gaps are found in five cases
- everything from the earlier rungs, with the race detector on

## How to work
    bash scripts/new_attempt.sh H4.1/lab/rung-5
    # edit work/H4.1/lab/rung-5/
    bash exercises/H4.1/lab/rung-5/test.sh work/H4.1/lab/rung-5
On the lab server: `bash scripts/labserver.sh kit H4.1/lab/rung-5 work/H4.1/lab/rung-5`
