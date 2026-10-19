#include "check.hpp"
#include "vtable.hpp"

// The same two shapes with the language's own `virtual`.
struct VShape {
    virtual ~VShape() = default;
    virtual long long area() const = 0;
};
struct VRect : VShape {
    VRect(int w, int h) : w(w), h(h) {}
    long long area() const override { return static_cast<long long>(w) * h; }
    int w, h;
};
struct VSquare : VShape {
    explicit VSquare(int s) : side(s) {}
    long long area() const override { return static_cast<long long>(side) * side; }
    int side;
};
struct PlainRect { int w, h; };                     // the same data with no virtual function

void the_hand_made_table_gives_each_class_its_own_answer() {
    ManualRect r = make_rect(3, 4);
    ManualSquare s = make_square(5);
    CHECK(call_area(&r) == 12);
    CHECK(call_area(&s) == 25);
}
void the_hand_made_call_matches_the_virtual_call() {
    for (int a = 0; a <= 12; ++a) {
        for (int b = 0; b <= 12; ++b) {
            ManualRect m = make_rect(a, b);
            VRect v(a, b);
            const VShape& base = v;
            CHECK(call_area(&m) == base.area());
        }
        ManualSquare ms = make_square(a);
        VSquare vs(a);
        const VShape& vbase = vs;
        CHECK(call_area(&ms) == vbase.area());
    }
}
void objects_of_one_class_share_one_table() {
    ManualRect a = make_rect(1, 1);
    ManualRect b = make_rect(2, 2);
    ManualSquare c = make_square(3);
    CHECK(a.table == b.table);
    CHECK(a.table != c.table);
}
void a_virtual_function_adds_one_pointer_to_every_object() {
    CHECK(sizeof(VRect) == sizeof(PlainRect) + sizeof(void*));
    CHECK(sizeof(ManualRect) == sizeof(PlainRect) + sizeof(void*));
}

int main() {
    RUN(the_hand_made_table_gives_each_class_its_own_answer);
    RUN(the_hand_made_call_matches_the_virtual_call);
    RUN(objects_of_one_class_share_one_table);
    RUN(a_virtual_function_adds_one_pointer_to_every_object);
    return check::report();
}
