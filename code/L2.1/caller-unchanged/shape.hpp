#pragma once
// The shared signature. Callers depend only on this.
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};
