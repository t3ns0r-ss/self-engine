// An order placed through four objects. Every call between objects is recorded in `trace` as "Caller->Callee: function",
// so a sequence diagram can be checked against what the program really did.
#pragma once
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

inline std::vector<std::string> trace;
inline void call(const char* from, const char* to, const char* what) { trace.push_back(std::string(from) + "->" + to + ": " + what); }

struct OutOfStock : std::runtime_error { using std::runtime_error::runtime_error; };
struct PaymentDeclined : std::runtime_error { using std::runtime_error::runtime_error; };

class Inventory {
public:
    void stock(const std::string& sku, int n) { have_[sku] += n; }
    int have(const std::string& sku) const { auto i = have_.find(sku); return i == have_.end() ? 0 : i->second; }
    void reserve(const std::string& sku, int n) {
        if (have(sku) < n) throw OutOfStock("out of stock: " + sku);
        have_[sku] -= n;
    }
    void release(const std::string& sku, int n) { have_[sku] += n; }
private:
    std::map<std::string, int> have_;
};

class Payments {
public:
    explicit Payments(int limit_cents) : limit_(limit_cents) {}
    void charge(int cents) { if (cents > limit_) throw PaymentDeclined("declined"); }
private:
    int limit_;
};

class Mailer {
public:
    void send(const std::string& to, const std::string& text) { sent_.push_back(to + ": " + text); }
    std::size_t sent() const { return sent_.size(); }
private:
    std::vector<std::string> sent_;
};

class Shop {
public:
    Shop(Inventory& inventory, Payments& payments, Mailer& mailer) : inventory_(inventory), payments_(payments), mailer_(mailer) {}
    void place_order(const std::string& to, const std::string& sku, int qty, int unit_cents) {
        call("Shop", "Inventory", "reserve");
        inventory_.reserve(sku, qty);
        try {
            call("Shop", "Payments", "charge");
            payments_.charge(qty * unit_cents);
        } catch (const PaymentDeclined&) {
            call("Shop", "Inventory", "release");
            inventory_.release(sku, qty);              // give the stock back before the failure leaves the shop
            throw;
        }
        call("Shop", "Mailer", "send");
        mailer_.send(to, "order confirmed");
    }
private:
    Inventory& inventory_;
    Payments& payments_;
    Mailer& mailer_;
};
