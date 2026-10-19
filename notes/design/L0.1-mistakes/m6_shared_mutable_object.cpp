#include <cstdio>
#include <memory>
#include <string>

struct Address { std::string street; };                       // MISTAKE: mutable, and shared by two orders

struct Order {
    std::shared_ptr<Address> address;
};

int main() {
    auto home = std::make_shared<Address>(Address{"1 Main St"});
    Order a{home}, b{home};
    a.address->street = "9 Side St";                           // meant to change order a only
    std::printf("order b ships to: %s\n", b.address->street.c_str());
    return b.address->street == "1 Main St" ? 0 : 1;
}
