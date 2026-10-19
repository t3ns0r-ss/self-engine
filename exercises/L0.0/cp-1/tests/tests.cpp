#include <filesystem>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <unistd.h>

#include "check.hpp"
#include "temp_file.hpp"

static_assert(!std::is_copy_constructible_v<TempFile>);
static_assert(std::is_move_constructible_v<TempFile>);

static std::string unique(const char* stem) { return std::string("cp1-") + stem + "-" + std::to_string(::getpid()); }
static bool file_exists(const std::filesystem::path& p) { return std::filesystem::exists(p); }

void the_file_exists_inside_the_scope_and_is_gone_after() {
    std::filesystem::path p;
    {
        TempFile f(unique("scope"));
        p = f.path();
        CHECK(file_exists(p));
    }
    CHECK(!file_exists(p));
}
void the_file_is_gone_after_an_exception() {
    std::filesystem::path p;
    try {
        TempFile f(unique("throw"));
        p = f.path();
        throw std::runtime_error("later step failed");
    } catch (const std::runtime_error&) {}
    CHECK(!p.empty());
    CHECK(!file_exists(p));
}
void writes_append_and_read_returns_everything() {
    TempFile f(unique("rw"));
    CHECK(f.read() == "");
    f.write("ab");
    f.write("cd");
    CHECK(f.read() == "abcd");
}
void a_moved_to_owner_keeps_the_file_alive() {
    std::optional<TempFile> a;
    a.emplace(unique("move"));
    TempFile b(std::move(*a));
    a.reset();                       // the moved-from object is destroyed now
    CHECK(file_exists(b.path()));
}
void the_new_owner_deletes_it() {
    std::filesystem::path p;
    {
        TempFile a(unique("move2"));
        TempFile b(std::move(a));
        p = b.path();
    }
    CHECK(!file_exists(p));
}
void two_files_are_independent() {
    TempFile a(unique("one")), b(unique("two"));
    a.write("x");
    CHECK(b.read() == "");
    CHECK(a.path() != b.path());
}
void a_name_that_cannot_be_created_throws() {
    CHECK_THROWS(TempFile("no-such-directory-cp1/inside"));
}

int main() {
    RUN(the_file_exists_inside_the_scope_and_is_gone_after);
    RUN(the_file_is_gone_after_an_exception);
    RUN(writes_append_and_read_returns_everything);
    RUN(a_moved_to_owner_keeps_the_file_alive);
    RUN(the_new_owner_deletes_it);
    RUN(two_files_are_independent);
    RUN(a_name_that_cannot_be_created_throws);
    return check::report();
}
