# L0.3/cp-1: A library of books, members and loans

## Task
Build `Library` (see `starter/library.hpp`): it owns its books and members, and a loan refers to a book and a member without owning either. Copying a library must give an independent library, and loans must stay valid when the library grows. Time: 45 minutes.

## Public interface
The class `Library` in `starter/library.hpp`. Add private members as you like. The tests include `library.hpp` only.

## Acceptance tests (in words)
- ids follow the order added
- lend and give back; the borrower is named
- a book cannot be lent twice
- the loan limit (3 by default, settable); a refused lend changes nothing
- unknown ids and returning a book that is not lent are refused
- loans survive 400 more additions
- a copied library is independent

## How to work
    bash scripts/new_attempt.sh L0.3/cp-1
    # edit work/L0.3/cp-1/library.hpp
    bash exercises/L0.3/cp-1/test.sh work/L0.3/cp-1
On the lab server: `bash scripts/labserver.sh kit L0.3/cp-1 work/L0.3/cp-1`
