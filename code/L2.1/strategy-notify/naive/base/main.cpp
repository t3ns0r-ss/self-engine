#include <iostream>
#include "notifier.hpp"

int main() {
    Notifier n;
    std::cout << n.send("EMAIL", "ann", "your parcel has arrived") << "\n";
    std::cout << n.send("SMS", "ann", "your parcel has arrived") << "\n";
}
