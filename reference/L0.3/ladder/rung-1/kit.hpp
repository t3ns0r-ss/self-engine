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

