#include <functional>
#include <iostream>
#include <map>
#include <string>

using FeeFn = std::function<long long(long long)>;

int main() {
    std::map<std::string, FeeFn> plans;
    plans["HOURLY"] = [](long long m) { return (m + 59) / 60 * 20; };
    std::cout << plans["HOURLY"](60) << "\n";
    std::cout << plans["WEEKEND"](60) << "\n";   // MISTAKE: operator[] quietly inserted an empty std::function
}
