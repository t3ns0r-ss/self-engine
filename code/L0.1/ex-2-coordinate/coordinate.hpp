// Worked example 2: a pair of coordinates used as a key in a map. It must not change while it is a key,
// or the map can no longer find it. An immutable value gives that for free.
#pragma once
#include <cstddef>
#include <functional>
#include <map>

class Coordinate {
public:
    constexpr Coordinate(int x, int y) : x_(x), y_(y) {}
    constexpr int x() const { return x_; }
    constexpr int y() const { return y_; }
    constexpr Coordinate moved(int dx, int dy) const { return Coordinate(x_ + dx, y_ + dy); }   // a new value
    constexpr bool operator==(const Coordinate&) const = default;
    constexpr bool operator<(const Coordinate& o) const { return x_ != o.x_ ? x_ < o.x_ : y_ < o.y_; }
private:
    const int x_;
    const int y_;
};
