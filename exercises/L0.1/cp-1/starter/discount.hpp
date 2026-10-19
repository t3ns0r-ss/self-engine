// cp-1: a Percentage and a Discount that cannot hold bad values.
#pragma once
#include <stdexcept>

// Percentage(v): v must be 0 to 100 inclusive, otherwise std::invalid_argument. of(cents) is cents * v / 100 rounded
// down; it throws std::invalid_argument for a negative amount.
class Percentage {
public:
    explicit Percentage(int value) { throw std::logic_error("not implemented"); }
    int value() const { throw std::logic_error("not implemented"); }
    long long of(long long cents) const { throw std::logic_error("not implemented"); }
};

// Discount(percent, min_spend): min_spend (cents) must not be negative, otherwise std::invalid_argument.
// apply(total) returns total minus percent.of(total) when total >= min_spend, otherwise total unchanged; it throws
// std::invalid_argument for a negative total. none() is a discount that changes nothing.
// Neither class may let a bad value in at any point of its life.
class Discount {
public:
    Discount(Percentage percent, long long min_spend) { throw std::logic_error("not implemented"); }
    static Discount none() { throw std::logic_error("not implemented"); }
    long long apply(long long total_cents) const { throw std::logic_error("not implemented"); }
};
