#include "check.hpp"
#include "notifier.hpp"

struct FaxChannel final : Channel {
    std::string send(const std::string& to, const std::string& text) const override { return "FAX to " + to + ": " + text; }
};

void built_in_channels_keep_their_messages() {
    Notifier n;
    CHECK(n.send("EMAIL", "ann", "hello") == "EMAIL to ann: hello");
    CHECK(n.send("SMS", "bob", std::string(200, 'x')) == "SMS to bob: " + std::string(160, 'x'));
    CHECK(n.send("PUSH", "cy", std::string(100, 'x')) == "PUSH to cy: " + std::string(60, 'x'));
}
void unknown_channel_throws() {
    Notifier n;
    CHECK_THROWS(n.send("FAX", "ann", "hi"));
}
void a_channel_defined_by_the_caller_can_be_added() {
    Notifier n;
    n.add_channel("FAX", std::make_unique<FaxChannel>());
    CHECK(n.send("FAX", "dee", "hi") == "FAX to dee: hi");
    CHECK(n.send("EMAIL", "ann", "hi") == "EMAIL to ann: hi");
}
void adding_an_existing_name_replaces_the_channel() {
    Notifier n;
    n.add_channel("EMAIL", std::make_unique<FaxChannel>());
    CHECK(n.send("EMAIL", "ann", "hi") == "FAX to ann: hi");
}
void a_null_channel_is_rejected() {
    Notifier n;
    CHECK_THROWS(n.add_channel("NULL", nullptr));
}

int main() {
    RUN(built_in_channels_keep_their_messages);
    RUN(unknown_channel_throws);
    RUN(a_channel_defined_by_the_caller_can_be_added);
    RUN(adding_an_existing_name_replaces_the_channel);
    RUN(a_null_channel_is_rejected);
    return check::report();
}
