#pragma once
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include "channel.hpp"

class Notifier {
public:
    void add_channel(const std::string& name, std::unique_ptr<Channel> channel) {
        channels_[name] = std::move(channel);
    }
    std::string send(const std::string& channel, const std::string& to, const std::string& text) const {
        auto it = channels_.find(channel);
        if (it == channels_.end()) throw std::invalid_argument("unknown channel: " + channel);
        return it->second->send(to, text);
    }
private:
    std::map<std::string, std::unique_ptr<Channel>> channels_;
};
