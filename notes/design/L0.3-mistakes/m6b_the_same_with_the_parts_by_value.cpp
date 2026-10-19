#include <cstdio>
#include <cstdlib>
#include <new>
#include <vector>

static int allocations = 0;
void* operator new(std::size_t n) { ++allocations; void* p = std::malloc(n); if (!p) throw std::bad_alloc(); return p; }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }

struct Line { int sku; int quantity; };

class Order {
public:
    Order() { lines_.reserve(100); }
    void add(int sku, int quantity) { lines_.push_back(Line{sku, quantity}); }                          // composition: stored by value
    int total_quantity() const { int s = 0; for (const auto& l : lines_) s += l.quantity; return s; }
private:
    std::vector<Line> lines_;
};

int main() {
    Order o;
    for (int i = 0; i < 100; ++i) o.add(i, 2);
    std::printf("total = %d, allocations = %d, bytes per line held = %zu\n", o.total_quantity(), allocations, sizeof(Line));
}
