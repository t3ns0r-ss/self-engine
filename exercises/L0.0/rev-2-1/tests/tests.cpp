#include <stdexcept>
#include <type_traits>
#include <vector>

#include "check.hpp"
#include "scoped_timer.hpp"

static_assert(!std::is_copy_constructible_v<ScopedTimer>);
static_assert(std::is_move_constructible_v<ScopedTimer>);

static long long fake_time = 0;
static long long fake_now() { return fake_time; }

void records_the_elapsed_time_when_the_scope_ends() {
    std::vector<long long> out;
    fake_time = 100;
    {
        ScopedTimer t(out, fake_now);
        fake_time = 130;
        CHECK(out.empty());
    }
    CHECK(out.size() == 1);
    CHECK(out[0] == 30);
}
int early(std::vector<long long>& out, bool leave) {
    ScopedTimer t(out, fake_now);
    fake_time += 5;
    if (leave) return 1;
    fake_time += 5;
    return 2;
}
void records_on_every_return_path() {
    std::vector<long long> out;
    fake_time = 0;
    early(out, true);
    early(out, false);
    CHECK(out.size() == 2);
    CHECK(out[0] == 5);
    CHECK(out[1] == 10);
}
void records_when_an_exception_leaves() {
    std::vector<long long> out;
    fake_time = 0;
    try {
        ScopedTimer t(out, fake_now);
        fake_time = 7;
        throw std::runtime_error("boom");
    } catch (const std::runtime_error&) {}
    CHECK(out.size() == 1);
    CHECK(out[0] == 7);
}
void nested_timers_record_inner_first() {
    std::vector<long long> out;
    fake_time = 0;
    {
        ScopedTimer outer(out, fake_now);
        fake_time = 10;
        {
            ScopedTimer inner(out, fake_now);
            fake_time = 14;
        }
        fake_time = 20;
    }
    CHECK(out.size() == 2);
    CHECK(out[0] == 4);
    CHECK(out[1] == 20);
}
void a_moved_timer_records_once() {
    std::vector<long long> out;
    fake_time = 0;
    {
        ScopedTimer a(out, fake_now);
        ScopedTimer b(std::move(a));
        fake_time = 9;
    }
    CHECK(out.size() == 1);
    CHECK(out[0] == 9);
}
void a_timer_that_takes_no_time_records_zero() {
    std::vector<long long> out;
    fake_time = 50;
    { ScopedTimer t(out, fake_now); }
    CHECK(out.size() == 1);
    CHECK(out[0] == 0);
}
int main() {
    RUN(records_the_elapsed_time_when_the_scope_ends);
    RUN(records_on_every_return_path);
    RUN(records_when_an_exception_leaves);
    RUN(nested_timers_record_inner_first);
    RUN(a_moved_timer_records_once);
    RUN(a_timer_that_takes_no_time_records_zero);
    return check::report();
}
