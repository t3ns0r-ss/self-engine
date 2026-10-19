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

// Constructing a Connection counts one open in the log; destroying it counts one close, whichever way the scope ends.
// It must not be copyable (two owners would close twice) but must be movable (the new owner closes, the old one does not).
class Connection {
public:
    explicit Connection(Log& log) { throw std::logic_error("not implemented"); }
};

