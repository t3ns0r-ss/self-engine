#include "check.hpp"
#include "scoped_lock.hpp"

void every_return_path_unlocks() {
    Door d;
    CHECK(classify(d, 0) == 0);
    CHECK(classify(d, 5) == 1);
    CHECK(classify(d, 50) == 2);
    CHECK(d.locks() == 3);
    CHECK(d.unlocks() == 3);
    CHECK(!d.held());
}
void a_throw_unlocks() {
    Door d;
    bool threw = false;
    try { classify(d, -1); } catch (int) { threw = true; }
    CHECK(threw);
    CHECK(d.unlocks() == 1);
    CHECK(!d.held());
}
void held_inside_the_scope() {
    Door d;
    {
        ScopedHold h(d);
        CHECK(d.held());
    }
    CHECK(!d.held());
}
void two_holds_in_a_row_each_unlock() {
    Door d;
    { ScopedHold a(d); }
    { ScopedHold b(d); }
    CHECK(d.locks() == 2);
    CHECK(d.unlocks() == 2);
}
void nested_holds_on_two_doors_both_unlock() {
    Door outer, inner;
    {
        ScopedHold a(outer);
        ScopedHold b(inner);
        CHECK(outer.held() && inner.held());
    }
    CHECK(!outer.held() && !inner.held());
}
void a_hold_does_not_change_the_door_it_does_not_use() {
    Door a, b;
    { ScopedHold h(a); }
    CHECK(b.locks() == 0);
}
int main() {
    RUN(every_return_path_unlocks);
    RUN(a_throw_unlocks);
    RUN(held_inside_the_scope);
    RUN(two_holds_in_a_row_each_unlock);
    RUN(nested_holds_on_two_doors_both_unlock);
    RUN(a_hold_does_not_change_the_door_it_does_not_use);
    return check::report();
}
