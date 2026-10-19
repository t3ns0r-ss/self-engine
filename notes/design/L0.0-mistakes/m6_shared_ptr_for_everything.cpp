#include <cstdio>
#include <memory>

struct Config { int values[16] = {}; };

int main() {                           // OVER-ENGINEERED: one owner, but shared_ptr everywhere "to be safe"
    std::printf("unique_ptr: %zu bytes, shared_ptr: %zu bytes\n", sizeof(std::unique_ptr<Config>), sizeof(std::shared_ptr<Config>));
    auto u = std::make_unique<Config>();
    auto s = std::make_shared<Config>();
    std::printf("use_count of the shared one: %ld; the unique one has no count to read\n", s.use_count());
    return u->values[0] + s->values[0];
}
