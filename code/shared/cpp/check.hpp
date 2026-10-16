// check.hpp: a minimal test helper used by every LLD unit and kit.
// CHECK(expr) records a failure (with file and line) if expr is false; it does not stop the test.
// CHECK_THROWS(expr) records a failure if expr does not throw.
// main() in each test file calls RUN(name) for each test function and returns report().
#pragma once
#include <cstdio>
#include <string>

namespace check {
inline int failures = 0;   // C++17 inline variable: one shared counter across all files
inline void fail(const char* file, int line, const char* text) {
    std::printf("FAIL %s:%d: %s\n", file, line, text);
    ++failures;
}
inline int report() {
    if (failures == 0) std::printf("all checks passed\n");
    return failures == 0 ? 0 : 1;
}
}  // namespace check

// The macros capture the expression's source text (#expr) and the location (__FILE__, __LINE__),
// which a normal function cannot do. That is the only reason they are macros.
#define CHECK(expr) \
    do { if (!(expr)) check::fail(__FILE__, __LINE__, #expr); } while (0)
#define CHECK_THROWS(expr) \
    do { bool threw_ = false; try { (void)(expr); } catch (...) { threw_ = true; } \
         if (!threw_) check::fail(__FILE__, __LINE__, "expected exception: " #expr); } while (0)
#define RUN(test_function) \
    do { std::printf("- %s\n", #test_function); test_function(); } while (0)
