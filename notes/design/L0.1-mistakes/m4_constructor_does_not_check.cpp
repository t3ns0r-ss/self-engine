#include <cstdio>
#include <string>

class Percentage {
public:
    explicit Percentage(int v) : value_(v) {}                 // MISTAKE: no check, so 250 is a Percentage
    long long of(long long total) const { return total * value_ / 100; }
private:
    int value_;
};

int main() {
    Percentage p(250);
    std::printf("250%% of 1000 = %lld\n", p.of(1000));
    return p.of(1000) > 1000 ? 1 : 0;
}
