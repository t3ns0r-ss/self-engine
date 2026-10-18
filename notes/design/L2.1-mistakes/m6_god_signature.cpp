#include <string>

// MISTAKE: to make "one signature fit every variant", the interface takes everything any variant might want.
struct Context {
    long long minutes = 0;
    bool is_truck = false;
    bool is_member = false;
    int hour_of_day = 0;
    std::string promo_code;
};
class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual long long fee(const Context&) const = 0;
};
class HourlyPricing final : public PricingStrategy {
public:
    long long fee(const Context& c) const override { return (c.minutes + 59) / 60 * 20; }   // ignores 4 of 5 fields
};
class MemberPricing final : public PricingStrategy {
public:
    long long fee(const Context& c) const override { return c.is_member ? 0 : (c.minutes + 59) / 60 * 20; }
};
int main() {
    Context c; c.minutes = 90; c.is_member = true;
    return HourlyPricing().fee(c) == 40 && MemberPricing().fee(c) == 0 ? 0 : 1;
}
