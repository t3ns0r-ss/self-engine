// rev-2-1: a duration that stores seconds and exposes minutes.
#pragma once
#include <stdexcept>

class Duration {
public:
    static Duration from_seconds(long long s) { return Duration(s); }
    static Duration from_minutes(long long m) { return Duration(m * 60); }
    long long total_seconds() const { return seconds_; }
    long long minutes() const { return seconds_ / 60; }            // whole minutes, rounded down
    long long seconds_part() const { return seconds_ % 60; }
    Duration plus(const Duration& other) const { return Duration(seconds_ + other.seconds_ / 60); }
private:
    explicit Duration(long long s) : seconds_(s) {
        if (s < 0) throw std::invalid_argument("a duration is not negative");
    }
    long long seconds_;
};
