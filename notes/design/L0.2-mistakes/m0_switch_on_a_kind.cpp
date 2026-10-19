#include <cstdio>
#include <vector>

enum class Kind { Rect, Square, Triangle };           // Triangle was added last month
struct Shape { Kind kind; long long a, b; };

long long area(const Shape& s) {
    switch (s.kind) {
        case Kind::Rect: return s.a * s.b;
        case Kind::Square: return s.a * s.a;
        default: return 0;                             // MISTAKE: the new kind was added to the enum and to perimeter(), not here
    }
}
long long perimeter(const Shape& s) {
    switch (s.kind) {
        case Kind::Rect: return 2 * (s.a + s.b);
        case Kind::Square: return 4 * s.a;
        case Kind::Triangle: return 3 * s.a;
    }
    return 0;
}

int main() {
    std::vector<Shape> shapes{{Kind::Rect, 3, 4}, {Kind::Triangle, 6, 5}};
    long long total = 0, edge = 0;
    for (const Shape& s : shapes) { total += area(s); edge += perimeter(s); }
    std::printf("total area = %lld (expected 27), total perimeter = %lld\n", total, edge);
    return total == 27 ? 0 : 1;
}
