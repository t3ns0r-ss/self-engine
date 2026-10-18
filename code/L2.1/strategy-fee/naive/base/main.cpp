#include <iostream>
#include "fee_calculator.hpp"

int main() {
    FeeCalculator calc;
    std::cout << "HOURLY 150 minutes: " << calc.fee("HOURLY", 150) << "\n";
    std::cout << "DAILY 150 minutes: " << calc.fee("DAILY", 150) << "\n";
}
