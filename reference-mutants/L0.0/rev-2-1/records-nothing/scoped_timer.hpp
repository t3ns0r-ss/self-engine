// rev-2-1: a timer that records the elapsed time even when the function returns early or throws.
#pragma once
#include <utility>
#include <vector>

class ScopedTimer {
public:
    ScopedTimer(std::vector<long long>& out, long long (*now)()) : out_(&out), now_(now), start_(now()) {}
    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer& operator=(const ScopedTimer&) = delete;
    ScopedTimer(ScopedTimer&& other) noexcept : out_(std::exchange(other.out_, nullptr)), now_(other.now_), start_(other.start_) {}
    ScopedTimer& operator=(ScopedTimer&&) = delete;
    ~ScopedTimer() {}
private:
    std::vector<long long>* out_;
    long long (*now_)();
    long long start_;
};
