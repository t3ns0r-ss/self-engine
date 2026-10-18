# H4.2/lab/rung-5: A workload that tolerates a second of staleness

## Task
Write `Choose(toleratedStalenessMs)` for N = 3: below 1000 ms return W = 2, R = 2 without read repair; at 1000 ms or more return W = 2, R = 1 with read repair. The Client does not change: this rung is a setting, not new structure.

## Public interface
Package `kv`. Implement the functions and methods declared in `starter/`. Do not change their signatures. The tests bring their own fake network (`fakeNet`), so you only edit the files in `starter/`.

## Acceptance tests (in words)
- the four thresholds give the right settings
- both settings keep working with one replica down
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh H4.2/lab/rung-5
    # edit work/H4.2/lab/rung-5/
    bash exercises/H4.2/lab/rung-5/test.sh work/H4.2/lab/rung-5
On the lab server: `bash scripts/labserver.sh kit H4.2/lab/rung-5 work/H4.2/lab/rung-5`
