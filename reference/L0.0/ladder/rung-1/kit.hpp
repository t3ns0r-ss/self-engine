// The public header of the L0.0 ladder: every rung adds one piece to this file.
#pragma once
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

// Rung 1: a connection that closes itself.
struct Log {                     // counts what happened, so the tests can see it
    int opened = 0;
    int closed = 0;
};

class Connection {
public:
    explicit Connection(Log& log) : log_(&log) { ++log_->opened; }
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    Connection(Connection&& other) noexcept : log_(std::exchange(other.log_, nullptr)) {}
    Connection& operator=(Connection&&) = delete;
    ~Connection() { if (log_) ++log_->closed; }
private:
    Log* log_;
};

