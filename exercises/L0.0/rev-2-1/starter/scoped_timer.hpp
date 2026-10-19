// rev-2-1: a timer that records the elapsed time even when the function returns early or throws.
#pragma once
#include <stdexcept>
#include <vector>

// ScopedTimer(out, now) reads now() once when it is created. When it is destroyed, on any way out of its scope,
// it appends now() - start to `out`. It cannot be copied; it can be moved, and a moved-from timer records nothing.
class ScopedTimer {
public:
    ScopedTimer(std::vector<long long>& out, long long (*now)()) { throw std::logic_error("not implemented"); }
};
