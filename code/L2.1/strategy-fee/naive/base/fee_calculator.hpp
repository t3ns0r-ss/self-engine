#pragma once
#include <stdexcept>
#include <string>

class FeeCalculator {
public:
    long long fee(const std::string& plan, long long minutes) const {
        if (plan == "HOURLY") return (minutes + 59) / 60 * 20;
        if (plan == "DAILY") return (minutes + 1439) / 1440 * 100;
        throw std::invalid_argument("unknown plan: " + plan);
    }
};
