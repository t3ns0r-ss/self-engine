#pragma once
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>

using RateFn = std::function<long long(long long)>;

// Shipping cost in cents by carrier and weight in grams.
class ShippingRates {
public:
    ShippingRates() {
        add("STANDARD", [](long long g) { return 500 + (g + 999) / 1000 * 100; });
        add("EXPRESS", [](long long g) { return 1200 + (g + 999) / 1000 * 200; });
        add("FREIGHT", [](long long g) { return 5000 + g / 10000 * 1500; });
        add("PICKUP", [](long long) { return 0LL; });
    }
    long long cost(const std::string& carrier, long long grams) const {
        auto it = rates_.find(carrier);
        if (it == rates_.end()) throw std::invalid_argument("unknown carrier: " + carrier);
        return it->second(grams);
    }
    // Adds a carrier, or replaces the rate of an existing one.
    void add(const std::string& carrier, RateFn rate) {
        if (!rate) throw std::invalid_argument("empty rate for " + carrier);
        rates_[carrier] = std::move(rate);
    }
private:
    std::map<std::string, RateFn> rates_;
};
