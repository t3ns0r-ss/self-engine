// A connection to a pretend server. Opening it is a side effect (the log counts it), and closing is the
// destructor's job, so every way out of the scope that owns the Connection closes it once.
#pragma once
#include <utility>

struct Log {            // counts what happened, so tests can see it
    int opened = 0;
    int closed = 0;
};

class Connection {
public:
    explicit Connection(Log& log) : log_(&log) { ++log_->opened; }
    Connection(const Connection&) = delete;             // copying would mean two owners closing one connection
    Connection& operator=(const Connection&) = delete;
    Connection(Connection&& other) noexcept : log_(std::exchange(other.log_, nullptr)) {}   // ownership moves
    Connection& operator=(Connection&&) = delete;
    ~Connection() { if (log_) ++log_->closed; }
private:
    Log* log_;          // null in a moved-from Connection: nothing left to close
};
