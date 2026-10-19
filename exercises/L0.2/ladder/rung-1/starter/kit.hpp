// The public header of the L0.2 ladder: every rung adds one piece to this file.
#pragma once
#include <concepts>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// Rung 1: an interface (abstract class) with two shapes.
// Shape is the promise "I can tell my area"; no Shape object can be made, only Rect and Square. Rect is w * h,
// Square is side * side. total_area adds up the areas of a list of shapes through the Shape interface only.
class Shape {
public:
    virtual ~Shape() = default;
    virtual long long area() const { throw std::logic_error("not implemented"); }              // make this the promise, not an answer
};
class Rect final : public Shape {
public:
    Rect(long long w, long long h) { throw std::logic_error("not implemented"); }
    long long area() const override { throw std::logic_error("not implemented"); }
};
class Square final : public Shape {
public:
    explicit Square(long long side) { throw std::logic_error("not implemented"); }
    long long area() const override { throw std::logic_error("not implemented"); }
};
inline long long total_area(const std::vector<std::unique_ptr<Shape>>& shapes) { throw std::logic_error("not implemented"); }

