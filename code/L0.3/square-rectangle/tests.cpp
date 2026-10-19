#include <type_traits>

#include "check.hpp"
#include "shapes.hpp"

void a_rect_keeps_its_own_promise() {
    Rect r(3, 4);
    CHECK(keeps_rect_promise(r));
}
void a_square_that_derives_from_rect_breaks_the_promise() {
    BadSquare s(4);
    CHECK(!keeps_rect_promise(s));                  // setting the width changed the height too
}
void the_break_shows_in_a_function_written_for_rect() {
    auto stretch = [](Rect& r) { r.set_width(10); return r.area(); };   // expects 10 * height
    Rect r(3, 4);
    BadSquare s(4);
    CHECK(stretch(r) == 40);
    CHECK(stretch(s) == 100);                       // not 40: the caller's reasoning is wrong for a BadSquare
}
void the_separate_square_is_not_a_rect() {
    static_assert(!std::is_base_of_v<Rect, Square>);
    CHECK((!std::is_base_of_v<Rect, Square>));
}
void a_square_scales_by_building_a_new_one() {
    Square s(2);
    Square t = s.scaled(3);
    CHECK(s.side() == 2);
    CHECK(t.side() == 6);
    CHECK(t.area() == 36);
}
void a_square_converted_to_a_rect_keeps_the_rect_promise() {
    Rect r = Square(5).as_rect();
    CHECK(r.area() == 25);
    CHECK(keeps_rect_promise(r));
}

int main() {
    RUN(a_rect_keeps_its_own_promise);
    RUN(a_square_that_derives_from_rect_breaks_the_promise);
    RUN(the_break_shows_in_a_function_written_for_rect);
    RUN(the_separate_square_is_not_a_rect);
    RUN(a_square_scales_by_building_a_new_one);
    RUN(a_square_converted_to_a_rect_keeps_the_rect_promise);
    return check::report();
}
