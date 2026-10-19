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

// Rung 2: a function that returns a heap object.
class Report {
public:
    explicit Report(int total) : total_(total) { ++live_; }
    Report(const Report&) = delete;
    Report& operator=(const Report&) = delete;
    ~Report() { --live_; }
    int total() const { return total_; }
    static int live() { return live_; }
private:
    int total_;
    inline static int live_ = 0;
};

// Returns a Report whose total is 1 + 2 + ... + n, owned by the caller. Throws std::invalid_argument for n < 1.
// Whatever happens, no Report may be left alive that nobody owns.
inline std::unique_ptr<Report> make_report(int n) { throw std::logic_error("not implemented"); }

