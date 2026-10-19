// Bird, FlyingBird, Penguin: put an operation in the base only if every class below it can keep the promise.
#pragma once
#include <string>

class Bird {
public:
    explicit Bird(std::string name) : name_(std::move(name)) {}
    virtual ~Bird() = default;
    const std::string& name() const { return name_; }
    virtual std::string eat() const { return name_ + " eats"; }
private:
    std::string name_;
};

class FlyingBird : public Bird {              // the promise "can fly" lives here, not in Bird
public:
    using Bird::Bird;
    virtual std::string fly() const { return name() + " flaps and flies"; }
};

class Sparrow final : public FlyingBird {
public:
    Sparrow() : FlyingBird("sparrow") {}
};

class Penguin final : public Bird {            // a Bird that makes no promise to fly
public:
    Penguin() : Bird("penguin") {}
    std::string swim() const { return name() + " swims"; }
};

inline std::string migrate(const FlyingBird& b) { return b.fly() + " south"; }   // written once, for every FlyingBird

template <class T> concept CanFly = requires(const T& t) { t.fly(); };
