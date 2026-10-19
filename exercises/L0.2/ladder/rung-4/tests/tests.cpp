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

static_assert(std::has_virtual_destructor_v<Handler>, "deleting a derived object through Handler* needs a virtual destructor");

void deleting_through_the_base_runs_the_derived_destructor() {
    CHECK(live_buffers == 0);
    Handler* h = new BufferedHandler;
    CHECK(live_buffers == 1);
    delete h;
    CHECK(live_buffers == 0);
}
void a_unique_ptr_to_the_base_cleans_up() {
    {
        std::unique_ptr<Handler> h = std::make_unique<BufferedHandler>();
        CHECK(h->name() == "buffered");
        CHECK(live_buffers == 1);
    }
    CHECK(live_buffers == 0);
}
void two_objects_both_release() {
    {
        std::unique_ptr<Handler> a = std::make_unique<BufferedHandler>();
        std::unique_ptr<Handler> b = std::make_unique<BufferedHandler>();
        CHECK(live_buffers == 2);
    }
    CHECK(live_buffers == 0);
}
void the_name_comes_from_the_derived_class() {
    BufferedHandler b;
    const Handler& h = b;
    CHECK(h.name() == "buffered");
}

static_assert(HasArea<SRect>);
static_assert(HasArea<STriangle>);
static_assert(!HasArea<int>, "a type with no area() is refused when the program is compiled");
static_assert(sizeof(SRect) == 2 * sizeof(long long), "no hidden pointer");

void the_triangle_rounds_down() {
    CHECK((STriangle{6, 5}).area() == 15);
    CHECK((STriangle{3, 3}).area() == 4);
    CHECK((STriangle{0, 9}).area() == 0);
}
void area_of_works_for_any_type_with_area() {
    CHECK(area_of(SRect{3, 4}) == 12);
    CHECK(area_of(SSquare{6}) == 36);
    CHECK(area_of(STriangle{4, 5}) == 10);
}
void total_of_adds_every_element() {
    std::vector<SRect> v{{1, 2}, {3, 4}, {5, 6}};
    CHECK(total_of(v) == 2 + 12 + 30);
}
void total_of_an_empty_vector_is_zero() {
    CHECK(total_of(std::vector<SSquare>{}) == 0);
}
void a_new_type_works_without_editing_the_functions() {
    struct Circle100 { long long area() const { return 314; } };
    static_assert(HasArea<Circle100>);
    std::vector<Circle100> v(3);
    CHECK(total_of(v) == 942);
}
void the_last_element_is_counted() {
    std::vector<STriangle> v{{2, 2}, {4, 4}};
    CHECK(total_of(v) == 2 + 8);
}

void both_loops_agree() {
    Rect r(3, 4);
    SRect sr{3, 4};
    CHECK(repeat_static(sr, 1000) == 12000);
    CHECK(repeat_dynamic(r, 1000) == 12000);
}
void zero_repeats_give_zero() {
    CHECK(repeat_static(SSquare{9}, 0) == 0);
    CHECK(repeat_dynamic(Square(9), 0) == 0);
}
void one_repeat_is_one_area() {
    CHECK(repeat_static(SSquare{9}, 1) == 81);
    CHECK(repeat_dynamic(Square(9), 1) == 81);
}
void ten_million_repeats() {
    CHECK(repeat_static(SSquare{2}, 10'000'000) == 40'000'000);
    CHECK(repeat_dynamic(Square(2), 10'000'000) == 40'000'000);
}
void the_dynamic_loop_follows_the_derived_class() {
    struct Odd final : Shape { long long area() const override { return 7; } };
    CHECK(repeat_dynamic(Odd{}, 5) == 35);
}

int main() {
    RUN(a_call_through_a_base_reference_runs_the_derived_function);
    RUN(a_list_of_mixed_shapes_is_summed);
    RUN(an_empty_list_is_zero);
    RUN(a_shape_defined_by_the_caller_works_too);
    RUN(a_zero_side_has_no_area);
    RUN(deleting_through_the_base_runs_the_derived_destructor);
    RUN(a_unique_ptr_to_the_base_cleans_up);
    RUN(two_objects_both_release);
    RUN(the_name_comes_from_the_derived_class);
    RUN(the_triangle_rounds_down);
    RUN(area_of_works_for_any_type_with_area);
    RUN(total_of_adds_every_element);
    RUN(total_of_an_empty_vector_is_zero);
    RUN(a_new_type_works_without_editing_the_functions);
    RUN(the_last_element_is_counted);
    RUN(both_loops_agree);
    RUN(zero_repeats_give_zero);
    RUN(one_repeat_is_one_area);
    RUN(ten_million_repeats);
    RUN(the_dynamic_loop_follows_the_derived_class);
    return check::report();
}
