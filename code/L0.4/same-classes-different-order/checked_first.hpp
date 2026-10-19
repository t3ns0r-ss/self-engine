// Variant checked_first: the same three classes and the same members; only the order of the calls inside place_order differs.
#pragma once
#include <stdexcept>
#include <string>
#include <vector>

namespace checked_first {
inline std::vector<std::string> trace;
inline void call(const char* from, const char* to, const char* what) { trace.push_back(std::string(from) + "->" + to + ": " + what); }

class Inventory {
public:
    void reserve(int n) { if (n > left_) throw std::runtime_error("out of stock"); left_ -= n; }
    int left() const { return left_; }
private:
    int left_ = 1;
};
class Mailer {
public:
    void send() { ++sent_; }
    int sent() const { return sent_; }
private:
    int sent_ = 0;
};
class Shop {
public:
    Shop(Inventory& inventory, Mailer& mailer) : inventory_(inventory), mailer_(mailer) {}
    void place_order(int qty) {
        call("Shop", "Inventory", "reserve");
        inventory_.reserve(qty);
        call("Shop", "Mailer", "send");
        mailer_.send();
    }
private:
    Inventory& inventory_;
    Mailer& mailer_;
};
}  // namespace checked_first
