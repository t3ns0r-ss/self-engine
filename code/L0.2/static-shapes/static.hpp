// Static polymorphism: the same promise, checked at compile time. No base class, no hidden pointer.
#pragma once
#include <concepts>
#include <variant>
#include <vector>

template <class S>
concept HasArea = requires(const S& s) { { s.area() } -> std::convertible_to<long long>; };

struct SRect {
    long long w, h;
    long long area() const { return w * h; }
};
struct SSquare {
    long long side;
    long long area() const { return side * side; }
};
struct STriangle {
    long long b, h;
    long long area() const { return b * h / 2; }
};

// One call per type, resolved when the program is compiled.
template <HasArea S>
long long area_of(const S& s) { return s.area(); }

// All elements have the SAME type S.
template <HasArea S>
long long total_area(const std::vector<S>& items) {
    long long sum = 0;
    for (const S& s : items) sum += area_of(s);
    return sum;
}

// A closed set of types chosen at compile time: a variant. The set cannot grow without editing this line.
using AnyShape = std::variant<SRect, SSquare, STriangle>;
inline long long total_area_of_any(const std::vector<AnyShape>& items) {
    long long sum = 0;
    for (const AnyShape& s : items) sum += std::visit([](const auto& x) { return x.area(); }, s);
    return sum;
}
