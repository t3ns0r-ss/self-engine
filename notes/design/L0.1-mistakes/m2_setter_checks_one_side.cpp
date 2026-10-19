#include <cstdio>
#include <stdexcept>

class DateRange {                      // rule: start <= end
public:
    DateRange(int start, int end) : start_(start), end_(end) {
        if (start > end) throw std::invalid_argument("start after end");
    }
    void set_start(int s) { if (s < 0) throw std::invalid_argument("negative"); start_ = s; }   // MISTAKE: never compares with end_
    int start() const { return start_; }
    int end() const { return end_; }
private:
    int start_, end_;
};

int main() {
    DateRange r(10, 20);
    r.set_start(50);
    std::printf("range = %d..%d\n", r.start(), r.end());
    return r.start() > r.end() ? 1 : 0;
}
