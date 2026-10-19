#include <cstdlib>
#include <fstream>
#include "booking.hpp"

template <class F> void scenario(const char* name, F f) {
    trace.clear();
    call("Test", "Scheduler", "book");
    try { f(); } catch (const std::exception&) {}
    if (const char* dir = std::getenv("TRACE_DIR")) {
        std::ofstream out(std::string(dir) + "/" + name + ".txt");
        for (const auto& l : trace) out << l << "\n";
    }
}
int main() {
    Room r("blue"); Person p("ann@example.com");
    EmailNotifier mail; Scheduler s(mail);
    scenario("booked", [&] { s.book(r, p, 9); });
    scenario("conflict", [&] { s.book(r, p, 9); });
}
