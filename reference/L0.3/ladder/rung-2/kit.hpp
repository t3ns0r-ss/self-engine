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

