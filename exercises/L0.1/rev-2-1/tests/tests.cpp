#include <stdexcept>
#include <type_traits>

#include "check.hpp"
#include "duration.hpp"

static_assert(!std::is_aggregate_v<Duration>);

void minutes_and_seconds_are_split() {
    Duration d = Duration::from_seconds(135);
    CHECK(d.minutes() == 2);
    CHECK(d.seconds_part() == 15);
    CHECK(d.total_seconds() == 135);
}
void minutes_round_down() {
    CHECK(Duration::from_seconds(119).minutes() == 1);
    CHECK(Duration::from_seconds(59).minutes() == 0);
    CHECK(Duration::from_seconds(60).minutes() == 1);
}
void from_minutes_stores_seconds() {
    CHECK(Duration::from_minutes(3).total_seconds() == 180);
    CHECK(Duration::from_minutes(0).total_seconds() == 0);
}
void negative_durations_are_refused() {
    CHECK_THROWS(Duration::from_seconds(-1));
    CHECK_THROWS(Duration::from_minutes(-1));
}
void plus_returns_a_new_duration_and_leaves_the_operands() {
    Duration a = Duration::from_seconds(50), b = Duration::from_seconds(20);
    Duration c = a.plus(b);
    CHECK(c.total_seconds() == 70);
    CHECK(a.total_seconds() == 50);
    CHECK(b.total_seconds() == 20);
}
void seconds_part_stays_below_60() {
    for (long long s = 0; s < 400; s += 7) CHECK(Duration::from_seconds(s).seconds_part() < 60);
}
int main() {
    RUN(minutes_and_seconds_are_split);
    RUN(minutes_round_down);
    RUN(from_minutes_stores_seconds);
    RUN(negative_durations_are_refused);
    RUN(plus_returns_a_new_duration_and_leaves_the_operands);
    RUN(seconds_part_stays_below_60);
    return check::report();
}
