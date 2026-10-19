// The public header of the L0.3 ladder: every rung adds one piece to this file.
#pragma once
#include <concepts>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

// Rung 1: composition. A Car owns its Engine; the engine is built with the car and destroyed with it.
// Engine is finished. Finish Car: it records "car built" and "car destroyed" in events, start() starts its own engine,
// running() asks it. The engine must be a member held by value, not a pointer: no allocation, nobody else can free it.
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
    Car() { throw std::logic_error("not implemented"); }
    ~Car() {}
    void start() { throw std::logic_error("not implemented"); }
    bool running() const { throw std::logic_error("not implemented"); }
};

