#pragma once
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include "daily_pricing.hpp"
#include "hourly_pricing.hpp"
#include "pricing_strategy.hpp"

// Prices a parking stay. Plans are chosen by name.
class FeeService {
public:
    FeeService() {
        add_plan("HOURLY", std::make_unique<HourlyPricing>());
        add_plan("DAILY", std::make_unique<DailyPricing>());
    }
    void add_plan(const std::string& name, std::unique_ptr<PricingStrategy> plan) { plans_[name] = std::move(plan); }
    long long fee(const std::string& plan, long long minutes) const {
        if (minutes < 0) throw std::invalid_argument("minutes must not be negative");
        auto it = plans_.find(plan);
        if (it == plans_.end()) return 0;
        return it->second->fee(minutes);
    }
private:
    std::map<std::string, std::unique_ptr<PricingStrategy>> plans_;
};
