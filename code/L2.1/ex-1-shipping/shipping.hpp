#pragma once
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>

// The shared signature: grams in, cost in cents out.
using RateFn = std::function<long long(long long grams)>;

class ShippingRates {
public:
    void add(const std::string& carrier, RateFn rate) { rates_[carrier] = std::move(rate); }
    long long cost(const std::string& carrier, long long grams) const {
        auto it = rates_.find(carrier);
        if (it == rates_.end()) throw std::invalid_argument("unknown carrier: " + carrier);
        return it->second(grams);
    }
private:
    std::map<std::string, RateFn> rates_;
};

// The only place that knows which carriers exist. A new carrier is one more add() line here.
inline ShippingRates make_rates() {
    ShippingRates r;
    r.add("STANDARD", [](long long g) { return 500 + (g + 999) / 1000 * 100; });
    r.add("EXPRESS", [](long long g) { return 1200 + (g + 999) / 1000 * 200; });
    r.add("PICKUP", [](long long) { return 0LL; });
    return r;
}
