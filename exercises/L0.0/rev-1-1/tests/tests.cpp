#include "check.hpp"
#include "loader.hpp"

void a_good_name_gives_its_pixels() {
    CHECK(load_and_measure("logo.png") == 800);
    CHECK(load_and_measure("a") == 100);
}
void nothing_stays_alive_after_a_good_call() {
    load_and_measure("logo.png");
    CHECK(Image::live() == 0);
}
void an_empty_name_throws_and_leaks_nothing() {
    CHECK_THROWS(load_and_measure(""));
    CHECK(Image::live() == 0);
}
void a_long_name_throws_and_leaks_nothing() {
    CHECK_THROWS(load_and_measure(std::string(21, 'x')));
    CHECK(Image::live() == 0);
}
void a_name_of_exactly_20_characters_is_fine() {
    CHECK(load_and_measure(std::string(20, 'x')) == 2000);
    CHECK(Image::live() == 0);
}
void many_calls_leave_nothing() {
    for (int i = 0; i < 50; ++i) {
        load_and_measure("x");
        try { load_and_measure(""); } catch (const std::invalid_argument&) {}
    }
    CHECK(Image::live() == 0);
}
int main() {
    RUN(a_good_name_gives_its_pixels);
    RUN(nothing_stays_alive_after_a_good_call);
    RUN(an_empty_name_throws_and_leaks_nothing);
    RUN(a_long_name_throws_and_leaks_nothing);
    RUN(a_name_of_exactly_20_characters_is_fine);
    RUN(many_calls_leave_nothing);
    return check::report();
}
