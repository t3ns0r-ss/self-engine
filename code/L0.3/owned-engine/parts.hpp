// Composition: a Car owns its Engine as a member, so the engine lives and dies with the car.
#pragma once
#include <string>
#include <vector>

inline std::vector<std::string> events;   // what was built and destroyed, in order

class Engine {
public:
    Engine() { events.push_back("engine built"); }
    ~Engine() { events.push_back("engine destroyed"); }
    Engine(const Engine&) = delete;              // one engine, one car
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
    Engine engine_;                              // composition: held by value, no pointer, nobody else can free it
};
