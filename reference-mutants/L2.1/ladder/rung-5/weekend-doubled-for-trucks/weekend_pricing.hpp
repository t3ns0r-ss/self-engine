#pragma once
#include "pricing_strategy.hpp"

class WeekendPricing final : public PricingStrategy {
public:
    long long fee(long long minutes, Vehicle vehicle) const override { return (minutes + 59) / 60 * (vehicle == Vehicle::Truck ? 80 : 40); }
};
