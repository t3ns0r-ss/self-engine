// rev-1-3: a Stack that holds a vector instead of being one.
#pragma once
#include <cstddef>
#include <stdexcept>
#include <vector>

class Stack {
public:
    void push(int v) { items_.push_back(v); }
    int pop() {
        if (items_.empty()) throw std::out_of_range("pop on an empty stack");
        int v = items_.back();
        items_.pop_back();
        return v;
    }
    int top() const {
        if (items_.empty()) return 0;
        return items_.back();
    }
    std::size_t size() const { return items_.size(); }
    bool empty() const { return items_.empty(); }
    void clear() { items_.clear(); }
private:
    std::vector<int> items_;
};
