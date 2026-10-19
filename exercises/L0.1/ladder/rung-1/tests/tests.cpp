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

int main() {
    RUN(a_valid_amount_is_kept);
    RUN(zero_is_allowed);
    RUN(a_negative_amount_cannot_be_built);
    RUN(a_bad_currency_cannot_be_built);
    RUN(the_largest_amount_is_allowed);
    return check::report();
}
