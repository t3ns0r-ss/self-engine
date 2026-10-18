#pragma once

// The one signature every pricing plan shares.
class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;   // deleting through a base pointer must run the derived destructor
    virtual long long fee(long long minutes) const = 0;
};
