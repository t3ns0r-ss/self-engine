#include <memory>
#include <type_traits>
#include <vector>

#include "check.hpp"
#include "shape.hpp"
#include "triangle.hpp"

static_assert(std::is_abstract_v<Shape>, "Shape must be an interface: no object of it can be made");

void a_call_through_a_base_reference_runs_the_derived_function() {
    Rect r(3, 4);
    Square q(5);
    const Shape& a = r;
    const Shape& b = q;
    CHECK(a.area() == 12);
    CHECK(b.area() == 25);
}
void a_call_through_a_base_pointer_runs_the_derived_function() {
    std::unique_ptr<Shape> p = std::make_unique<Rect>(2, 7);
    CHECK(p->area() == 14);
}
void the_caller_sums_a_mixed_list() {
    std::vector<std::unique_ptr<Shape>> v;
    v.push_back(std::make_unique<Rect>(3, 4));
    v.push_back(std::make_unique<Square>(5));
    CHECK(total_area(v) == 37);
}
void a_third_shape_works_with_the_unchanged_caller() {
    std::vector<std::unique_ptr<Shape>> v;
    v.push_back(std::make_unique<Rect>(3, 4));
    v.push_back(std::make_unique<Triangle>(6, 5));      // total_area was compiled without knowing Triangle
    v.push_back(std::make_unique<Square>(2));
    CHECK(total_area(v) == 12 + 15 + 4);
}
void an_empty_list_has_zero_area() {
    std::vector<std::unique_ptr<Shape>> v;
    CHECK(total_area(v) == 0);
}
// The contract every Shape must keep: it can be called twice with the same answer, and it is not negative.
void check_contract(const Shape& s) {
    CHECK(s.area() >= 0);
    CHECK(s.area() == s.area());
}
void every_shape_keeps_the_contract() {
    check_contract(Rect(0, 9));
    check_contract(Rect(6, 6));
    check_contract(Square(11));
    check_contract(Triangle(7, 3));
}

int main() {
    RUN(a_call_through_a_base_reference_runs_the_derived_function);
    RUN(a_call_through_a_base_pointer_runs_the_derived_function);
    RUN(the_caller_sums_a_mixed_list);
    RUN(a_third_shape_works_with_the_unchanged_caller);
    RUN(an_empty_list_has_zero_area);
    RUN(every_shape_keeps_the_contract);
    return check::report();
}
