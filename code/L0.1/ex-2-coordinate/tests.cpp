#include <map>
#include <string>

#include "check.hpp"
#include "coordinate.hpp"

void a_coordinate_keeps_its_values() {
    Coordinate c(3, 4);
    CHECK(c.x() == 3 && c.y() == 4);
}
void moved_gives_a_new_value_and_leaves_the_old_one() {
    Coordinate a(1, 1);
    Coordinate b = a.moved(2, 3);
    CHECK(a.x() == 1 && a.y() == 1);
    CHECK(b.x() == 3 && b.y() == 4);
}
void equal_values_are_equal() {
    CHECK(Coordinate(1, 2) == Coordinate(1, 2));
    CHECK(!(Coordinate(1, 2) == Coordinate(2, 1)));
}
void a_key_is_found_again() {
    std::map<Coordinate, std::string> grid;
    grid.emplace(Coordinate(0, 0), "start");
    grid.emplace(Coordinate(5, 5), "goal");
    CHECK(grid.at(Coordinate(5, 5)) == "goal");
    CHECK(grid.find(Coordinate(9, 9)) == grid.end());
}
void a_key_cannot_be_changed_after_insertion() {
    std::map<Coordinate, int> grid;
    auto [it, inserted] = grid.emplace(Coordinate(1, 2), 7);
    CHECK(inserted);
    Coordinate shifted = it->first.moved(10, 10);     // builds a new value; the key in the map is untouched
    CHECK(it->first.x() == 1);
    CHECK(grid.find(Coordinate(1, 2)) != grid.end());
    CHECK(grid.find(shifted) == grid.end());
}
void ordering_is_by_x_then_y() {
    CHECK(Coordinate(1, 9) < Coordinate(2, 0));
    CHECK(Coordinate(1, 1) < Coordinate(1, 2));
    CHECK(!(Coordinate(1, 2) < Coordinate(1, 2)));
}
int main() {
    RUN(a_coordinate_keeps_its_values);
    RUN(moved_gives_a_new_value_and_leaves_the_old_one);
    RUN(equal_values_are_equal);
    RUN(a_key_is_found_again);
    RUN(a_key_cannot_be_changed_after_insertion);
    RUN(ordering_is_by_x_then_y);
    return check::report();
}
