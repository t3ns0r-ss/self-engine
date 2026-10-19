#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "check.hpp"
#include "kit.hpp"

static_assert(std::is_abstract_v<Shape>, "Shape is an interface: no Shape object can be made");

void a_call_through_a_base_reference_runs_the_derived_function() {
    Rect r(3, 4);
    Square q(5);
    const Shape& a = r;
    const Shape& b = q;
    CHECK(a.area() == 12);
    CHECK(b.area() == 25);
}
void a_list_of_mixed_shapes_is_summed() {
    std::vector<std::unique_ptr<Shape>> v;
    v.push_back(std::make_unique<Rect>(3, 4));
    v.push_back(std::make_unique<Square>(5));
    v.push_back(std::make_unique<Rect>(1, 1));
    CHECK(total_area(v) == 38);
}
void an_empty_list_is_zero() {
    std::vector<std::unique_ptr<Shape>> v;
    CHECK(total_area(v) == 0);
}
void a_shape_defined_by_the_caller_works_too() {
    struct Fixed final : Shape { long long area() const override { return 100; } };
    std::vector<std::unique_ptr<Shape>> v;
    v.push_back(std::make_unique<Fixed>());
    v.push_back(std::make_unique<Square>(2));
    CHECK(total_area(v) == 104);
}
void a_zero_side_has_no_area() {
    CHECK(Rect(0, 9).area() == 0);
    CHECK(Square(0).area() == 0);
}

int main() {
    RUN(a_call_through_a_base_reference_runs_the_derived_function);
    RUN(a_list_of_mixed_shapes_is_summed);
    RUN(an_empty_list_is_zero);
    RUN(a_shape_defined_by_the_caller_works_too);
    RUN(a_zero_side_has_no_area);
    return check::report();
}
