// cp-1: a Percentage and a Discount that cannot hold bad values.
#pragma once
#include <stdexcept>

class Percentage {
public:
    explicit Percentage(int value) : value_(value) {
        if (value < 0 || value > 100) throw std::invalid_argument("a percentage is 0 to 100");
    }
    int value() const { return value_; }
    long long of(long long cents) const {
        if (cents < 0) throw std::invalid_argument("negative amount");
        return cents * value_ / 100;           // rounded down
    }
private:
    int value_;
};

class Discount {
public:
    Discount(Percentage percent, long long min_spend) : percent_(percent), min_spend_(min_spend) {
    }
    static Discount none() { return Discount(Percentage(0), 0); }
    long long apply(long long total_cents) const {
        if (total_cents < 0) throw std::invalid_argument("negative total");
        return total_cents >= min_spend_ ? total_cents - percent_.of(total_cents) : total_cents;
    }
private:
    Percentage percent_;
    long long min_spend_;
};
