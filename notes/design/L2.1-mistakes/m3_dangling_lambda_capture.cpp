#include <functional>
#include <iostream>

using FeeFn = std::function<long long(long long)>;

FeeFn make_hourly(long long rate) {
    return [&rate](long long minutes) { return (minutes + 59) / 60 * rate; };   // MISTAKE: captures the parameter by reference
}

int main() {
    FeeFn plan = make_hourly(20);   // `rate` is gone as soon as make_hourly returns
    std::cout << plan(120) << "\n";
}
