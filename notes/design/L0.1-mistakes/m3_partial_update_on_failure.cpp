#include <cstdio>
#include <stdexcept>

class Seats {
public:
    explicit Seats(int capacity) : capacity_(capacity) {}
    void book(int n) {
        booked_ += n;                  // MISTAKE: changes the state first and checks afterwards
        if (booked_ > capacity_) throw std::invalid_argument("over capacity");
    }
    int booked() const { return booked_; }
private:
    int capacity_;
    int booked_ = 0;
};

int main() {
    Seats s(5);
    try { s.book(8); } catch (const std::invalid_argument&) {}
    std::printf("booked after a refused booking = %d of 5\n", s.booked());
    return s.booked() > 5 ? 1 : 0;
}
