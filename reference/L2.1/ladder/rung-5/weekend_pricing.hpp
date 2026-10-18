#pragma once
#include "pricing_strategy.hpp"

class WeekendPricing final : public PricingStrategy {
public:
    long long fee(long long minutes, Vehicle) const override { return (minutes + 59) / 60 * 40; }
};
