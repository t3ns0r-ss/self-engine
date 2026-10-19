#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "check.hpp"
#include "channels.hpp"

static_assert(std::is_abstract_v<Channel>);
static_assert(std::has_virtual_destructor_v<Channel>);

struct Pager final : Channel {                  // a channel the original switch never knew about
    std::string describe(const std::string& to) const override { return "pager to " + to; }
};

void each_channel_describes_itself() {
    CHECK(EmailChannel().describe("bob") == "email to bob");
    CHECK(SmsChannel().describe("amy") == "sms to amy");
}
void broadcast_keeps_the_order() {
    std::vector<std::unique_ptr<Channel>> v;
    v.push_back(std::make_unique<SmsChannel>());
    v.push_back(std::make_unique<EmailChannel>());
    auto out = broadcast(v, "cy");
    CHECK(out.size() == 2);
    CHECK(out[0] == "sms to cy");
    CHECK(out[1] == "email to cy");
}
void a_new_channel_needs_no_edit_to_broadcast() {
    std::vector<std::unique_ptr<Channel>> v;
    v.push_back(std::make_unique<Pager>());
    v.push_back(std::make_unique<EmailChannel>());
    auto out = broadcast(v, "di");
    CHECK(out[0] == "pager to di");
    CHECK(out[1] == "email to di");
}
void an_empty_list_gives_nothing() {
    std::vector<std::unique_ptr<Channel>> v;
    CHECK(broadcast(v, "x").empty());
}
void a_null_channel_is_refused() {
    std::vector<std::unique_ptr<Channel>> v;
    v.push_back(std::make_unique<EmailChannel>());
    v.push_back(nullptr);
    CHECK_THROWS(broadcast(v, "x"));
}

int main() {
    RUN(each_channel_describes_itself);
    RUN(broadcast_keeps_the_order);
    RUN(a_new_channel_needs_no_edit_to_broadcast);
    RUN(an_empty_list_gives_nothing);
    RUN(a_null_channel_is_refused);
    return check::report();
}
