#include <iostream>

class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual long long fee(long long minutes) const = 0;
};
class HourlyPricing final : public PricingStrategy {
public:
    long long fee(long long minutes) const override { return (minutes + 59) / 60 * 20; }
};

class FeeCalculator {
public:
    explicit FeeCalculator(const PricingStrategy* plan) : plan_(plan) {}   // MISTAKE: stores a pointer it does not own
    long long fee(long long minutes) const { return plan_->fee(minutes); }
private:
    const PricingStrategy* plan_;
};

FeeCalculator make() {
    HourlyPricing plan;                // a local object, destroyed when make() returns
    return FeeCalculator(&plan);
}

int main() {
    FeeCalculator calc = make();
    std::cout << calc.fee(60) << "\n";
}
