#pragma once
#include "hourly_pricing.hpp"

// Hourly pricing with a percentage taken off, rounded down.
class MemberPricing final : public PricingStrategy {
public:
    explicit MemberPricing(int discount_percent) : discount_percent_(discount_percent) {}
    long long fee(long long minutes) const override {
        return base_.fee(minutes) * (100 - discount_percent_) / 100;
    }
private:
    HourlyPricing base_;
    int discount_percent_;
};
