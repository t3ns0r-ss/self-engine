#include <cstdio>
#include <vector>

struct Shape {
    virtual ~Shape() = default;
    virtual long long area() const { return 0; }
};
struct Rect : Shape {
    long long w, h;
    Rect(long long w, long long h) : w(w), h(h) {}
    long long area() const override { return w * h; }
};

int main() {
    std::vector<Shape> shapes;                     // MISTAKE: Shape by value, not Shape* or unique_ptr<Shape>
    shapes.push_back(Rect(3, 4));                  // copies only the Shape part: the Rect part is cut off
    std::printf("area = %lld (expected 12)\n", shapes[0].area());
    return shapes[0].area() == 12 ? 0 : 1;
}
