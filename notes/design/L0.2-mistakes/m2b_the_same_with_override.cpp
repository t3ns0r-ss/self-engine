#include <cstdio>

struct Shape {
    virtual ~Shape() = default;
    virtual long long area() const { return 0; }
};
struct Rect : Shape {
    long long w = 3, h = 4;
    long long area() override { return w * h; }    // the keyword turns the silent mistake into a compile error
};

int main() {
    Rect r;
    std::printf("%lld\n", r.area());
}
