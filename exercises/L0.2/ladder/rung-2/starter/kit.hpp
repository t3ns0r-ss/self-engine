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
// live_buffers counts BufferedHandler objects alive. Deleting a BufferedHandler through a Handler* (or a
// std::unique_ptr<Handler>) must run ~BufferedHandler. Fix Handler so that it does.
inline int live_buffers = 0;
class Handler {
public:
    ~Handler() {}
    virtual std::string name() const = 0;
};
class BufferedHandler final : public Handler {
public:
    BufferedHandler() : buffer_(1024, 'x') { ++live_buffers; }
    ~BufferedHandler() { --live_buffers; }
    std::string name() const override { return "buffered"; }
private:
    std::string buffer_;
};

