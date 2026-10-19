# L0.4/ladder/rung-4: Show the error path in the sequence

## Task
The editor of the last rung now handles a full disk. Extend `sequence.mmd` so that it shows both runs the test records: the successful save and the save that hits `DiskFull`. Use an `alt` block with an `else` branch.

## Files
`starter/sequence.mmd` is the diagram of the successful run only. Block syntax: `alt condition` … `else other condition` … `end`.

## Acceptance tests (in words)
- the successful run is still an allowed path through the diagram
- the failing run is an allowed path: the cleanup call and the failure notice appear, and the success notice does not
- the diagram allows no path with a call that neither run made

## How to work
    bash scripts/new_attempt.sh L0.4/ladder/rung-4
    # edit work/L0.4/ladder/rung-4/sequence.mmd
    bash exercises/L0.4/ladder/rung-4/test.sh work/L0.4/ladder/rung-4
The checker prints one line for each difference between your drawing and the code. Preview a diagram at mermaid.live or in any Mermaid-aware editor.
On the lab server: `bash scripts/labserver.sh kit L0.4/ladder/rung-4 work/L0.4/ladder/rung-4`
