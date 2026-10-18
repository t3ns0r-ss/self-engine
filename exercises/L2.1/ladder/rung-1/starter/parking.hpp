#pragma once
#include <stdexcept>
#include <string>

// Prices a parking stay. Plans are chosen by name: "HOURLY" and "DAILY".
class FeeService {
public:
    long long fee(const std::string&, long long) const { throw std::logic_error("not implemented"); }
};
