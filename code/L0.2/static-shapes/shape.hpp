// An interface as an abstract class: Shape promises area(); each shape answers for itself.
#pragma once
#include <memory>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual long long area() const = 0;        // "= 0": no Shape object can exist, only derived ones
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

// The caller. It knows Shape only. It is compiled before any third shape exists.
inline long long total_area(const std::vector<std::unique_ptr<Shape>>& shapes) {
    long long sum = 0;
    for (const auto& s : shapes) sum += s->area();
    return sum;
}
