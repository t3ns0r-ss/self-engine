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
    return check::report();
}
