// The public header of the L0.1 ladder: every rung adds one piece to this file.
#pragma once
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

// Rung 1: a Money that can never hold a bad value.
// The rule for every Money, for its whole life: cents >= 0 and the currency is exactly three capital letters.
// The constructor throws std::invalid_argument if either part is wrong. Keep the fields private.
class Money {
public:
    Money(long long cents, std::string currency) { throw std::logic_error("not implemented"); }
    long long cents() const { throw std::logic_error("not implemented"); }
    const std::string& currency() const { throw std::logic_error("not implemented"); }
private:
    long long cents_ = 0;
    std::string currency_;
};

