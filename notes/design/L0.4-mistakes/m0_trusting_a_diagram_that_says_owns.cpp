// The diagram says "Shop *-- Order", so the author assumes that destroying a shop destroys its orders.
// The header holds raw pointers, so nothing does: the diagram and the code disagree.
#include <cstdio>
#include <vector>

int live_orders = 0;
struct Order {
    Order() { ++live_orders; }
    ~Order() { --live_orders; }
};
class Shop {
public:
    Order& place() { orders_.push_back(new Order); return *orders_.back(); }
private:
    std::vector<Order*> orders_;              // the code says "refers to", the diagram said "owns"
};

int main() {
    {
        Shop shop;
        shop.place();
        shop.place();
    }
    std::printf("orders alive after the shop is gone: %d (the diagram promised 0)\n", live_orders);
    std::fflush(stdout);                      // the leak checker ends the process before the buffer is flushed
}
