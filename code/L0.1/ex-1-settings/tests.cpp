#include "check.hpp"
#include "settings.hpp"

void defaults_are_sensible() {
    Settings s;
    CHECK(describe(s) == "light/14/en/tips");
}
void every_combination_of_the_flags_is_valid() {
    int count = 0;
    for (bool dark : {false, true})
        for (bool tips : {false, true})
            for (int size : {1, 14, 400}) {
                Settings s{dark, size, "de", tips};
                CHECK(!describe(s).empty());
                ++count;
            }
    CHECK(count == 12);
}
void fields_are_set_directly() {
    Settings s;
    s.font_size = 20;
    CHECK(s.font_size == 20);
    CHECK(describe(s) == "light/20/en/tips");
}
void a_copy_is_independent() {
    Settings a;
    Settings b = a;
    b.dark_mode = true;
    CHECK(!a.dark_mode);
}
void aggregate_initialisation_works() {
    Settings s{true, 12, "fr", false};
    CHECK(describe(s) == "dark/12/fr");
}
void language_can_be_anything() {
    Settings s;
    s.language = "";
    CHECK(describe(s) == "light/14//tips");
}
int main() {
    RUN(defaults_are_sensible);
    RUN(every_combination_of_the_flags_is_valid);
    RUN(fields_are_set_directly);
    RUN(a_copy_is_independent);
    RUN(aggregate_initialisation_works);
    RUN(language_can_be_anything);
    return check::report();
}
