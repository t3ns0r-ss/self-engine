#pragma once
#include <memory>
#include "daily_pricing.hpp"
#include "fee_calculator.hpp"
#include "hourly_pricing.hpp"

// Wiring: the only place that knows which plans exist.
inline FeeCalculator make_calculator() {
    FeeCalculator calc;
    calc.add_plan("HOURLY", std::make_unique<HourlyPricing>());
    calc.add_plan("DAILY", std::make_unique<DailyPricing>());
    return calc;
}
