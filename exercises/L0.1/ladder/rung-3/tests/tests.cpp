#include <limits>
#include <memory>
#include <stdexcept>
#include <type_traits>

#include "check.hpp"
#include "kit.hpp"

static_assert(!std::is_aggregate_v<Money>, "a struct with public fields would let anyone write a negative amount");

void a_valid_amount_is_kept() {
    Money m(250, "EUR");
    CHECK(m.cents() == 250);
    CHECK(m.currency() == "EUR");
}
void zero_is_allowed() { CHECK(Money(0, "USD").cents() == 0); }
void a_negative_amount_cannot_be_built() { CHECK_THROWS(Money(-1, "USD")); }
void a_bad_currency_cannot_be_built() {
    CHECK_THROWS(Money(1, "usd"));
    CHECK_THROWS(Money(1, "US"));
    CHECK_THROWS(Money(1, "USDX"));
    CHECK_THROWS(Money(1, ""));
}
void the_largest_amount_is_allowed() { CHECK(Money(std::numeric_limits<long long>::max(), "EUR").cents() == std::numeric_limits<long long>::max()); }

void adding_gives_a_new_money_and_leaves_the_operands() {
    Money a(100, "EUR"), b(50, "EUR");
    Money c = a.add(b);
    CHECK(c.cents() == 150);
    CHECK(a.cents() == 100);
    CHECK(b.cents() == 50);
}
void adding_two_currencies_throws() {
    CHECK_THROWS(Money(1, "EUR").add(Money(1, "USD")));
    CHECK_THROWS(Money(0, "EUR").add(Money(0, "USD")));
}
void an_overflowing_sum_is_detected() {
    Money big(std::numeric_limits<long long>::max(), "EUR");
    CHECK_THROWS(big.add(Money(1, "EUR")));
    CHECK(big.add(Money(0, "EUR")).cents() == std::numeric_limits<long long>::max());
}
void the_overflow_error_type_is_overflow_error() {
    bool right_type = false;
    try { Money(std::numeric_limits<long long>::max(), "EUR").add(Money(1, "EUR")); } catch (const std::overflow_error&) { right_type = true; } catch (...) {}
    CHECK(right_type);
}
void the_sum_keeps_the_currency() { CHECK(Money(1, "USD").add(Money(2, "USD")).currency() == "USD"); }

static_assert(!std::is_aggregate_v<DateRange>);

void a_range_keeps_its_ends() {
    DateRange r(3, 9);
    CHECK(r.start() == 3 && r.end() == 9);
    CHECK(r.length() == 6);
}
void a_one_point_range_is_allowed() { CHECK(DateRange(5, 5).length() == 0); }
void start_after_end_is_refused() { CHECK_THROWS(DateRange(6, 5)); }
void with_start_returns_a_new_range_and_leaves_the_old_one() {
    DateRange a(3, 9);
    DateRange b = a.with_start(4);
    CHECK(a.start() == 3);
    CHECK(b.start() == 4 && b.end() == 9);
}
void with_end_returns_a_new_range_and_leaves_the_old_one() {
    DateRange a(3, 9);
    DateRange b = a.with_end(12);
    CHECK(a.end() == 9);
    CHECK(b.start() == 3 && b.end() == 12);
}
void a_change_that_breaks_the_rule_is_refused_and_the_old_range_is_fine() {
    DateRange a(3, 9);
    CHECK_THROWS(a.with_start(10));
    CHECK_THROWS(a.with_end(2));
    CHECK(a.start() == 3 && a.end() == 9);
    CHECK(a.with_start(9).length() == 0);
}

int main() {
    RUN(a_valid_amount_is_kept);
    RUN(zero_is_allowed);
    RUN(a_negative_amount_cannot_be_built);
    RUN(a_bad_currency_cannot_be_built);
    RUN(the_largest_amount_is_allowed);
    RUN(adding_gives_a_new_money_and_leaves_the_operands);
    RUN(adding_two_currencies_throws);
    RUN(an_overflowing_sum_is_detected);
    RUN(the_overflow_error_type_is_overflow_error);
    RUN(the_sum_keeps_the_currency);
    RUN(a_range_keeps_its_ends);
    RUN(a_one_point_range_is_allowed);
    RUN(start_after_end_is_refused);
    RUN(with_start_returns_a_new_range_and_leaves_the_old_one);
    RUN(with_end_returns_a_new_range_and_leaves_the_old_one);
    RUN(a_change_that_breaks_the_rule_is_refused_and_the_old_range_is_fine);
    return check::report();
}
