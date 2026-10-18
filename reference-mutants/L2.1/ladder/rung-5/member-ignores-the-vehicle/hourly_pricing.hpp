#pragma once
#include "pricing_strategy.hpp"

class HourlyPricing final : public PricingStrategy {
public:
    long long fee(long long minutes, Vehicle vehicle) const override { return (minutes + 59) / 60 * (vehicle == Vehicle::Truck ? 40 : 20); }
};
