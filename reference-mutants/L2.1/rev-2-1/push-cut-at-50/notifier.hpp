#pragma once
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

// A delivery channel: turns a recipient and a text into the message that is sent.
class Channel {
public:
    virtual ~Channel() = default;
    virtual std::string send(const std::string& to, const std::string& text) const = 0;
};

class EmailChannel final : public Channel {
public:
    std::string send(const std::string& to, const std::string& text) const override { return "EMAIL to " + to + ": " + text; }
};
class SmsChannel final : public Channel {
public:
    std::string send(const std::string& to, const std::string& text) const override { return "SMS to " + to + ": " + text.substr(0, 160); }
};
class PushChannel final : public Channel {
public:
    std::string send(const std::string& to, const std::string& text) const override { return "PUSH to " + to + ": " + text.substr(0, 50); }
};

class Notifier {
public:
    Notifier() {
        add_channel("EMAIL", std::make_unique<EmailChannel>());
        add_channel("SMS", std::make_unique<SmsChannel>());
        add_channel("PUSH", std::make_unique<PushChannel>());
    }
    // Adds a channel, or replaces an existing one of the same name.
    void add_channel(const std::string& name, std::unique_ptr<Channel> channel) {
        if (!channel) throw std::invalid_argument("null channel: " + name);
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
