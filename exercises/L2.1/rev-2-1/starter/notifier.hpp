#pragma once
#include <memory>
#include <stdexcept>
#include <string>

// A delivery channel: turns a recipient and a text into the message that is sent.
class Channel {
public:
    virtual ~Channel() = default;
    virtual std::string send(const std::string& to, const std::string& text) const = 0;
};

enum class Kind { Email, Sms, Push };

class Notifier {
public:
    // The old way: a type code.
    std::string send(Kind kind, const std::string& to, const std::string& text) const {
        switch (kind) {
            case Kind::Email: return "EMAIL to " + to + ": " + text;
            case Kind::Sms: return "SMS to " + to + ": " + text.substr(0, 160);
            case Kind::Push: return "PUSH to " + to + ": " + text.substr(0, 60);
        }
        throw std::invalid_argument("unknown kind");
    }
    // The new way: channels by name. Not supported yet.
    void add_channel(const std::string&, std::unique_ptr<Channel>) { throw std::logic_error("not implemented"); }
    std::string send(const std::string&, const std::string&, const std::string&) const { throw std::logic_error("not implemented"); }
};
