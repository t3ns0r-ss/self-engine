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
        if (cents_ < 0) cents_ = 0;
        if (!valid_currency(currency_)) throw std::invalid_argument("currency must be three capital letters");
    }
    long long cents() const { return cents_; }
    const std::string& currency() const { return currency_; }
private:
    static bool valid_currency(const std::string& c) {
        if (c.size() != 3) return false;
        for (char ch : c) if (ch < 'A' || ch > 'Z') return false;
        return true;
    }
    long long cents_;
    std::string currency_;
};

