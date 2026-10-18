#pragma once
#include <stdexcept>
#include <string>

class Notifier {
public:
    std::string send(const std::string& channel, const std::string& to, const std::string& text) const {
        if (channel == "EMAIL") return "EMAIL to " + to + ": " + text;
        if (channel == "SMS") return "SMS to " + to + ": " + text.substr(0, 160);
        throw std::invalid_argument("unknown channel: " + channel);
    }
};
