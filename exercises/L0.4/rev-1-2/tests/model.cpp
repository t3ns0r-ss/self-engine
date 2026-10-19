#include <cstdlib>
#include <fstream>
#include "model.hpp"

template <class F> void scenario(const char* name, F f) {
    trace.clear();
    call("Test", "Refunds", "refund");
    try { f(); } catch (const std::exception&) {}
    if (const char* dir = std::getenv("TRACE_DIR")) {
        std::ofstream out(std::string(dir) + "/" + name + ".txt");
        for (const auto& l : trace) out << l << "\n";
    }
}
int main() {
    Ledger l; Wallet w; Refunds r(l, w);
    l.record(7, 500);
    scenario("ok", [&] { r.refund(7); });
    scenario("not_found", [&] { r.refund(7); });
}
