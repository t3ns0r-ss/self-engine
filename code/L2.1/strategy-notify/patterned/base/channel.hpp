#pragma once
#include <string>

// The one signature every delivery channel shares.
class Channel {
public:
    virtual ~Channel() = default;   // deleting through a base pointer must run the derived destructor
    virtual std::string send(const std::string& to, const std::string& text) const = 0;
};
