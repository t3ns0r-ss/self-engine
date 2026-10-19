#include <cstdio>

struct Base {
    Base() { std::printf("constructing, name = %s\n", name()); }       // MISTAKE: virtual call while Base is being built
    virtual ~Base() = default;
    virtual const char* name() const { return "Base"; }
};
struct Derived : Base {
    const char* name() const override { return "Derived"; }
};

int main() {
    Derived d;
    std::printf("after construction, name = %s\n", d.name());
}
