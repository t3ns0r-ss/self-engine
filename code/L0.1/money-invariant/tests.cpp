#include <limits>
#include <stdexcept>
#include <type_traits>

#include "check.hpp"
#include "money.hpp"

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
void adding_gives_a_new_money_and_leaves_the_operands() {
    Money a(100, "EUR"), b(50, "EUR");
    Money c = a.add(b);
    CHECK(c.cents() == 150);
    CHECK(a.cents() == 100);
    CHECK(b.cents() == 50);
}
void adding_two_currencies_throws() { CHECK_THROWS(Money(1, "EUR").add(Money(1, "USD"))); }
void an_overflowing_sum_is_detected() {
    Money big(std::numeric_limits<long long>::max(), "EUR");
    CHECK_THROWS(big.add(Money(1, "EUR")));
    CHECK(big.add(Money(0, "EUR")).cents() == std::numeric_limits<long long>::max());
}
void subtracting_below_zero_throws() {
    CHECK_THROWS(Money(5, "EUR").subtract(Money(6, "EUR")));
    CHECK(Money(5, "EUR").subtract(Money(5, "EUR")).cents() == 0);
}
// Exhaustive on a small domain: whatever add and subtract accept, the result still obeys the rule.
void every_accepted_result_obeys_the_rule() {
    for (long long a = 0; a <= 30; ++a)
        for (long long b = 0; b <= 30; ++b) {
            Money x(a, "EUR"), y(b, "EUR");
            CHECK(x.add(y).cents() == a + b);
            if (b <= a) CHECK(x.subtract(y).cents() == a - b);
            else CHECK_THROWS(x.subtract(y));
        }
}
int main() {
    RUN(a_valid_amount_is_kept);
    RUN(zero_is_allowed);
    RUN(a_negative_amount_cannot_be_built);
    RUN(a_bad_currency_cannot_be_built);
    RUN(adding_gives_a_new_money_and_leaves_the_operands);
    RUN(adding_two_currencies_throws);
    RUN(an_overflowing_sum_is_detected);
    RUN(subtracting_below_zero_throws);
    RUN(every_accepted_result_obeys_the_rule);
    return check::report();
}
