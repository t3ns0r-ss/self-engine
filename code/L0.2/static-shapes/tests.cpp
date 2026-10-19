#include <memory>
#include <vector>

#include "check.hpp"
#include "shape.hpp"          // the virtual version, from the sibling unit
#include "static.hpp"

static_assert(HasArea<SRect>);
static_assert(HasArea<STriangle>);
static_assert(!HasArea<int>, "a type with no area() is refused when the program is compiled");
static_assert(sizeof(SRect) == 2 * sizeof(long long), "no hidden pointer");

// The same contract tests, run against the template version and the virtual version.
template <class MakeRect, class MakeSquare>
void contract(MakeRect rect, MakeSquare square) {
    CHECK(rect(3, 4) == 12);
    CHECK(rect(0, 9) == 0);
    CHECK(square(5) == 25);
}
void the_template_version_passes_the_contract() {
    contract([](long long w, long long h) { return area_of(SRect{w, h}); },
             [](long long s) { return area_of(SSquare{s}); });
}
void the_virtual_version_passes_the_same_contract() {
    contract([](long long w, long long h) { return Rect(w, h).area(); },
             [](long long s) { return Square(s).area(); });
}
void both_versions_give_the_same_totals() {
    std::vector<SRect> t;
    std::vector<std::unique_ptr<Shape>> v;
    for (long long i = 1; i <= 20; ++i) {
        t.push_back(SRect{i, i + 1});
        v.push_back(std::make_unique<Rect>(i, i + 1));
    }
    CHECK(total_area(t) == total_area(v));
    CHECK(total_area(t) == 3080);
}
void a_closed_set_in_one_vector_needs_a_variant() {
    std::vector<AnyShape> items;
    items.push_back(SRect{3, 4});
    items.push_back(SSquare{5});
    items.push_back(STriangle{6, 5});
    CHECK(total_area_of_any(items) == 12 + 25 + 15);
}
void the_choice_is_made_when_the_program_is_compiled() {
    // `S` is fixed by the argument type; there is nothing to look up while the program runs.
    CHECK(area_of(SSquare{6}) == 36);
    CHECK(area_of(STriangle{4, 5}) == 10);
}

int main() {
    RUN(the_template_version_passes_the_contract);
    RUN(the_virtual_version_passes_the_same_contract);
    RUN(both_versions_give_the_same_totals);
    RUN(a_closed_set_in_one_vector_needs_a_variant);
    RUN(the_choice_is_made_when_the_program_is_compiled);
    return check::report();
}
