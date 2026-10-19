// Seats: a booking count that must stay between 0 and the capacity after every operation.
// A refused operation changes nothing: the object is exactly as it was before the call.
#pragma once
#include <stdexcept>

class Seats {
public:
    explicit Seats(int capacity) : capacity_(capacity) {
        if (capacity < 0) throw std::invalid_argument("capacity must not be negative");
    }
    int capacity() const { return capacity_; }
    int booked() const { return booked_; }
    int free() const { return capacity_ - booked_; }

    void book(int n) {
        if (n < 0 || n > free()) throw std::invalid_argument("cannot book that many");
        booked_ += n;                     // the check came first, so a refusal never gets here
    }
    void cancel(int n) {
        if (n < 0 || n > booked_) throw std::invalid_argument("cannot cancel that many");
        booked_ -= n;
    }
    // Moves bookings between two Seats as one step: either both change or neither does.
    static void transfer(Seats& from, Seats& to, int n) {
        if (n < 0 || n > from.booked_ || n > to.free()) throw std::invalid_argument("cannot transfer that many");
        from.booked_ -= n;
        to.booked_ += n;
    }
private:
    int capacity_;
    int booked_ = 0;
};
