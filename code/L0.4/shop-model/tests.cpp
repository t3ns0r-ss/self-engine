#include <memory>
#include <string>
#include <type_traits>

#include "check.hpp"
#include "shop.hpp"

void destroying_the_shop_destroys_what_it_owns_and_nothing_else() {
    ConsoleMailer mailer;
    Customer ann("ann", "ann@example.com");
    CHECK(live_items == 0);
    {
        Shop shop(mailer);
        shop.catalog().add("pen", 150);
        shop.place(ann, "pen", 2);
        CHECK(live_items == 1);
        CHECK(live_orders == 1);
    }
    CHECK(live_items == 0);                    // Shop *-- Catalog *-- Item: the items went with the shop
    CHECK(live_orders == 0);                   // Shop *-- Order
    CHECK(live_customers == 1);                // Order o-- Customer: the customer was not the shop's to destroy
    CHECK(mailer.sent() == 1);                 // Shop o-- Mailer: the mailer is still there and still has its record
}
void an_order_refers_to_its_customer_and_to_item_prices() {
    ConsoleMailer mailer;
    Customer ann("ann", "ann@example.com");
    Shop shop(mailer);
    shop.catalog().add("pen", 150);
    Order& o = shop.place(ann, "pen", 3);
    CHECK(o.total() == 450);
    CHECK(&o.customer() == &ann);              // the same object, not a copy
}
void an_unknown_sku_stores_and_sends_nothing() {
    ConsoleMailer mailer;
    Customer ann("ann", "ann@example.com");
    Shop shop(mailer);
    CHECK_THROWS(shop.place(ann, "nope", 1));
    CHECK(shop.orders() == 0);
    CHECK(mailer.sent() == 0);
}
void things_with_one_owner_cannot_be_copied_but_a_line_can() {
    CHECK((!std::is_copy_constructible_v<Customer>));
    CHECK((!std::is_copy_constructible_v<Order>));
    CHECK((std::is_copy_constructible_v<Line>));           // a Line holds only an address and a number
    CHECK((std::is_base_of_v<Mailer, ConsoleMailer>));
}

int main() {
    RUN(destroying_the_shop_destroys_what_it_owns_and_nothing_else);
    RUN(an_order_refers_to_its_customer_and_to_item_prices);
    RUN(an_unknown_sku_stores_and_sends_nothing);
    RUN(things_with_one_owner_cannot_be_copied_but_a_line_can);
    return check::report();
}
