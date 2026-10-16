#include "check.hpp"
#include "{{PACKAGE}}.hpp"

// TODO: behaviour tests through the public interface only.
void todo() { CHECK(false); }

int main() {
    RUN(todo);
    return check::report();
}
