#pragma once
#include "shape.hpp"

class Square final : public Shape {
public:
    explicit Square(double side) : side_(side) {}
    double area() const override { return side_ * side_; }
private:
    double side_;
};

// Added later, without touching total_area.hpp.
class Rectangle final : public Shape {
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
private:
    double w_, h_;
};
