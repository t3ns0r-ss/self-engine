#include <stdexcept>
#include <type_traits>
#include <vector>

#include "check.hpp"
#include "connection.hpp"

static_assert(!std::is_copy_constructible_v<Connection>, "two owners would close one connection twice");
static_assert(std::is_nothrow_move_constructible_v<Connection>);

void closes_when_the_scope_ends() {
    Log log;
    {
        Connection c(log);
        CHECK(log.opened == 1);
        CHECK(log.closed == 0);   // still open inside the scope
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
        Connection b(std::move(a));   // b owns it now; a owns nothing
        CHECK(log.closed == 0);
    }
    CHECK(log.opened == 1);
    CHECK(log.closed == 1);
}

void a_container_of_connections_closes_each_once() {
    Log log;
    {
        std::vector<Connection> v;
        for (int i = 0; i < 5; ++i) v.emplace_back(log);   // growth moves the elements
        CHECK(log.opened == 5);
    }
    CHECK(log.closed == 5);
}

void opens_and_closes_stay_in_balance_over_many_scopes() {
    Log log;
    for (int i = 0; i < 100; ++i) { Connection c(log); }
    CHECK(log.opened == 100);
    CHECK(log.closed == 100);
}

int main() {
    RUN(closes_when_the_scope_ends);
    RUN(closes_on_an_early_return);
    RUN(closes_when_an_exception_leaves_the_scope);
    RUN(moving_closes_once_not_twice);
    RUN(a_container_of_connections_closes_each_once);
    RUN(opens_and_closes_stay_in_balance_over_many_scopes);
    return check::report();
}
