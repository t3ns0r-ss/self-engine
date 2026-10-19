#include <memory>

struct Parent;
struct Child { std::shared_ptr<Parent> parent; };      // MISTAKE: the back pointer is an owner too
struct Parent { std::shared_ptr<Child> child; };

int main() {
    auto p = std::make_shared<Parent>();
    p->child = std::make_shared<Child>();
    p->child->parent = p;              // p and child now keep each other alive for ever
    return 0;
}
