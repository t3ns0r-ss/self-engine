# H4.2/lab/rung-2: One replica is down

## Task
Make the store survive a down replica. `Put` succeeds when at least W replicas acknowledged and `Get` when at least R answered; otherwise return an error that wraps `ErrNoQuorum`.

## Public interface
Package `kv`. Implement the functions and methods declared in `starter/`. Do not change their signatures. The tests bring their own fake network (`fakeNet`), so you only edit the files in `starter/`.

## Acceptance tests (in words)
- one replica down: write and read still succeed
- one cut link: write and read still succeed
- two replicas down: both operations return an error wrapping ErrNoQuorum
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh H4.2/lab/rung-2
    # edit work/H4.2/lab/rung-2/
    bash exercises/H4.2/lab/rung-2/test.sh work/H4.2/lab/rung-2
On the lab server: `bash scripts/labserver.sh kit H4.2/lab/rung-2 work/H4.2/lab/rung-2`
