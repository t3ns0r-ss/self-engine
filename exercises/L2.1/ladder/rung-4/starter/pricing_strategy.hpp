#pragma once

// The one signature every parking plan shares.
class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual long long fee(long long minutes) const = 0;
};
