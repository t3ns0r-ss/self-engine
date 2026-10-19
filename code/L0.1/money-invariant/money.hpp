// Money: an amount in whole cents with a currency. The rule that holds for the whole life of every Money:
//   cents >= 0, and the currency is exactly three capital letters.
// The fields are private, so the constructor and add/subtract are the only ways to set them, and each one checks.
#pragma once
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>

class Money {
public:
    Money(long long cents, std::string currency) : cents_(cents), currency_(std::move(currency)) {
        if (cents_ < 0) throw std::invalid_argument("negative amount");
        if (!valid_currency(currency_)) throw std::invalid_argument("currency must be three capital letters");
    }
    long long cents() const { return cents_; }
    const std::string& currency() const { return currency_; }

    // Returns a new Money. Throws on different currencies, and std::overflow_error if the sum does not fit.
    Money add(const Money& other) const {
        if (currency_ != other.currency_) throw std::invalid_argument("different currencies");
        if (cents_ > std::numeric_limits<long long>::max() - other.cents_) throw std::overflow_error("sum too large");
        return Money(cents_ + other.cents_, currency_);
    }
    // Throws if the result would be negative.
    Money subtract(const Money& other) const {
        if (currency_ != other.currency_) throw std::invalid_argument("different currencies");
        if (other.cents_ > cents_) throw std::invalid_argument("result would be negative");
        return Money(cents_ - other.cents_, currency_);
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
