// Deleting a derived object through a base pointer: the base destructor must be virtual.
#pragma once
#include <string>
#include <vector>

inline int live_buffers = 0;      // counts buffers acquired and not yet released

class Handler {
public:
    virtual ~Handler() = default;                  // virtual: delete through Handler* runs the derived destructor too
    virtual std::string name() const = 0;
};

class BufferedHandler final : public Handler {
public:
    BufferedHandler() : buffer_(1024, 'x') { ++live_buffers; }
    ~BufferedHandler() override { --live_buffers; }
    std::string name() const override { return "buffered"; }
private:
    std::vector<char> buffer_;
};
