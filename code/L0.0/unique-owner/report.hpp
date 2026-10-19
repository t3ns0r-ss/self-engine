// A heap object with one owner. Report counts how many are alive, so tests can see leaks and double deletes.
#pragma once
#include <memory>
#include <stdexcept>
#include <vector>

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

// The caller receives sole ownership. Throws std::invalid_argument for n < 1, and leaks nothing when it does.
inline std::unique_ptr<Report> make_report(int n) {
    if (n < 1) throw std::invalid_argument("n must be at least 1");
    int sum = 0;
    for (int i = 1; i <= n; ++i) sum += i;
    return std::make_unique<Report>(sum);
}
