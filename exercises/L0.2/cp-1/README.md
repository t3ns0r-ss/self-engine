# L0.2/cp-1: Shape area service with an interface and a template twin

## Task
Implement `Shape`, `Rect`, `Square`, `AreaService` and the template `total_area_of` (see `starter/service.hpp`). The service works with any Shape subclass, owns the shapes it is given and destroys them correctly; the template twin does the same total without a base class. Time: 45 minutes.

## Public interface
The classes and the function template in `starter/service.hpp`. Add private helpers as you like. The tests include `service.hpp` only.

## Acceptance tests (in words)
- each shape gives its area, perimeter and name
- the service totals a mixed list; empty gives 0 and no largest
- the largest shape is the first one with the largest area
- a null shape is refused
- a subclass defined by the test works and is destroyed with the service
- the template twin gives the same total
- `Shape` is abstract and has a virtual destructor

## How to work
    bash scripts/new_attempt.sh L0.2/cp-1
    # edit work/L0.2/cp-1/service.hpp
    bash exercises/L0.2/cp-1/test.sh work/L0.2/cp-1
On the lab server: `bash scripts/labserver.sh kit L0.2/cp-1 work/L0.2/cp-1`
