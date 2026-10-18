#pragma once
#include "pricing_strategy.hpp"

class DailyPricing final : public PricingStrategy {
public:
    long long fee(long long minutes) const override { return (minutes / 1440 + 1) * 100; }
};
