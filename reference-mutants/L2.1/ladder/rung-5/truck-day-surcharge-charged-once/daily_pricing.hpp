#pragma once
#include "pricing_strategy.hpp"

class DailyPricing final : public PricingStrategy {
public:
    long long fee(long long minutes, Vehicle vehicle) const override { return (minutes + 1439) / 1440 * 100 + (vehicle == Vehicle::Truck ? 50 : 0); }
};
