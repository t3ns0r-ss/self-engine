#include <type_traits>
#include <vector>

#include "check.hpp"
#include "stack.hpp"

template <class T> concept CanErase = requires(T t) { t.erase(t.begin()); };
template <class T> concept CanIndex = requires(T t) { t[0]; };
static_assert(!std::is_base_of_v<std::vector<int>, Stack>, "hold the vector; do not inherit from it");
static_assert(!CanErase<Stack> && !CanIndex<Stack>, "only the stack operations may exist");

void pop_returns_the_last_push() {
    Stack s;
    for (int i = 1; i <= 3; ++i) s.push(i);
    CHECK(s.pop() == 3);
    CHECK(s.pop() == 2);
    CHECK(s.pop() == 1);
}
void top_looks_without_removing() {
    Stack s;
    s.push(8);
    s.push(9);
    CHECK(s.top() == 9);
    CHECK(s.size() == 2);
}
void an_empty_stack_refuses_pop_and_top() {
    Stack s;
    CHECK(s.empty());
    CHECK_THROWS(s.pop());
    CHECK_THROWS(s.top());
    CHECK(s.size() == 0);
}
void clear_empties_the_stack() {
    Stack s;
    s.push(1);
    s.push(2);
    s.clear();
    CHECK(s.empty());
    s.push(5);
    CHECK(s.pop() == 5);
}
void a_stack_can_be_copied_independently() {
    Stack a;
    a.push(1);
    Stack b = a;
    b.push(2);
    CHECK(a.size() == 1);
    CHECK(b.size() == 2);
}

int main() {
    RUN(pop_returns_the_last_push);
    RUN(top_looks_without_removing);
    RUN(an_empty_stack_refuses_pop_and_top);
    RUN(clear_empties_the_stack);
    RUN(a_stack_can_be_copied_independently);
    return check::report();
}
