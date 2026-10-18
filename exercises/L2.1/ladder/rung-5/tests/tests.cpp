#include "check.hpp"
#include "parking.hpp"

void cars_pay_the_old_fees() {
    CHECK(Parking("HOURLY").fee(61, Vehicle::Car) == 40);
    CHECK(Parking("DAILY").fee(1441, Vehicle::Car) == 200);
    CHECK(Parking("WEEKEND").fee(61, Vehicle::Car) == 80);
    CHECK(Parking("MEMBER", 25).fee(61, Vehicle::Car) == 30);
}

void trucks_pay_double_hourly() {
    CHECK(Parking("HOURLY").fee(61, Vehicle::Truck) == 80);
    CHECK(Parking("HOURLY").fee(60, Vehicle::Truck) == 40);
}

void trucks_pay_fifty_more_for_each_started_day() {
    CHECK(Parking("DAILY").fee(1, Vehicle::Truck) == 150);
    CHECK(Parking("DAILY").fee(1441, Vehicle::Truck) == 300);
}

void weekend_is_the_same_for_trucks() {
    CHECK(Parking("WEEKEND").fee(61, Vehicle::Truck) == 80);
}

void member_discount_applies_to_the_truck_fee() {
    CHECK(Parking("MEMBER", 25).fee(61, Vehicle::Truck) == 60);   // truck hourly 80, minus 25 per cent
}

void invalid_input_is_still_rejected() {
    CHECK_THROWS(Parking("MONTHLY"));
    CHECK_THROWS(Parking("HOURLY").fee(-1, Vehicle::Car));
    CHECK_THROWS(Parking("MEMBER", 101));
}

int main() {
    RUN(cars_pay_the_old_fees);
    RUN(trucks_pay_double_hourly);
    RUN(trucks_pay_fifty_more_for_each_started_day);
    RUN(weekend_is_the_same_for_trucks);
    RUN(member_discount_applies_to_the_truck_fee);
    RUN(invalid_input_is_still_rejected);
    return check::report();
}
