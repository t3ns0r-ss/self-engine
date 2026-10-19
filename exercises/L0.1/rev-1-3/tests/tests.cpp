#include <stdexcept>
#include <type_traits>

#include "check.hpp"
#include "stack.hpp"

static_assert(!std::is_aggregate_v<Stack>, "a public size field lets any code break the rule");

void push_then_pop_returns_the_last_value() {
    Stack s;
    s.push(1);
    s.push(2);
    CHECK(s.pop() == 2);
    CHECK(s.pop() == 1);
}
void size_follows_the_operations() {
    Stack s;
    CHECK(s.size() == 0);
    s.push(5);
    CHECK(s.size() == 1);
    s.pop();
    CHECK(s.size() == 0);
}
void pushing_onto_a_full_stack_throws_and_changes_nothing() {
    Stack s;
    for (int i = 0; i < 4; ++i) s.push(i);
    bool threw_length_error = false;
    try { s.push(99); } catch (const std::length_error&) { threw_length_error = true; }
    CHECK(threw_length_error);
    CHECK(s.size() == 4);
    CHECK(s.pop() == 3);
}
void popping_an_empty_stack_throws_and_changes_nothing() {
    Stack s;
    bool threw_out_of_range = false;
    try { s.pop(); } catch (const std::out_of_range&) { threw_out_of_range = true; }
    CHECK(threw_out_of_range);
    CHECK(s.size() == 0);
    s.push(7);
    CHECK(s.pop() == 7);
}
void exactly_four_fit() {
    Stack s;
    for (int i = 0; i < 4; ++i) s.push(i);
    CHECK(s.size() == 4);
}
int main() {
    RUN(push_then_pop_returns_the_last_value);
    RUN(size_follows_the_operations);
    RUN(pushing_onto_a_full_stack_throws_and_changes_nothing);
    RUN(popping_an_empty_stack_throws_and_changes_nothing);
    RUN(exactly_four_fit);
    return check::report();
}
