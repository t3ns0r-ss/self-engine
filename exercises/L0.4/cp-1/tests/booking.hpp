// Room booking. Every call between the scheduler and its collaborators is recorded in `trace`.
#pragma once
#include <stdexcept>
#include <string>
#include <vector>

inline std::vector<std::string> trace;
inline void call(const char* from, const char* to, const char* what) { trace.push_back(std::string(from) + "->" + to + ": " + what); }

struct Conflict : std::runtime_error { using std::runtime_error::runtime_error; };

class Person {
public:
    explicit Person(std::string email) : email_(std::move(email)) {}
    const std::string& email() const { return email_; }
private:
    std::string email_;
};
class Room {
public:
    explicit Room(std::string name) : name_(std::move(name)) {}
    const std::string& name() const { return name_; }
private:
    std::string name_;
};
class Booking {
public:
    Booking(const Room& room, const Person& who, int hour) : room_(&room), who_(&who), hour_(hour) {}
    bool same_slot(const Room& r, int hour) const { return room_ == &r && hour_ == hour; }
private:
    const Room* room_;
    const Person* who_;
    int hour_;
};
class Calendar {
public:
    bool free(const Room& r, int hour) const {
        for (const Booking& b : bookings_) if (b.same_slot(r, hour)) return false;
        return true;
    }
    void add(const Room& r, const Person& p, int hour) { bookings_.emplace_back(r, p, hour); }
    std::size_t size() const { return bookings_.size(); }
private:
    std::vector<Booking> bookings_;
};
class Notifier {
public:
    virtual ~Notifier() = default;
    virtual void send(const std::string& to, const std::string& text) = 0;
};
class EmailNotifier : public Notifier {
public:
    void send(const std::string& to, const std::string& text) override { outbox_.push_back(to + ": " + text); }
private:
    std::vector<std::string> outbox_;
};
class Scheduler {
public:
    explicit Scheduler(Notifier& notifier) : notifier_(notifier) {}
    void book(const Room& room, const Person& who, int hour) {
        call("Scheduler", "Calendar", "free");
        if (!calendar_.free(room, hour)) throw Conflict("slot taken");
        call("Scheduler", "Calendar", "add");
        calendar_.add(room, who, hour);
        call("Scheduler", "Notifier", "send");
        notifier_.send(who.email(), "booked " + room.name());
    }
private:
    Calendar calendar_;
    Notifier& notifier_;
};
