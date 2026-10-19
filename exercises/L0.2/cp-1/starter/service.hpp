// cp-1: a shape area service with an interface and a template twin.
#pragma once
#include <concepts>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// Shape: an interface (no Shape object can be made) with area(), perimeter() and name(), safe to delete through a
// Shape pointer. Rect(w, h): area w*h, perimeter 2(w+h), name "rect". Square(side): area side*side, perimeter 4*side,
// name "square".
class Shape {
public:
    virtual ~Shape() = default;
    virtual long long area() const { throw std::logic_error("not implemented"); }
};
class Rect final : public Shape {
public:
    Rect(long long w, long long h) { throw std::logic_error("not implemented"); }
};
class Square final : public Shape {
public:
    explicit Square(long long side) { throw std::logic_error("not implemented"); }
};

// AreaService owns the shapes it is given. add(nullptr) throws std::invalid_argument. count() is how many shapes.
// total_area() adds the areas (0 when empty). largest() is the first shape with the largest area, or nullptr when
// there are none. It must work with a Shape subclass the caller defines.
class AreaService {
public:
    void add(std::unique_ptr<Shape> s) { throw std::logic_error("not implemented"); }
    std::size_t count() const { throw std::logic_error("not implemented"); }
    long long total_area() const { throw std::logic_error("not implemented"); }
    const Shape* largest() const { throw std::logic_error("not implemented"); }
};

// The twin: the same total for a vector of one type with an area() member, resolved at compile time.
// Do not add a base class to make it work. HasArea is given.
template <class S>
concept HasArea = requires(const S& s) { { s.area() } -> std::convertible_to<long long>; };
template <HasArea S>
long long total_area_of(const std::vector<S>& items) { throw std::logic_error("not implemented"); }
