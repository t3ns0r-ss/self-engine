// The public header of the L0.3 ladder: every rung adds one piece to this file.
#pragma once
#include <concepts>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

// Rung 1: composition. A Car owns its Engine; the engine is built with the car and destroyed with it.
inline std::vector<std::string> events;   // what was built and destroyed, in order
class Engine {
public:
    Engine() { events.push_back("engine built"); }
    ~Engine() { events.push_back("engine destroyed"); }
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    void start() { running_ = true; }
    bool running() const { return running_; }
private:
    bool running_ = false;
};
class Car {
public:
    Car() { events.push_back("car built"); }
    ~Car() { events.push_back("car destroyed"); }
    void start() { engine_.start(); }
    bool running() const { return engine_.running(); }
private:
    Engine engine_;
};

// Rung 2: aggregation. A Team refers to Players that exist on their own; it never builds, copies or destroys them.
inline int live_players = 0;
inline int player_copies = 0;
struct Player {
    std::string name;
    int score = 0;
    Player(std::string n, int s) : name(std::move(n)), score(s) { ++live_players; }
    Player(const Player& o) : name(o.name), score(o.score) { ++live_players; ++player_copies; }
    Player& operator=(const Player&) = default;
    ~Player() { --live_players; }
};
class Team {
public:
    void add(const Player& p) { members_.push_back(&p); }
    void add(Player&&) = delete;
    std::size_t size() const { return members_.size(); }
    int total_score() const {
        int sum = 0;
        for (const Player* p : members_) sum += p->score;
        return sum;
    }
    std::vector<std::string> names() const {
        std::vector<std::string> out;
        for (const Player* p : members_) out.push_back(p->name);
        return out;
    }
private:
    std::vector<const Player*> members_;
};
template <class T> concept CanAddTemporary = requires(T t) { t.add(Player{"tmp", 0}); };

// Rung 3: inheritance needs a true is-a. Rect is finished; Square must keep every promise of a square without deriving from Rect.
using Len = long long;
class Rect {
public:
    Rect(Len w, Len h) : w_(w), h_(h) {}
    virtual ~Rect() = default;
    virtual void set_width(Len w) { w_ = w; }
    virtual void set_height(Len h) { h_ = h; }
    Len width() const { return w_; }
    Len height() const { return h_; }
    Len area() const { return w_ * h_; }
private:
    Len w_, h_;
};
inline bool keeps_rect_promise(Rect& r) {
    const Len h = r.height();
    r.set_width(5);
    if (r.width() != 5 || r.height() != h) return false;
    const Len w = r.width();
    r.set_height(7);
    return r.height() == 7 && r.width() == w && r.area() == w * 7;
}
class Square {
public:
    explicit Square(Len side) : side_(side) {}
    Len side() const { return side_; }
    Len area() const { return side_ + side_; }
    Square scaled(Len k) const { return Square(side_ * k); }
    Rect as_rect() const { return Rect(side_, side_); }
private:
    Len side_;
};

