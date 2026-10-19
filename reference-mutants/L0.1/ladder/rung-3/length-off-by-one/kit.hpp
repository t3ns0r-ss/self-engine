// The public header of the L0.1 ladder: every rung adds one piece to this file.
#pragma once
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

// Rung 1: a Money that can never hold a bad value.
class Money {
public:
    Money(long long cents, std::string currency) : cents_(cents), currency_(std::move(currency)) {
        if (cents_ < 0) throw std::invalid_argument("negative amount");
        if (!valid_currency(currency_)) throw std::invalid_argument("currency must be three capital letters");
    }
    long long cents() const { return cents_; }
    const std::string& currency() const { return currency_; }

    // Rung 2: returns a new Money; throws std::invalid_argument for different currencies and std::overflow_error
    // if the sum does not fit in a long long.
    Money add(const Money& other) const {
        if (currency_ != other.currency_) throw std::invalid_argument("different currencies");
        if (cents_ > std::numeric_limits<long long>::max() - other.cents_) throw std::overflow_error("sum too large");
        return Money(cents_ + other.cents_, currency_);
    }
private:
    static bool valid_currency(const std::string& c) {
        if (c.size() != 3) return false;
        for (char ch : c) if (ch < 'A' || ch > 'Z') return false;
        return true;
    }
    long long cents_;
    std::string currency_;
};

// Rung 3: an immutable date range. Every field is set once, in the constructor.
class DateRange {
public:
    DateRange(int start, int end) : start_(start), end_(end) {
        if (start > end) throw std::invalid_argument("start after end");
    }
    int start() const { return start_; }
    int end() const { return end_; }
    int length() const { return end_ - start_ + 1; }
    DateRange with_start(int start) const { return DateRange(start, end_); }
    DateRange with_end(int end) const { return DateRange(start_, end); }
private:
    int start_;
    int end_;
};

