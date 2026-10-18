# H4.2/lab/rung-3: Refuse settings that can read stale data

## Task
Add `NewClient`. It returns `ErrUnsafeQuorum` when W + R <= N unless `allowStale` is true, and an error when W or R is outside 1..N.

## Public interface
Package `kv`. Implement the functions and methods declared in `starter/`. Do not change their signatures. The tests bring their own fake network (`fakeNet`), so you only edit the files in `starter/`.

## Acceptance tests (in words)
- W=1,R=1 and W=2,R=1 are refused with ErrUnsafeQuorum
- W+R>N settings are accepted
- W or R outside 1..N is an error
- with allowStale a W=1,R=1 client really reads stale
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh H4.2/lab/rung-3
    # edit work/H4.2/lab/rung-3/
    bash exercises/H4.2/lab/rung-3/test.sh work/H4.2/lab/rung-3
On the lab server: `bash scripts/labserver.sh kit H4.2/lab/rung-3 work/H4.2/lab/rung-3`
