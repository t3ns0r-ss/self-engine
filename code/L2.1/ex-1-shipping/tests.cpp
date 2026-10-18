#include "check.hpp"
#include "shipping.hpp"

void standard_is_500_plus_100_per_started_kilogram() {
    ShippingRates r = make_rates();
    CHECK(r.cost("STANDARD", 0) == 500);
    CHECK(r.cost("STANDARD", 1) == 600);
    CHECK(r.cost("STANDARD", 1000) == 600);
    CHECK(r.cost("STANDARD", 1001) == 700);
}
void express_is_1200_plus_200_per_started_kilogram() {
    ShippingRates r = make_rates();
    CHECK(r.cost("EXPRESS", 2500) == 1800);
}
void pickup_is_free() {
    ShippingRates r = make_rates();
    CHECK(r.cost("PICKUP", 123456) == 0);
}
void unknown_carrier_throws() {
    ShippingRates r = make_rates();
    CHECK_THROWS(r.cost("DRONE", 10));
}
void a_new_carrier_is_one_add_line_and_leaves_the_others_alone() {
    ShippingRates r = make_rates();
    r.add("SAMEDAY", [](long long g) { return 2500 + (g + 999) / 1000 * 300; });
    CHECK(r.cost("SAMEDAY", 1500) == 3100);
    CHECK(r.cost("STANDARD", 1500) == 700);
}

int main() {
    RUN(standard_is_500_plus_100_per_started_kilogram);
    RUN(express_is_1200_plus_200_per_started_kilogram);
    RUN(pickup_is_free);
    RUN(unknown_carrier_throws);
    RUN(a_new_carrier_is_one_add_line_and_leaves_the_others_alone);
    return check::report();
}
