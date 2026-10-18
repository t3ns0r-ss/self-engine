#include "check.hpp"
#include "shipping.hpp"

void the_four_built_in_carriers_keep_their_rates() {
    ShippingRates r;
    CHECK(r.cost("STANDARD", 1001) == 700);
    CHECK(r.cost("EXPRESS", 2500) == 1800);
    CHECK(r.cost("FREIGHT", 10001) == 8000);
    CHECK(r.cost("FREIGHT", 10000) == 6500);
    CHECK(r.cost("PICKUP", 99999) == 0);
}
void unknown_carrier_throws() {
    ShippingRates r;
    CHECK_THROWS(r.cost("DRONE", 10));
}
void a_carrier_can_be_added() {
    ShippingRates r;
    r.add("SAMEDAY", [](long long g) { return 2500 + (g + 999) / 1000 * 300; });
    CHECK(r.cost("SAMEDAY", 1500) == 3100);
    CHECK(r.cost("STANDARD", 1500) == 700);
}
void adding_an_existing_carrier_replaces_its_rate() {
    ShippingRates r;
    r.add("PICKUP", [](long long) { return 100LL; });
    CHECK(r.cost("PICKUP", 1) == 100);
}
void an_empty_rate_is_rejected() {
    ShippingRates r;
    CHECK_THROWS(r.add("BAD", std::function<long long(long long)>{}));
}

int main() {
    RUN(the_four_built_in_carriers_keep_their_rates);
    RUN(unknown_carrier_throws);
    RUN(a_carrier_can_be_added);
    RUN(adding_an_existing_carrier_replaces_its_rate);
    RUN(an_empty_rate_is_rejected);
    return check::report();
}
