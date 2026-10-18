#include "check.hpp"
#include "parking.hpp"

void hourly_rounds_up_started_hours() {
    FeeService s;
    CHECK(s.fee("HOURLY", 1) == 20);
    CHECK(s.fee("HOURLY", 60) == 20);
    CHECK(s.fee("HOURLY", 61) == 40);
    CHECK(s.fee("HOURLY", 120) == 40);
    CHECK(s.fee("HOURLY", 121) == 60);
}

void daily_rounds_up_started_days() {
    FeeService s;
    CHECK(s.fee("DAILY", 1) == 100);
    CHECK(s.fee("DAILY", 1440) == 100);
    CHECK(s.fee("DAILY", 1441) == 200);
}

void zero_minutes_cost_nothing() {
    FeeService s;
    CHECK(s.fee("HOURLY", 0) == 0);
    CHECK(s.fee("DAILY", 0) == 0);
}

void unknown_plan_is_rejected() {
    FeeService s;
    CHECK_THROWS(s.fee("MONTHLY", 10));
}

void plan_names_are_case_sensitive() {
    FeeService s;
    CHECK_THROWS(s.fee("hourly", 10));
}

void negative_minutes_are_rejected() {
    FeeService s;
    CHECK_THROWS(s.fee("HOURLY", -1));
    CHECK_THROWS(s.fee("DAILY", -1));
}

void weekend_is_forty_per_started_hour() {
    FeeService s;
    CHECK(s.fee("WEEKEND", 1) == 40);
    CHECK(s.fee("WEEKEND", 60) == 40);
    CHECK(s.fee("WEEKEND", 61) == 80);
    CHECK(s.fee("WEEKEND", 0) == 0);
}

void adding_weekend_leaves_the_other_plans_alone() {
    FeeService s;
    CHECK(s.fee("HOURLY", 61) == 40);
    CHECK(s.fee("DAILY", 1) == 100);
}

void parking_charges_by_the_chosen_plan() {
    CHECK(Parking("HOURLY").fee(61) == 40);
    CHECK(Parking("DAILY").fee(1441) == 200);
    CHECK(Parking("WEEKEND").fee(61) == 80);
}

void parking_rejects_an_unknown_plan_when_created() {
    CHECK_THROWS(Parking("MONTHLY"));
}

void parking_rejects_negative_minutes() {
    const Parking p("HOURLY");
    CHECK_THROWS(p.fee(-5));
}

void member_takes_a_percentage_off_the_hourly_fee() {
    CHECK(Parking("MEMBER", 25).fee(61) == 30);
    CHECK(Parking("MEMBER", 25).fee(31) == 15);
    CHECK(Parking("MEMBER", 0).fee(61) == 40);
    CHECK(Parking("MEMBER", 100).fee(61) == 0);
    CHECK(Parking("MEMBER", 25).fee(0) == 0);
}

void member_discount_rounds_down() {
    CHECK(Parking("MEMBER", 33).fee(61) == 26);   // 40 * 67 / 100 = 26.8, rounded down
}

void member_discount_must_be_0_to_100() {
    CHECK_THROWS(Parking("MEMBER", -1));
    CHECK_THROWS(Parking("MEMBER", 101));
}

void other_plans_ignore_the_discount() {
    CHECK(Parking("HOURLY", 25).fee(61) == 40);
    CHECK(Parking("DAILY", 25).fee(1) == 100);
    CHECK(Parking("WEEKEND", 25).fee(61) == 80);
}

int main() {
    RUN(hourly_rounds_up_started_hours);
    RUN(daily_rounds_up_started_days);
    RUN(zero_minutes_cost_nothing);
    RUN(unknown_plan_is_rejected);
    RUN(plan_names_are_case_sensitive);
    RUN(negative_minutes_are_rejected);
    RUN(weekend_is_forty_per_started_hour);
    RUN(adding_weekend_leaves_the_other_plans_alone);
    RUN(parking_charges_by_the_chosen_plan);
    RUN(parking_rejects_an_unknown_plan_when_created);
    RUN(parking_rejects_negative_minutes);
    RUN(member_takes_a_percentage_off_the_hourly_fee);
    RUN(member_discount_rounds_down);
    RUN(member_discount_must_be_0_to_100);
    RUN(other_plans_ignore_the_discount);
    return check::report();
}
