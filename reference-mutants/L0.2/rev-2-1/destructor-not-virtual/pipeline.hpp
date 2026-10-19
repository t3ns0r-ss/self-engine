// rev-2-1: a pipeline of steps chosen while the program runs.
#pragma once
#include <memory>
#include <stdexcept>
#include <vector>

class Step {
public:
    ~Step() = default;
    virtual long long apply(long long x) const = 0;
};
class AddStep final : public Step {
public:
    explicit AddStep(long long n) : n_(n) {}
    long long apply(long long x) const override { return x + n_; }
private:
    long long n_;
};
class MulStep final : public Step {
public:
    explicit MulStep(long long n) : n_(n) {}
    long long apply(long long x) const override { return x * n_; }
private:
    long long n_;
};
class Pipeline {
public:
    void add(std::unique_ptr<Step> s) {
        if (!s) throw std::invalid_argument("null step");
        steps_.push_back(std::move(s));
    }
    std::size_t size() const { return steps_.size(); }
    long long run(long long x) const {
        for (const auto& s : steps_) x = s->apply(x);
        return x;
    }
private:
    std::vector<std::unique_ptr<Step>> steps_;
};
