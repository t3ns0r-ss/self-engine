#include "check.hpp"
#include "point.hpp"

void a_copy_is_independent_of_the_original() {
    Point a{1, 2};
    Point b = a;
    b.x = 99;
    CHECK(a.x == 1);
    CHECK(b.x == 99);
}
void passing_by_value_leaves_the_argument_alone() {
    Point a{4, 6}, b{8, 2};
    Point m = midpoint(a, b);
    CHECK(m.x == 6 && m.y == 4);
    CHECK(a.x == 4 && b.x == 8);
}
void midpoint_truncates_toward_zero() {
    CHECK(midpoint({0, 0}, {1, 1}).x == 0);
    CHECK(midpoint({-1, -1}, {0, 0}).x == 0);
    CHECK(midpoint({-3, 0}, {0, 0}).x == -1);
}
void default_point_is_the_origin() {
    Point p;
    CHECK(p.x == 0 && p.y == 0);
}
void points_in_an_array_are_separate_values() {
    Point ps[3] = {{1, 1}, {2, 2}, {3, 3}};
    Point copy[3];
    for (int i = 0; i < 3; ++i) copy[i] = ps[i];
    copy[1].y = 7;
    CHECK(ps[1].y == 2);
}
void midpoint_of_equal_points_is_that_point() {
    Point p{5, -5};
    Point m = midpoint(p, p);
    CHECK(m.x == 5 && m.y == -5);
}
int main() {
    RUN(a_copy_is_independent_of_the_original);
    RUN(passing_by_value_leaves_the_argument_alone);
    RUN(midpoint_truncates_toward_zero);
    RUN(default_point_is_the_origin);
    RUN(points_in_an_array_are_separate_values);
    RUN(midpoint_of_equal_points_is_that_point);
    return check::report();
}
