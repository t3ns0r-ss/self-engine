#pragma once
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include "daily_pricing.hpp"
#include "hourly_pricing.hpp"
#include "pricing_strategy.hpp"
#include "weekend_pricing.hpp"

// Prices a parking stay. Plans are chosen by name.
class FeeService {
public:
    FeeService() {
        add_plan("HOURLY", std::make_unique<HourlyPricing>());
        add_plan("DAILY", std::make_unique<DailyPricing>());
        add_plan("WEEKEND", std::make_unique<WeekendPricing>());
    }
    void add_plan(const std::string& name, std::unique_ptr<PricingStrategy> plan) { plans_[name] = std::move(plan); }
    bool has_plan(const std::string& name) const { return plans_.count(name) != 0; }
    long long fee(const std::string& plan, long long minutes) const {
        if (minutes < 0) throw std::invalid_argument("minutes must not be negative");
        auto it = plans_.find(plan);
        if (it == plans_.end()) throw std::invalid_argument("unknown plan: " + plan);
        return it->second->fee(minutes);
    }
private:
    std::map<std::string, std::unique_ptr<PricingStrategy>> plans_;
};

// One parking plan, chosen once from a setting.
class Parking {
public:
    explicit Parking(const std::string& plan) : plan_(plan) {
    }
    long long fee(long long minutes) const { return service_.fee(plan_, minutes); }
private:
    FeeService service_;
    std::string plan_;
};
