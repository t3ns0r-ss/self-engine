// rev-1-3: this code chooses behaviour with a tag and a switch, so every new channel edits describe().
// Replace it with an interface: class Channel with a virtual describe(to) const that returns the text, safe to delete
// through a Channel pointer; EmailChannel returns "email to <to>" and SmsChannel returns "sms to <to>".
// broadcast(channels, to) returns one description per channel, in order. A Channel subclass written by the caller
// must work with broadcast. A null channel in the list throws std::invalid_argument.
#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

enum class Kind { Email, Sms };
inline std::string describe(Kind kind, const std::string& to) {
    switch (kind) {
        case Kind::Email: return "email to " + to;
        case Kind::Sms: return "sms to " + to;
    }
    throw std::logic_error("unknown kind");
}
