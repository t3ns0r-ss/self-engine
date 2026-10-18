#pragma once
#include <memory>
#include "email_channel.hpp"
#include "notifier.hpp"
#include "sms_channel.hpp"

// Composition root: the only place that knows which channels exist.
inline Notifier make_notifier() {
    Notifier n;
    n.add_channel("EMAIL", std::make_unique<EmailChannel>());
    n.add_channel("SMS", std::make_unique<SmsChannel>());
    return n;
}
