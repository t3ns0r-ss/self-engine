#include <stdexcept>
#include <string>
#include <vector>

#include "check.hpp"
#include "checked_first.hpp"
#include "mailed_first.hpp"

void the_two_shops_do_the_same_for_an_order_that_fits() {
    checked_first::Inventory ia; checked_first::Mailer ma; checked_first::Shop a(ia, ma);
    mailed_first::Inventory ib; mailed_first::Mailer mb; mailed_first::Shop b(ib, mb);
    a.place_order(1); b.place_order(1);
    CHECK(ia.left() == ib.left());
    CHECK(ma.sent() == mb.sent());
}
void the_two_shops_call_in_a_different_order() {
    checked_first::trace.clear(); mailed_first::trace.clear();
    checked_first::Inventory ia; checked_first::Mailer ma; checked_first::Shop a(ia, ma);
    mailed_first::Inventory ib; mailed_first::Mailer mb; mailed_first::Shop b(ib, mb);
    a.place_order(1); b.place_order(1);
    CHECK((checked_first::trace == std::vector<std::string>{"Shop->Inventory: reserve", "Shop->Mailer: send"}));
    CHECK((mailed_first::trace == std::vector<std::string>{"Shop->Mailer: send", "Shop->Inventory: reserve"}));
}
void only_the_order_of_calls_shows_which_shop_confirms_an_order_that_then_fails() {
    checked_first::Inventory ia; checked_first::Mailer ma; checked_first::Shop a(ia, ma);
    mailed_first::Inventory ib; mailed_first::Mailer mb; mailed_first::Shop b(ib, mb);
    CHECK_THROWS(a.place_order(5));
    CHECK_THROWS(b.place_order(5));
    CHECK(ma.sent() == 0);                     // the checked-first shop mailed nobody
    CHECK(mb.sent() == 1);                     // the mailed-first shop confirmed an order it could not fill
}

int main() {
    RUN(the_two_shops_do_the_same_for_an_order_that_fits);
    RUN(the_two_shops_call_in_a_different_order);
    RUN(only_the_order_of_calls_shows_which_shop_confirms_an_order_that_then_fails);
    return check::report();
}
