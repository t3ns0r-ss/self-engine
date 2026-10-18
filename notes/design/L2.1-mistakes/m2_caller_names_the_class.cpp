#include <memory>
#include <string>

class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual long long fee(long long minutes) const = 0;
};
class HourlyPricing final : public PricingStrategy {
public:
    long long fee(long long minutes) const override { return (minutes + 59) / 60 * 20; }
};
class WeekendPricing final : public PricingStrategy {
public:
    long long fee(long long minutes) const override { return (minutes + 59) / 60 * 40; }
};

// MISTAKE: the caller asks which class it has been given, so every new plan must be added here too.
long long bill(const PricingStrategy& plan, long long minutes) {
    if (dynamic_cast<const HourlyPricing*>(&plan)) return plan.fee(minutes);
    if (dynamic_cast<const WeekendPricing*>(&plan)) return plan.fee(minutes);
    return -1;   // a plan added later falls through here
}

class DailyPricing final : public PricingStrategy {   // added later; bill() was never told
public:
    long long fee(long long minutes) const override { return (minutes + 1439) / 1440 * 100; }
};

int main() {
    DailyPricing daily;
    return bill(daily, 90) == 100 ? 0 : 1;   // expected a fee of 100; bill() answers -1
}
