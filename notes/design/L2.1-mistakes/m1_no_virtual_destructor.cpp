#include <memory>
#include <string>

class PricingStrategy {            // MISTAKE: the destructor is not virtual
public:
    virtual long long fee(long long minutes) const = 0;
};

class LoggingPricing final : public PricingStrategy {
public:
    long long fee(long long minutes) const override { return minutes; }
private:
    std::string log_ = std::string(100, 'x');   // owned memory the derived destructor must free
};

int main() {
    std::unique_ptr<PricingStrategy> p = std::make_unique<LoggingPricing>();
    return static_cast<int>(p->fee(3)) - 3;
}
