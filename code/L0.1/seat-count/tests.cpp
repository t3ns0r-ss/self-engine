#include <stdexcept>

#include "check.hpp"
#include "seats.hpp"

void a_new_count_starts_empty() {
    Seats s(10);
    CHECK(s.booked() == 0);
    CHECK(s.free() == 10);
}
void booking_and_cancelling_move_the_count() {
    Seats s(10);
    s.book(4);
    CHECK(s.booked() == 4);
    s.cancel(1);
    CHECK(s.booked() == 3);
}
void booking_more_than_free_is_refused_and_changes_nothing() {
    Seats s(5);
    s.book(3);
    CHECK_THROWS(s.book(3));
    CHECK(s.booked() == 3);       // unchanged by the refusal
}
void cancelling_more_than_booked_is_refused_and_changes_nothing() {
    Seats s(5);
    s.book(2);
    CHECK_THROWS(s.cancel(3));
    CHECK(s.booked() == 2);
}
void negative_numbers_are_refused() {
    Seats s(5);
    CHECK_THROWS(s.book(-1));
    CHECK_THROWS(s.cancel(-1));
    CHECK(s.booked() == 0);
    CHECK_THROWS(Seats(-1));
}
void a_refused_transfer_changes_neither_side() {
    Seats a(5), b(2);
    a.book(4);
    b.book(1);
    CHECK_THROWS(Seats::transfer(a, b, 2));   // b has room for only 1
    CHECK(a.booked() == 4);
    CHECK(b.booked() == 1);
}
void a_transfer_moves_both_sides() {
    Seats a(5), b(5);
    a.book(3);
    Seats::transfer(a, b, 2);
    CHECK(a.booked() == 1);
    CHECK(b.booked() == 2);
}
// Exhaustive: after any sequence of up to 4 operations drawn from a small set, 0 <= booked <= capacity.
void the_rule_holds_after_every_short_sequence() {
    const int ops[] = {-1, 1, 2, 3};      // negative = cancel that many
    int checked = 0;
    for (int a : ops) for (int b : ops) for (int c : ops) for (int d : ops) {
        Seats s(4);
        for (int op : {a, b, c, d}) {
            try { if (op > 0) s.book(op); else s.cancel(-op); } catch (const std::invalid_argument&) {}
            CHECK(s.booked() >= 0 && s.booked() <= s.capacity());
        }
        ++checked;
    }
    CHECK(checked == 256);
}
int main() {
    RUN(a_new_count_starts_empty);
    RUN(booking_and_cancelling_move_the_count);
    RUN(booking_more_than_free_is_refused_and_changes_nothing);
    RUN(cancelling_more_than_booked_is_refused_and_changes_nothing);
    RUN(negative_numbers_are_refused);
    RUN(a_refused_transfer_changes_neither_side);
    RUN(a_transfer_moves_both_sides);
    RUN(the_rule_holds_after_every_short_sequence);
    return check::report();
}
