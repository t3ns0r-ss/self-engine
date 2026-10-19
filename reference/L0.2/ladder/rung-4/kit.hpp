// The public header of the L0.2 ladder: every rung adds one piece to this file.
#pragma once
#include <concepts>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// Rung 1: an interface (abstract class) with two shapes.
class Shape {
public:
    virtual ~Shape() = default;
    virtual long long area() const = 0;
};
class Rect final : public Shape {
public:
    Rect(long long w, long long h) : w_(w), h_(h) {}
    long long area() const override { return w_ * h_; }
private:
    long long w_, h_;
};
class Square final : public Shape {
public:
    explicit Square(long long side) : side_(side) {}
    long long area() const override { return side_ * side_; }
private:
    long long side_;
};
inline long long total_area(const std::vector<std::unique_ptr<Shape>>& shapes) {
    long long sum = 0;
    for (const auto& s : shapes) sum += s->area();
    return sum;
}

// Rung 2: deleting a derived object through a base pointer.
inline int live_buffers = 0;
class Handler {
public:
    virtual ~Handler() = default;
    virtual std::string name() const = 0;
};
class BufferedHandler final : public Handler {
public:
    BufferedHandler() : buffer_(1024, 'x') { ++live_buffers; }
    ~BufferedHandler() override { --live_buffers; }
    std::string name() const override { return "buffered"; }
private:
    std::string buffer_;
};

// Rung 3: the same promise checked at compile time. No base class and no hidden pointer.
template <class S>
concept HasArea = requires(const S& s) { { s.area() } -> std::convertible_to<long long>; };
struct SRect { long long w, h; long long area() const { return w * h; } };
struct SSquare { long long side; long long area() const { return side * side; } };
struct STriangle { long long b, h; long long area() const { return b * h / 2; } };
template <HasArea S>
long long area_of(const S& s) { return s.area(); }
template <HasArea S>
long long total_of(const std::vector<S>& items) {
    long long sum = 0;
    for (const S& s : items) sum += area_of(s);
    return sum;
}

// Rung 4: a hot loop. Two ways to call area() n times; the answers must agree.
template <HasArea S>
long long repeat_static(const S& s, long long n) {
    long long sum = 0;
    for (long long i = 0; i < n; ++i) sum += s.area();
    return sum;
}
inline long long repeat_dynamic(const Shape& s, long long n) {
    long long sum = 0;
    for (long long i = 0; i < n; ++i) sum += s.area();
    return sum;
}

