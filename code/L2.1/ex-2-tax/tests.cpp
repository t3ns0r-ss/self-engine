#include "check.hpp"
#include "tax.hpp"

void food_is_five_percent() { CHECK(tax_cents(1000, true) == 50); }
void other_is_twenty_percent() { CHECK(tax_cents(1000, false) == 200); }
void rounds_half_up() {
    CHECK(tax_cents(10, true) == 1);    // 0.5 rounds up
    CHECK(tax_cents(9, true) == 0);     // 0.45 rounds down
}
void zero_is_zero() {
    CHECK(tax_cents(0, true) == 0);
    CHECK(tax_cents(0, false) == 0);
}

int main() {
    RUN(food_is_five_percent);
    RUN(other_is_twenty_percent);
    RUN(rounds_half_up);
    RUN(zero_is_zero);
    return check::report();
}
