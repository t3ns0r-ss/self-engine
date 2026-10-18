#pragma once
#include <functional>
#include <stdexcept>
#include <string>

// Shipping cost in cents by carrier and weight in grams.
class ShippingRates {
public:
    long long cost(const std::string& carrier, long long grams) const {
        if (carrier == "STANDARD") return 500 + (grams + 999) / 1000 * 100;
        if (carrier == "EXPRESS") return 1200 + (grams + 999) / 1000 * 200;
        if (carrier == "FREIGHT") return 5000 + (grams + 9999) / 10000 * 1500;
        if (carrier == "PICKUP") return 0;
        throw std::invalid_argument("unknown carrier: " + carrier);
    }
    // Adds a carrier, or replaces the rate of an existing one. Not supported yet.
    void add(const std::string&, std::function<long long(long long)>) { throw std::logic_error("not implemented"); }
};
