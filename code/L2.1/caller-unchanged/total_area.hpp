#pragma once
#include <memory>
#include <vector>
#include "shape.hpp"

// The caller. This file is never edited when a new Shape is added (Claim L2.1.2).
inline double total_area(const std::vector<std::unique_ptr<Shape>>& shapes) {
    double sum = 0;
    for (const auto& s : shapes) sum += s->area();
    return sum;
}
