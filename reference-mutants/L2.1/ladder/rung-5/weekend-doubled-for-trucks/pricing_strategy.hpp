#pragma once

enum class Vehicle { Car, Truck };

// The one signature every parking plan shares.
class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual long long fee(long long minutes, Vehicle vehicle) const = 0;
};
