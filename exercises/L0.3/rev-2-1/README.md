# L0.3/rev-2-1: A course that refers to students in a registry

## Task
Finish `Course` (see `starter/course.hpp`): it owns its list of enrolments and refers to students kept in a `Registry` that outlives it, so a rename in the registry shows in the course.

## Public interface
The class `Course` in `starter/course.hpp`; `Registry` is finished. The tests include `course.hpp` only.

## Acceptance tests (in words)
- enrolled students are listed in order
- a rename in the registry shows in the course; two courses share one registry
- the registry survives the course
- unknown ids, duplicates and a full course are refused and change nothing
- a copied course has its own enrolments

## How to work
    bash scripts/new_attempt.sh L0.3/rev-2-1
    # edit work/L0.3/rev-2-1/course.hpp
    bash exercises/L0.3/rev-2-1/test.sh work/L0.3/rev-2-1
On the lab server: `bash scripts/labserver.sh kit L0.3/rev-2-1 work/L0.3/rev-2-1`
