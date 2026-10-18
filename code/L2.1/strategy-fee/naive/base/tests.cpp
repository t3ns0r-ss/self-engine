#include "check.hpp"
#include "fee_calculator.hpp"

void hourly_rounds_up_started_hours() {
    FeeCalculator calc;
    CHECK(calc.fee("HOURLY", 1) == 20);
    CHECK(calc.fee("HOURLY", 60) == 20);
    CHECK(calc.fee("HOURLY", 61) == 40);
}
void daily_rounds_up_started_days() {
    FeeCalculator calc;
    CHECK(calc.fee("DAILY", 1) == 100);
    CHECK(calc.fee("DAILY", 1440) == 100);
    CHECK(calc.fee("DAILY", 1441) == 200);
}
void zero_minutes_is_free() {
    FeeCalculator calc;
    CHECK(calc.fee("DAILY", 0) == 0);
}
void unknown_plan_throws() {
    FeeCalculator calc;
    CHECK_THROWS(calc.fee("MONTHLY", 10));
}

int main() {
    RUN(hourly_rounds_up_started_hours);
    RUN(daily_rounds_up_started_days);
    RUN(zero_minutes_is_free);
    RUN(unknown_plan_throws);
    return check::report();
}
