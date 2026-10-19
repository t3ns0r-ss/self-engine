#include <stdexcept>
#include <type_traits>

#include "check.hpp"
#include "discount.hpp"

static_assert(!std::is_aggregate_v<Percentage>);
static_assert(!std::is_aggregate_v<Discount>);

void a_percentage_from_0_to_100_is_valid() {
    CHECK(Percentage(0).value() == 0);
    CHECK(Percentage(100).value() == 100);
    CHECK(Percentage(37).value() == 37);
}
void a_percentage_outside_0_to_100_is_refused() {
    CHECK_THROWS(Percentage(-1));
    CHECK_THROWS(Percentage(101));
    CHECK_THROWS(Percentage(250));
}
void of_rounds_down() {
    CHECK(Percentage(10).of(1999) == 199);
    CHECK(Percentage(33).of(100) == 33);
    CHECK(Percentage(100).of(77) == 77);
    CHECK(Percentage(0).of(500) == 0);
}
void of_refuses_a_negative_amount() { CHECK_THROWS(Percentage(10).of(-1)); }
void a_discount_applies_from_the_minimum_spend() {
    Discount d(Percentage(10), 2000);
    CHECK(d.apply(2000) == 1800);       // the threshold itself qualifies
    CHECK(d.apply(1999) == 1999);
    CHECK(d.apply(5000) == 4500);
}
void a_negative_minimum_spend_is_refused() { CHECK_THROWS(Discount(Percentage(10), -1)); }
void a_negative_total_is_refused() { CHECK_THROWS(Discount(Percentage(10), 0).apply(-5)); }
void none_changes_nothing() {
    CHECK(Discount::none().apply(0) == 0);
    CHECK(Discount::none().apply(12345) == 12345);
}
void a_discount_can_be_applied_many_times_with_the_same_result() {
    const Discount d(Percentage(25), 100);
    CHECK(d.apply(1000) == 750);
    CHECK(d.apply(1000) == 750);
}
void a_hundred_percent_makes_it_free() { CHECK(Discount(Percentage(100), 0).apply(999) == 0); }

int main() {
    RUN(a_percentage_from_0_to_100_is_valid);
    RUN(a_percentage_outside_0_to_100_is_refused);
    RUN(of_rounds_down);
    RUN(of_refuses_a_negative_amount);
    RUN(a_discount_applies_from_the_minimum_spend);
    RUN(a_negative_minimum_spend_is_refused);
    RUN(a_negative_total_is_refused);
    RUN(none_changes_nothing);
    RUN(a_discount_can_be_applied_many_times_with_the_same_result);
    RUN(a_hundred_percent_makes_it_free);
    return check::report();
}
