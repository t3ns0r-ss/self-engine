# L0.0/cp-1: Wrap a temporary file so it is always deleted

## Task
Implement `TempFile` (see `starter/temp_file.hpp`): it creates an empty file in the system's temporary directory, deletes it when its owner goes away on every way out of the scope (normal end, early return, exception), can be moved but not copied, and a moved-from object must not delete the file the new owner still uses. Time: 45 minutes.

## Public interface
The class `TempFile` in `starter/temp_file.hpp`. Your own helpers are up to you. The tests include `temp_file.hpp` only.

## Acceptance tests (in words)
- the file exists inside the scope and is gone after it
- it is gone after an exception
- `write` appends and `read` returns everything
- after a move the new owner keeps the file alive and deletes it at the end
- two files are independent
- a name in a directory that does not exist throws `std::runtime_error`
- copying does not compile

## How to work
    bash scripts/new_attempt.sh L0.0/cp-1
    # edit work/L0.0/cp-1/temp_file.hpp
    bash exercises/L0.0/cp-1/test.sh work/L0.0/cp-1
On the lab server: `bash scripts/labserver.sh kit L0.0/cp-1 work/L0.0/cp-1`
