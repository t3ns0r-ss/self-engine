// cp-1: a shape area service with an interface and a template twin.
#pragma once
#include <concepts>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual long long area() const = 0;
    virtual long long perimeter() const = 0;
    virtual std::string name() const = 0;
};
class Rect final : public Shape {
public:
    Rect(long long w, long long h) : w_(w), h_(h) {}
    long long area() const override { return w_ * h_; }
    long long perimeter() const override { return 2 * (w_ + h_); }
    std::string name() const override { return "rect"; }
private:
    long long w_, h_;
};
class Square final : public Shape {
public:
    explicit Square(long long side) : side_(side) {}
    long long area() const override { return side_ * side_; }
    long long perimeter() const override { return 4 * side_; }
    std::string name() const override { return "square"; }
private:
    long long side_;
};

class AreaService {
public:
    void add(std::unique_ptr<Shape> s) {
        if (!s) throw std::invalid_argument("null shape");
        shapes_.push_back(std::move(s));
    }
    std::size_t count() const { return shapes_.size(); }
    long long total_area() const {
        long long sum = 0;
        for (const auto& s : shapes_) sum += s->area();
        return sum;
    }
    // The first shape with the largest area; nullptr when there are none.
    const Shape* largest() const {
        const Shape* best = nullptr;
        for (const auto& s : shapes_)
            if (!best || s->area() >= best->area()) best = s.get();
        return best;
    }
private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};

// The twin: the same total, with the type fixed at compile time.
template <class S>
concept HasArea = requires(const S& s) { { s.area() } -> std::convertible_to<long long>; };
template <HasArea S>
long long total_area_of(const std::vector<S>& items) {
    long long sum = 0;
    for (const S& s : items) sum += s.area();
    return sum;
}
