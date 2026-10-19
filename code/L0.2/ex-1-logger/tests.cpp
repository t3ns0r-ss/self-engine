#include "check.hpp"
#include "logger.hpp"

template <class L>
void use(L& log) {
    log.info("started");
    log.error("disk full");
}
void the_concrete_class_does_the_job() {
    Logger log;
    use(log);
    CHECK(log.lines().size() == 2);
    CHECK(log.lines()[0] == "INFO started");
    CHECK(log.lines()[1] == "ERROR disk full");
}
void the_interface_version_behaves_identically() {
    LoggerImpl impl;
    ILogger& log = impl;
    use(log);
    CHECK(log.lines().size() == 2);
    CHECK(log.lines()[0] == "INFO started");
    CHECK(log.lines()[1] == "ERROR disk full");
}
void the_interface_changes_no_behaviour_and_adds_a_pointer() {
    CHECK(sizeof(LoggerImpl) == sizeof(Logger) + sizeof(void*));
}

int main() {
    RUN(the_concrete_class_does_the_job);
    RUN(the_interface_version_behaves_identically);
    RUN(the_interface_changes_no_behaviour_and_adds_a_pointer);
    return check::report();
}
