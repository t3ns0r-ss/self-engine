# L0.3/ladder/rung-2: A team refers to its players

## Task
Finish `Team`: it refers to `Player` objects that exist on their own. It keeps their addresses (no copies), never destroys them, and refuses a temporary player.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- players stay valid after the team is destroyed
- the team sees a change made to a player
- adding a player copies nothing
- a temporary player cannot be added
- an empty team
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.3/ladder/rung-2
    # edit work/L0.3/ladder/rung-2/kit.hpp
    bash exercises/L0.3/ladder/rung-2/test.sh work/L0.3/ladder/rung-2
Commit after each rung and tag it (`rung-2`).
On the lab server: `bash scripts/labserver.sh kit L0.3/ladder/rung-2 work/L0.3/ladder/rung-2`
