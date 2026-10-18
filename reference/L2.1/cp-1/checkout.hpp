#pragma once
#include <algorithm>
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

struct Item {
    std::string name;
    long long price_cents;
};

// A rule takes the undiscounted basket and returns the total to pay.
using Rule = std::function<long long(const std::vector<Item>&)>;

inline long long sum_of(const std::vector<Item>& basket) {
    long long sum = 0;
    for (const Item& item : basket) sum += item.price_cents;
    return sum;
}

// Totals a basket under one named discount rule: NONE, PERCENT10, FIXED5, CHEAPEST_FREE, BULK.
class Checkout {
public:
    Checkout() {
        rules_["NONE"] = [](const std::vector<Item>& b) { return sum_of(b); };
        rules_["PERCENT10"] = [](const std::vector<Item>& b) { return sum_of(b) * 90 / 100; };
        rules_["FIXED5"] = [](const std::vector<Item>& b) { long long s = sum_of(b); return s >= 2000 ? s - 500 : s; };
        rules_["CHEAPEST_FREE"] = [](const std::vector<Item>& b) {
            if (b.size() < 3) return sum_of(b);
            auto cheapest = std::min_element(b.begin(), b.end(), [](const Item& x, const Item& y) { return x.price_cents < y.price_cents; });
            return sum_of(b) - cheapest->price_cents;
        };
        rules_["BULK"] = [](const std::vector<Item>& b) { long long s = sum_of(b); return b.size() >= 10 ? s * 85 / 100 : s; };
    }
    long long total(const std::vector<Item>& basket, const std::string& rule) const {
        for (const Item& item : basket) if (item.price_cents < 0) throw std::invalid_argument("negative price");
        auto it = rules_.find(rule);
        if (it == rules_.end()) throw std::invalid_argument("unknown rule: " + rule);
        return it->second(basket);
    }
private:
    std::map<std::string, Rule> rules_;
};
