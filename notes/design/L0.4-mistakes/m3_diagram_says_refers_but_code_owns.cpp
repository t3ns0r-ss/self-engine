// The diagram says "Shop o-- Order" (refers to), so the author thinks the orders belong to someone else and deletes one.
// The header holds std::unique_ptr<Order>: the shop owns them, and the shop deletes the order a second time.
#include <memory>
#include <vector>

struct Order { int id = 0; };
class Shop {
public:
    Order& place() { orders_.push_back(std::make_unique<Order>()); return *orders_.back(); }
private:
    std::vector<std::unique_ptr<Order>> orders_;   // the code says "owns", the diagram said "refers to"
};

int main() {
    Shop shop;
    Order& o = shop.place();
    delete &o;                                      // "the shop only refers to it, so I clean it up"
}
