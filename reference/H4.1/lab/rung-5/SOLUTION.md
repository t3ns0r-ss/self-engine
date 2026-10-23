# H4.1 lab rung 5: solution

## Design
A counter behind a mutex. The receiver sorts by sequence number, drops duplicates, and finds missing numbers by walking from 1 to the highest.

```mermaid
flowchart LR
  W[One writer: 1,2,3...] -->|reordered by the network| R[Reader: sort by number, report gaps]
```

New file seq.go; no existing code changes. This rung adds no new structure: the measurement is that a counter is enough.

## Decision record
- Decision: A plain counter. No vector, no hybrid clock.
- Alternative and when it is better: A vector clock with one entry: the same order with a map per record, and it cannot report a missing record.

## Three common wrong approaches
1. `Next` without a lock: the race detector reports a race.
2. `Gaps` starting at 0: it always reports 0 as missing.
3. `InOrder` that keeps duplicates.
