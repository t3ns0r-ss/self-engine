#include <cstdlib>
#include <fstream>
#include "model.hpp"

template <class F> void scenario(const char* name, F f) {
    trace.clear();
    call("Test", "Editor", "save");
    try { f(); } catch (const std::exception&) {}
    if (const char* dir = std::getenv("TRACE_DIR")) {
        std::ofstream out(std::string(dir) + "/" + name + ".txt");
        for (const auto& l : trace) out << l << "\n";
    }
}
int main() {
    Document doc("hello"); Storage st; Notifier n; Editor ed(doc, st, n);
    scenario("ok", [&] { ed.save("a.txt"); });
}
