# H4.1 lab rung 3: solution

## Design
Compare the vector clocks of every pair and look at the timestamps only where the clocks say Before.

```mermaid
flowchart LR
  A[A writes x=1 at TS 1000] -->|message| B[B writes x=2 at TS 990]
  B --> W[Wall winner: x=1, stale]
```

New file skew.go; clk.go unchanged. About 40 lines.

## Decision record
- Decision: Use the vector clocks as ground truth and report where the timestamps disagree.
- Alternative and when it is better: Trust the timestamps: right when the spread of the clocks is far below the gap between dependent writes.

## Three common wrong approaches
1. Treating a tie as not an inversion: `TestEqualTimestampsCountAsInversion` fails.
2. Counting concurrent writes as inversions: `TestConcurrentWritesAreNeverInversions` fails.
3. Checking the winner against the wrong direction of the comparison.
