// flags: -Wno-error=overloaded-virtual -Wno-overloaded-virtual
#include <cstdio>

struct Shape {
    virtual ~Shape() = default;
    virtual long long area() const { return 0; }
};
struct Rect : Shape {
    long long w = 3, h = 4;
    long long area() { return w * h; }             // MISTAKE: no const, so this is a new function, not an override
};

int main() {
    Rect r;
    const Shape& s = r;
    std::printf("through the base: %lld (expected 12)\n", s.area());
    return s.area() == 12 ? 0 : 1;
}
