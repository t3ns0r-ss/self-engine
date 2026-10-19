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
    Duration plus(const Duration& other) const { return Duration(seconds_ + other.seconds_); }
private:
    explicit Duration(long long s) : seconds_(s) {
    }
    long long seconds_;
};
