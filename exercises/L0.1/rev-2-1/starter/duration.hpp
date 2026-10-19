// rev-2-1: a duration that stores seconds and exposes minutes.
#pragma once
#include <stdexcept>

// A Duration is never negative and never changes after it is built. It is made with from_seconds or from_minutes
// (both throw std::invalid_argument for a negative number). minutes() is the whole minutes rounded down,
// seconds_part() the seconds left over (0 to 59). plus returns a new Duration.
class Duration {
public:
    static Duration from_seconds(long long s) { throw std::logic_error("not implemented"); }
    static Duration from_minutes(long long m) { throw std::logic_error("not implemented"); }
    long long total_seconds() const { throw std::logic_error("not implemented"); }
    long long minutes() const { throw std::logic_error("not implemented"); }
    long long seconds_part() const { throw std::logic_error("not implemented"); }
    Duration plus(const Duration& other) const { throw std::logic_error("not implemented"); }
};
