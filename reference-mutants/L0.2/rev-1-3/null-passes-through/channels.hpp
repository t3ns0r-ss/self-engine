// rev-1-3: channels behind an interface instead of a tag and a switch.
#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Channel {
public:
    virtual ~Channel() = default;
    virtual std::string describe(const std::string& to) const = 0;
};
class EmailChannel final : public Channel {
public:
    std::string describe(const std::string& to) const override { return "email to " + to; }
};
class SmsChannel final : public Channel {
public:
    std::string describe(const std::string& to) const override { return "sms to " + to; }
};
inline std::vector<std::string> broadcast(const std::vector<std::unique_ptr<Channel>>& channels, const std::string& to) {
    std::vector<std::string> out;
    for (const auto& c : channels) {
        out.push_back(c->describe(to));
    }
    return out;
}
