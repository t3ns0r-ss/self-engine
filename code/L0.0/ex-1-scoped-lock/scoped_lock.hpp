// Worked example 1: a lock that must be released on every return path of a function.
#pragma once

class Door {                      // pretend lock: locked and unlocked by hand
public:
    void lock() { ++locks_; held_ = true; }
    void unlock() { ++unlocks_; held_ = false; }
    bool held() const { return held_; }
    int locks() const { return locks_; }
    int unlocks() const { return unlocks_; }
private:
    bool held_ = false;
    int locks_ = 0;
    int unlocks_ = 0;
};

class ScopedHold {                // locks in the constructor, unlocks in the destructor
public:
    explicit ScopedHold(Door& d) : door_(d) { door_.lock(); }
    ScopedHold(const ScopedHold&) = delete;
    ScopedHold& operator=(const ScopedHold&) = delete;
    ~ScopedHold() { door_.unlock(); }
private:
    Door& door_;                  // a reference: ScopedHold never owns the Door, it only uses it
};

// Four exits (three returns and one throw), one hold: the destructor covers all of them.
inline int classify(Door& d, int n) {
    ScopedHold hold(d);
    if (n < 0) throw n;
    if (n == 0) return 0;
    if (n < 10) return 1;
    return 2;
}
