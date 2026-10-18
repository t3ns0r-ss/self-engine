#pragma once
#include <stdexcept>
#include <string>
#include <vector>

struct Item {
    std::string name;
    long long price_cents;
};

// Totals a basket under one named discount rule: NONE, PERCENT10, FIXED5, CHEAPEST_FREE, BULK.
class Checkout {
public:
    long long total(const std::vector<Item>&, const std::string&) const { throw std::logic_error("not implemented"); }
};
