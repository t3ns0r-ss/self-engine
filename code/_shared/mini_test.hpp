// A tiny test harness for LLD units (DESIGN_TRACKS_PLAN.md Section 9.2). Standard library only.
// One test file per unit defines MINI_TEST_MAIN before including this header; that file gets main().
//   TEST(name) { ... }            registers a test
//   CHECK(cond)                   fails the test when cond is false
//   CHECK_EQ(a, b)                fails when a != b, printing both values (they must be printable with <<)
//   CHECK_THROWS(expr, ExType)    fails unless evaluating expr throws ExType
#pragma once
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace mt {

struct Failure {
    std::string message;
};

struct Case {
    const char* name;
    void (*run)();
};

inline std::vector<Case>& cases() {
    static std::vector<Case> all;
    return all;
}

struct Registrar {
    Registrar(const char* name, void (*run)()) { cases().push_back({name, run}); }
};

inline std::string where(const char* file, int line) {
    return std::string(file) + ":" + std::to_string(line);
}

template <typename A, typename B>
void check_eq(const A& a, const B& b, const char* ea, const char* eb, const char* file, int line) {
    if (!(a == b)) {
        std::ostringstream out;
        out << where(file, line) << ": " << ea << " == " << eb << " failed: " << a << " vs " << b;
        throw Failure{out.str()};
    }
}

inline int run_all() {
    int failed = 0;
    for (const Case& c : cases()) {
        try {
            c.run();
        } catch (const Failure& f) {
            ++failed;
            std::cout << "FAIL " << c.name << ": " << f.message << "\n";
        } catch (const std::exception& e) {
            ++failed;
            std::cout << "FAIL " << c.name << ": unexpected exception: " << e.what() << "\n";
        }
    }
    std::cout << cases().size() << " tests, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}

}  // namespace mt

#define TEST(name)                                          \
    static void name();                                     \
    static mt::Registrar mt_registrar_##name(#name, name);  \
    static void name()

#define CHECK(cond)                                                                   \
    do {                                                                              \
        if (!(cond)) throw mt::Failure{mt::where(__FILE__, __LINE__) + ": " #cond " failed"}; \
    } while (0)

#define CHECK_EQ(a, b) mt::check_eq((a), (b), #a, #b, __FILE__, __LINE__)

#define CHECK_THROWS(expr, ExType)                                                    \
    do {                                                                              \
        bool mt_threw = false;                                                        \
        try {                                                                         \
            (void)(expr);                                                             \
        } catch (const ExType&) {                                                     \
            mt_threw = true;                                                          \
        }                                                                             \
        if (!mt_threw) throw mt::Failure{mt::where(__FILE__, __LINE__) + ": " #expr " did not throw " #ExType}; \
    } while (0)

#ifdef MINI_TEST_MAIN
int main() { return mt::run_all(); }
#endif
