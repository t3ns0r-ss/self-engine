#pragma once
#include "channel.hpp"

class EmailChannel final : public Channel {
public:
    std::string send(const std::string& to, const std::string& text) const override {
        const std::string& t = text;
        return "EMAIL to " + to + ": " + t;
    }
};
