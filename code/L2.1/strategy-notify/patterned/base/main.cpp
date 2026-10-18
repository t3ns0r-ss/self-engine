#include <iostream>
#include "make_notifier.hpp"

int main() {
    Notifier n = make_notifier();
    std::cout << n.send("EMAIL", "ann", "your parcel has arrived") << "\n";
    std::cout << n.send("SMS", "ann", "your parcel has arrived") << "\n";
}
