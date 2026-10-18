#include "check.hpp"
#include "shapes.hpp"
#include "total_area.hpp"

void sums_mixed_shapes() {
    std::vector<std::unique_ptr<Shape>> v;
    v.push_back(std::make_unique<Square>(2));
    v.push_back(std::make_unique<Rectangle>(2, 3));
    CHECK(total_area(v) == 10);
}
void empty_is_zero() {
    std::vector<std::unique_ptr<Shape>> none;
    CHECK(total_area(none) == 0);
}
void one_shape_is_its_own_area() {
    std::vector<std::unique_ptr<Shape>> v;
    v.push_back(std::make_unique<Rectangle>(4, 5));
    CHECK(total_area(v) == 20);
}
void order_does_not_matter() {
    std::vector<std::unique_ptr<Shape>> a, b;
    a.push_back(std::make_unique<Square>(3));
    a.push_back(std::make_unique<Rectangle>(1, 2));
    b.push_back(std::make_unique<Rectangle>(1, 2));
    b.push_back(std::make_unique<Square>(3));
    CHECK(total_area(a) == total_area(b));
}
void new_shape_defined_in_the_test_needs_no_caller_edit() {
    // A shape invented here, after total_area.hpp was written, still works with the unchanged caller.
    struct Triangle final : Shape {
        double area() const override { return 0.5 * 4 * 3; }
    };
    std::vector<std::unique_ptr<Shape>> v;
    v.push_back(std::make_unique<Triangle>());
    v.push_back(std::make_unique<Square>(1));
    CHECK(total_area(v) == 7);
}
void destroying_through_the_base_pointer_is_clean() {
    // Under the address sanitizer a missing virtual destructor would be reported as a leak or a size mismatch.
    std::unique_ptr<Shape> p = std::make_unique<Rectangle>(2, 2);
    CHECK(p->area() == 4);
}

int main() {
    RUN(sums_mixed_shapes);
    RUN(empty_is_zero);
    RUN(one_shape_is_its_own_area);
    RUN(order_does_not_matter);
    RUN(new_shape_defined_in_the_test_needs_no_caller_edit);
    RUN(destroying_through_the_base_pointer_is_clean);
    return check::report();
}
