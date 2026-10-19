// A third shape, added in its own file. shape.hpp (and so total_area) is not edited.
#pragma once
#include "shape.hpp"

class Triangle final : public Shape {
public:
    Triangle(long long base, long long height) : b_(base), h_(height) {}
    long long area() const override { return b_ * h_ / 2; }
private:
    long long b_, h_;
};
