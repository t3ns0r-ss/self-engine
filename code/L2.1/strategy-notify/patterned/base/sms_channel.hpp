#pragma once
#include "channel.hpp"

class SmsChannel final : public Channel {
public:
    std::string send(const std::string& to, const std::string& text) const override {
        const std::string& t = text;
        return "SMS to " + to + ": " + t.substr(0, 160);
    }
};
