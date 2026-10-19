#include <string>
#include <vector>

#include "check.hpp"
#include "library.hpp"

void ids_follow_the_order_added() {
    Library lib;
    CHECK(lib.add_book("Dune") == 0);
    CHECK(lib.add_book("Emma") == 1);
    CHECK(lib.add_member("ann") == 0);
    CHECK(lib.add_member("bo") == 1);
    CHECK(lib.book_count() == 2);
    CHECK(lib.member_count() == 2);
}
void a_lent_book_names_its_borrower_and_comes_back() {
    Library lib;
    lib.add_book("Dune");
    lib.add_member("ann");
    CHECK(!lib.is_lent(0));
    CHECK(lib.borrower_of(0) == "");
    lib.lend(0, 0);
    CHECK(lib.is_lent(0));
    CHECK(lib.borrower_of(0) == "ann");
    lib.give_back(0);
    CHECK(!lib.is_lent(0));
}
void a_book_cannot_be_lent_twice() {
    Library lib;
    lib.add_book("Dune");
    lib.add_member("ann");
    lib.add_member("bo");
    lib.lend(0, 0);
    CHECK_THROWS(lib.lend(0, 1));
    CHECK(lib.borrower_of(0) == "ann");
}
void the_loan_limit_is_three_by_default_and_a_refusal_changes_nothing() {
    Library lib;
    for (int i = 0; i < 4; ++i) lib.add_book("b" + std::to_string(i));
    lib.add_member("ann");
    lib.lend(0, 0);
    lib.lend(1, 0);
    lib.lend(2, 0);
    CHECK_THROWS(lib.lend(3, 0));
    CHECK(!lib.is_lent(3));
    CHECK((lib.titles_of(0) == std::vector<std::string>{"b0", "b1", "b2"}));
    lib.give_back(1);
    lib.lend(3, 0);
    CHECK((lib.titles_of(0) == std::vector<std::string>{"b0", "b2", "b3"}));
}
void the_limit_can_be_set() {
    Library lib(1);
    lib.add_book("a");
    lib.add_book("b");
    lib.add_member("ann");
    lib.lend(0, 0);
    CHECK_THROWS(lib.lend(1, 0));
}
void unknown_ids_are_refused() {
    Library lib;
    lib.add_book("Dune");
    lib.add_member("ann");
    CHECK_THROWS(lib.lend(5, 0));
    CHECK_THROWS(lib.lend(0, 5));
    CHECK_THROWS(lib.lend(-1, 0));
    CHECK_THROWS(lib.give_back(9));
    CHECK_THROWS(lib.is_lent(9));
    CHECK_THROWS(lib.titles_of(9));
}
void returning_a_book_that_is_not_lent_is_refused() {
    Library lib;
    lib.add_book("Dune");
    CHECK_THROWS(lib.give_back(0));
}
void loans_survive_the_library_growing() {
    Library lib;
    lib.add_book("Dune");
    lib.add_member("ann");
    lib.lend(0, 0);
    for (int i = 0; i < 200; ++i) { lib.add_book("x"); lib.add_member("y"); }
    CHECK(lib.borrower_of(0) == "ann");
    CHECK((lib.titles_of(0) == std::vector<std::string>{"Dune"}));
}
void a_copied_library_is_independent() {
    Library a;
    a.add_book("Dune");
    a.add_book("Emma");
    a.add_member("ann");
    a.lend(0, 0);
    Library b = a;
    b.lend(1, 0);
    CHECK(!a.is_lent(1));
    CHECK(b.is_lent(1));
    b.give_back(0);
    CHECK(a.is_lent(0));
}

int main() {
    RUN(ids_follow_the_order_added);
    RUN(a_lent_book_names_its_borrower_and_comes_back);
    RUN(a_book_cannot_be_lent_twice);
    RUN(the_loan_limit_is_three_by_default_and_a_refusal_changes_nothing);
    RUN(the_limit_can_be_set);
    RUN(unknown_ids_are_refused);
    RUN(returning_a_book_that_is_not_lent_is_refused);
    RUN(loans_survive_the_library_growing);
    RUN(a_copied_library_is_independent);
    return check::report();
}
