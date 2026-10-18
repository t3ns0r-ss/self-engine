# H4.2/lab/rung-4: Read repair

## Task
Add read repair. When `ReadRepair` is set, `Get` writes the newest version back to every replica that answered with an older one. A failed repair must not fail the read, and a repair never lowers a version.

## Public interface
Package `kv`. Implement the functions and methods declared in `starter/`. Do not change their signatures. The tests bring their own fake network (`fakeNet`), so you only edit the files in `starter/`.

## Acceptance tests (in words)
- read repair brings a stale replica up to date
- without the flag nothing changes
- repair writes the newest value, not the stale one
- a failed repair does not fail the read
- repair never lowers a newer replica
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh H4.2/lab/rung-4
    # edit work/H4.2/lab/rung-4/
    bash exercises/H4.2/lab/rung-4/test.sh work/H4.2/lab/rung-4
On the lab server: `bash scripts/labserver.sh kit H4.2/lab/rung-4 work/H4.2/lab/rung-4`
