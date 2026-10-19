# L0.0/ladder/rung-3: Two owners really need the same object

## Task
Implement `ImageCache::get(name)`: callers asking for the same name while any of them still holds the image get the same `Image`; the cache itself must not keep an image alive; once every holder has let go, the next `get` loads a new one.

## Public interface
The header `starter/kit.hpp`. Each rung adds one piece to it; the earlier pieces are finished and must keep working. Do not change the signatures. The tests include `kit.hpp` only.

## Acceptance tests (in words)
- two callers asking for one name share one image (use count 2, one image alive)
- the image is destroyed when the last holder lets go
- the cache does not keep images alive
- a dead entry is loaded again
- different names give different images
- everything from the earlier rungs

## How to work
    bash scripts/new_attempt.sh L0.0/ladder/rung-3
    # edit work/L0.0/ladder/rung-3/kit.hpp
    bash exercises/L0.0/ladder/rung-3/test.sh work/L0.0/ladder/rung-3
Commit after each rung and tag it (`rung-3`).
On the lab server: `bash scripts/labserver.sh kit L0.0/ladder/rung-3 work/L0.0/ladder/rung-3`
