#include <optional>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "check.hpp"
#include "kit.hpp"

static_assert(!std::is_copy_constructible_v<Connection>, "two owners would close one connection twice");
static_assert(std::is_move_constructible_v<Connection>);

void closes_when_the_scope_ends() {
    Log log;
    {
        Connection c(log);
        CHECK(log.opened == 1);
        CHECK(log.closed == 0);
    }
    CHECK(log.closed == 1);
}
int early_return(Log& log, bool leave_early) {
    Connection c(log);
    if (leave_early) return 1;
    return 2;
}
void closes_on_an_early_return() {
    Log log;
    CHECK(early_return(log, true) == 1);
    CHECK(log.closed == 1);
    CHECK(early_return(log, false) == 2);
    CHECK(log.closed == 2);
}
void fails_after_opening(Log& log) {
    Connection c(log);
    throw std::runtime_error("parse error after open");
}
void closes_when_an_exception_leaves_the_scope() {
    Log log;
    try { fails_after_opening(log); } catch (const std::runtime_error&) {}
    CHECK(log.opened == 1);
    CHECK(log.closed == 1);
}
void moving_closes_once_not_twice() {
    Log log;
    {
        Connection a(log);
        Connection b(std::move(a));
        CHECK(log.closed == 0);
    }
    CHECK(log.opened == 1);
    CHECK(log.closed == 1);
}
void a_container_of_connections_closes_each_once() {
    Log log;
    {
        std::vector<Connection> v;
        for (int i = 0; i < 5; ++i) v.emplace_back(log);
    }
    CHECK(log.opened == 5);
    CHECK(log.closed == 5);
}

void the_caller_owns_what_the_factory_returns() {
    {
        std::unique_ptr<Report> r = make_report(4);
        CHECK(Report::live() == 1);
        CHECK(r->total() == 10);
    }
    CHECK(Report::live() == 0);
}
void a_failing_factory_leaks_nothing() {
    CHECK_THROWS(make_report(0));
    CHECK(Report::live() == 0);
    CHECK_THROWS(make_report(-5));
    CHECK(Report::live() == 0);
}
void totals_are_triangular_numbers() {
    CHECK(make_report(1)->total() == 1);
    CHECK(make_report(10)->total() == 55);
    CHECK(make_report(100)->total() == 5050);
    CHECK(Report::live() == 0);
}
void reports_can_be_moved_into_a_container() {
    {
        std::vector<std::unique_ptr<Report>> v;
        v.push_back(make_report(1));
        v.push_back(make_report(2));
        CHECK(Report::live() == 2);
    }
    CHECK(Report::live() == 0);
}

int main() {
    RUN(closes_when_the_scope_ends);
    RUN(closes_on_an_early_return);
    RUN(closes_when_an_exception_leaves_the_scope);
    RUN(moving_closes_once_not_twice);
    RUN(a_container_of_connections_closes_each_once);
    RUN(the_caller_owns_what_the_factory_returns);
    RUN(a_failing_factory_leaks_nothing);
    RUN(totals_are_triangular_numbers);
    RUN(reports_can_be_moved_into_a_container);
    return check::report();
}
