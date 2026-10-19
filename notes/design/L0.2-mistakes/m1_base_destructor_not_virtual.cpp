#include <cstdio>
#include <memory>
#include <vector>

struct Handler {
    ~Handler() {}                                  // MISTAKE: not virtual
    virtual int id() const = 0;
};
struct Buffered : Handler {
    std::vector<char> buffer = std::vector<char>(4096, 'x');
    ~Buffered() { std::puts("~Buffered ran"); }
    int id() const override { return 7; }
};

int main() {
    Handler* h = new Buffered;
    std::printf("id = %d\n", h->id());
    delete h;                                      // runs ~Handler only: the 4096 bytes are never released
    std::puts("done");
}
