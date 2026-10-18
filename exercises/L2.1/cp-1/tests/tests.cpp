#include "check.hpp"
#include "checkout.hpp"

static std::vector<Item> items(std::initializer_list<long long> prices) {
    std::vector<Item> v;
    for (long long p : prices) v.push_back(Item{"x", p});
    return v;
}

void none_sums_the_prices() {
    Checkout c;
    CHECK(c.total(items({1000, 250}), "NONE") == 1250);
    CHECK(c.total(items({}), "NONE") == 0);
}
void percent10_takes_ten_percent_off_rounded_down() {
    Checkout c;
    CHECK(c.total(items({1999}), "PERCENT10") == 1799);
    CHECK(c.total(items({5}), "PERCENT10") == 4);
    CHECK(c.total(items({}), "PERCENT10") == 0);
}
void fixed5_takes_500_off_from_a_basket_of_2000() {
    Checkout c;
    CHECK(c.total(items({2000}), "FIXED5") == 1500);
    CHECK(c.total(items({1500, 1000}), "FIXED5") == 2000);
    CHECK(c.total(items({1999}), "FIXED5") == 1999);
}
void cheapest_free_needs_three_items() {
    Checkout c;
    CHECK(c.total(items({300, 100, 200}), "CHEAPEST_FREE") == 500);
    CHECK(c.total(items({300, 100}), "CHEAPEST_FREE") == 400);
    CHECK(c.total(items({100, 100, 100}), "CHEAPEST_FREE") == 200);
    CHECK(c.total(items({50, 400, 300, 200}), "CHEAPEST_FREE") == 900);
}
void bulk_takes_15_percent_off_from_ten_items_rounded_down() {
    Checkout c;
    CHECK(c.total(items({100, 100, 100, 100, 100, 100, 100, 100, 100, 100}), "BULK") == 850);
    CHECK(c.total(items({100, 100, 100, 100, 100, 100, 100, 100, 100}), "BULK") == 900);
    CHECK(c.total(items({1, 1, 1, 1, 1, 1, 1, 1, 1, 1}), "BULK") == 8);
}
void unknown_rule_is_rejected() {
    Checkout c;
    CHECK_THROWS(c.total(items({100}), "HALFPRICE"));
    CHECK_THROWS(c.total(items({100}), "none"));
}
void negative_price_is_rejected() {
    Checkout c;
    CHECK_THROWS(c.total(items({100, -1}), "NONE"));
}

int main() {
    RUN(none_sums_the_prices);
    RUN(percent10_takes_ten_percent_off_rounded_down);
    RUN(fixed5_takes_500_off_from_a_basket_of_2000);
    RUN(cheapest_free_needs_three_items);
    RUN(bulk_takes_15_percent_off_from_ten_items_rounded_down);
    RUN(unknown_rule_is_rejected);
    RUN(negative_price_is_rejected);
    return check::report();
}
