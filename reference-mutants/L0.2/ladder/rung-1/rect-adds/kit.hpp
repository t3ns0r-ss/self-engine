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
    long long area() const override { return w_ + h_; }
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

