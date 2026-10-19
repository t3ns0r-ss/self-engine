// Worked example 2: a small value passed around by copy. No pointers, no ownership to think about.
#pragma once
#include <type_traits>

struct Point {
    int x = 0;
    int y = 0;
};

inline Point midpoint(Point a, Point b) { return {(a.x + b.x) / 2, (a.y + b.y) / 2}; }   // integer division truncates toward zero

static_assert(std::is_trivially_copyable_v<Point>, "a plain value: copying it is copying its bytes");
static_assert(sizeof(Point) == 2 * sizeof(int));
