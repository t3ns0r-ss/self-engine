#pragma once
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include "pricing_strategy.hpp"

class FeeCalculator {
public:
    void add_plan(const std::string& name, std::unique_ptr<PricingStrategy> plan) {
        plans_[name] = std::move(plan);
    }
    long long fee(const std::string& plan, long long minutes) const {
        auto it = plans_.find(plan);
        if (it == plans_.end()) throw std::invalid_argument("unknown plan: " + plan);
        return it->second->fee(minutes);
    }
private:
    std::map<std::string, std::unique_ptr<PricingStrategy>> plans_;
};
