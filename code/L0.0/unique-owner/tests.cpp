#include <type_traits>
#include <utility>

#include "check.hpp"
#include "report.hpp"

static_assert(!std::is_copy_constructible_v<std::unique_ptr<Report>>, "a unique_ptr has one owner");

void the_caller_owns_what_the_factory_returns() {
    {
        std::unique_ptr<Report> r = make_report(4);
        CHECK(Report::live() == 1);
        CHECK(r->total() == 10);
    }
    CHECK(Report::live() == 0);   // destroyed when the owner went out of scope
}

void a_failing_factory_leaks_nothing() {
    CHECK_THROWS(make_report(0));
    CHECK(Report::live() == 0);
}

void moving_transfers_ownership_and_empties_the_source() {
    auto a = make_report(3);
    auto b = std::move(a);
    CHECK(a == nullptr);
    CHECK(b != nullptr);
    CHECK(Report::live() == 1);
    CHECK(b->total() == 6);
}

void a_container_owns_what_is_moved_into_it() {
    {
        std::vector<std::unique_ptr<Report>> v;
        v.push_back(make_report(1));
        v.push_back(make_report(2));
        v.push_back(make_report(3));
        CHECK(Report::live() == 3);
    }
    CHECK(Report::live() == 0);
}

void reset_destroys_the_object_now() {
    auto r = make_report(5);
    CHECK(Report::live() == 1);
    r.reset();
    CHECK(Report::live() == 0);
    CHECK(r == nullptr);
}

void release_gives_up_ownership_and_the_caller_must_delete() {
    auto r = make_report(2);
    Report* raw = r.release();
    CHECK(r == nullptr);
    CHECK(Report::live() == 1);   // nobody owns it any more
    delete raw;                   // the caller took on the job the unique_ptr did
    CHECK(Report::live() == 0);
}

int main() {
    RUN(the_caller_owns_what_the_factory_returns);
    RUN(a_failing_factory_leaks_nothing);
    RUN(moving_transfers_ownership_and_empties_the_source);
    RUN(a_container_owns_what_is_moved_into_it);
    RUN(reset_destroys_the_object_now);
    RUN(release_gives_up_ownership_and_the_caller_must_delete);
    return check::report();
}
