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

int main() {
    RUN(hourly_rounds_up_started_hours);
    RUN(daily_rounds_up_started_days);
    RUN(zero_minutes_cost_nothing);
    RUN(unknown_plan_is_rejected);
    RUN(plan_names_are_case_sensitive);
    RUN(negative_minutes_are_rejected);
    return check::report();
}
