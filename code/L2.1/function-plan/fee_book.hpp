#pragma once
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>

// A plan is any callable that takes minutes and returns a fee: a lambda, a plain function, or an object with operator().
using FeeFn = std::function<long long(long long)>;

class FeeBook {
public:
    void add(const std::string& name, FeeFn plan) {
        if (!plan) throw std::invalid_argument("empty plan: " + name);   // an empty std::function throws when called
        plans_[name] = std::move(plan);
    }
    long long fee(const std::string& name, long long minutes) const {
        auto it = plans_.find(name);
        if (it == plans_.end()) throw std::invalid_argument("unknown plan: " + name);
        return it->second(minutes);
    }
private:
    std::map<std::string, FeeFn> plans_;
};
