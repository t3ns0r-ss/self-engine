// rev-2-1: a pipeline of steps chosen while the program runs.
#pragma once
#include <memory>
#include <stdexcept>
#include <vector>

// Step: an interface with apply(x), safe to delete through a Step pointer. AddStep(n) returns x + n and MulStep(n)
// returns x * n. Pipeline owns the steps it is given: add(nullptr) throws std::invalid_argument, size() is how many
// steps, run(x) feeds x through the steps in the order they were added. A Step subclass written by the caller must work.
class Step {
public:
    virtual ~Step() = default;
    virtual long long apply(long long x) const { throw std::logic_error("not implemented"); }
};
class AddStep final : public Step {
public:
    explicit AddStep(long long n) { throw std::logic_error("not implemented"); }
};
class MulStep final : public Step {
public:
    explicit MulStep(long long n) { throw std::logic_error("not implemented"); }
};
class Pipeline {
public:
    void add(std::unique_ptr<Step> s) { throw std::logic_error("not implemented"); }
    std::size_t size() const { throw std::logic_error("not implemented"); }
    long long run(long long x) const { throw std::logic_error("not implemented"); }
};
