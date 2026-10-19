#include <cstdio>
#include <stdexcept>

class Account {
public:
    explicit Account(long long cents) : cents_(cents) { if (cents < 0) throw std::invalid_argument("negative"); }
    long long& cents() { return cents_; }                      // MISTAKE: hands out a writable reference to the private field
private:
    long long cents_;
};

int main() {
    Account a(100);
    a.cents() = -999;                                          // the "private" field written from outside
    std::printf("balance = %lld\n", a.cents());
    return a.cents() < 0 ? 1 : 0;
}
