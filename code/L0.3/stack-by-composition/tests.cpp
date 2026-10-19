#include "check.hpp"
#include "stack.hpp"

void both_stacks_pop_in_reverse_order_of_push() {
    Stack s;
    VecStack v;
    for (int i = 1; i <= 3; ++i) { s.push(i); v.push(i); }
    CHECK(s.pop() == 3);
    CHECK(v.pop() == 3);
    CHECK(s.pop() == 2);
    CHECK(v.pop() == 2);
}
void popping_an_empty_stack_is_refused() {
    Stack s;
    VecStack v;
    CHECK_THROWS(s.pop());
    CHECK_THROWS(v.pop());
}
void the_inheriting_stack_lets_a_caller_break_the_rule() {
    VecStack v;
    for (int i = 1; i <= 3; ++i) v.push(i);
    v.erase(v.begin() + 2);                         // compiles: erase is inherited and public
    CHECK(v.pop() == 2);                            // the last push was 3, but pop returns 2
}
void the_composed_stack_has_no_such_operation() {
    static_assert(CanErase<VecStack>);
    static_assert(!CanErase<Stack>);
    static_assert(CanIndex<VecStack>);
    static_assert(!CanIndex<Stack>);
    CHECK(!CanErase<Stack>);
    CHECK(!CanIndex<Stack>);
}
void the_composed_stack_reports_size_and_top() {
    Stack s;
    CHECK(s.empty());
    s.push(8);
    s.push(9);
    CHECK(s.size() == 2);
    CHECK(s.top() == 9);
    CHECK(s.size() == 2);
}

int main() {
    RUN(both_stacks_pop_in_reverse_order_of_push);
    RUN(popping_an_empty_stack_is_refused);
    RUN(the_inheriting_stack_lets_a_caller_break_the_rule);
    RUN(the_composed_stack_has_no_such_operation);
    RUN(the_composed_stack_reports_size_and_top);
    return check::report();
}
