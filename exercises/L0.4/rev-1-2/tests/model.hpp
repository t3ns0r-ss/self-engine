// Refunds. Every call between objects is recorded in `trace`.
#pragma once
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

inline std::vector<std::string> trace;
inline void call(const char* from, const char* to, const char* what) { trace.push_back(std::string(from) + "->" + to + ": " + what); }

struct NotFound : std::runtime_error { using std::runtime_error::runtime_error; };

class Ledger {
public:
    void record(int id, int cents) { paid_[id] = cents; }
    int find(int id) const { auto i = paid_.find(id); if (i == paid_.end()) throw NotFound("no such payment"); return i->second; }
    void mark_refunded(int id) { paid_.erase(id); }
private:
    std::map<int, int> paid_;
};
class Wallet {
public:
    void credit(int cents) { balance_ += cents; }
    int balance() const { return balance_; }
private:
    int balance_ = 0;
};
class Refunds {
public:
    Refunds(Ledger& ledger, Wallet& wallet) : ledger_(ledger), wallet_(wallet) {}
    void refund(int id) {
        call("Refunds", "Ledger", "find");
        int cents = ledger_.find(id);
        call("Refunds", "Wallet", "credit");
        wallet_.credit(cents);
        call("Refunds", "Ledger", "mark_refunded");
        ledger_.mark_refunded(id);
    }
private:
    Ledger& ledger_;
    Wallet& wallet_;
};
