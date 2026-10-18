#include "check.hpp"
#include "make_notifier.hpp"

void email_sends_the_whole_text() {
    Notifier n = make_notifier();
    CHECK(n.send("EMAIL", "ann", "hello") == "EMAIL to ann: hello");
    CHECK(n.send("EMAIL", "ann", std::string(200, 'x')).size() == std::string("EMAIL to ann: ").size() + 200);
}
void sms_is_cut_at_160_characters() {
    Notifier n = make_notifier();
    CHECK(n.send("SMS", "bob", "hi") == "SMS to bob: hi");
    CHECK(n.send("SMS", "bob", std::string(200, 'x')) == "SMS to bob: " + std::string(160, 'x'));
}
void unknown_channel_throws() {
    Notifier n = make_notifier();
    CHECK_THROWS(n.send("FAX", "ann", "hi"));
}

int main() {
    RUN(email_sends_the_whole_text);
    RUN(sms_is_cut_at_160_characters);
    RUN(unknown_channel_throws);
    return check::report();
}
