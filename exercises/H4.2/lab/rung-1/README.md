# H4.2/lab/rung-1: Put and Get over three replicas

## Task
Implement `Replica.Handle`, `Client.Put` and `Client.Get` for three replicas, W = 2 and R = 2. In this rung every replica must answer: if any call fails, return an error. `Get` returns the newest version it saw.

## Public interface
Package `kv`. Implement the functions and methods declared in `starter/`. Do not change their signatures. The tests bring their own fake network (`fakeNet`), so you only edit the files in `starter/`.

## Acceptance tests (in words)
- a written value is read back
- an unknown key reads as the zero value
- the newest version among replies wins even if only one replica has it
- an older write never replaces a newer value
- 40 clients writing one key at once end with the highest version (run with the race detector)

## How to work
    bash scripts/new_attempt.sh H4.2/lab/rung-1
    # edit work/H4.2/lab/rung-1/
    bash exercises/H4.2/lab/rung-1/test.sh work/H4.2/lab/rung-1
On the lab server: `bash scripts/labserver.sh kit H4.2/lab/rung-1 work/H4.2/lab/rung-1`
