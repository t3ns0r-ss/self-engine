// Reuse by composition or by inheritance: both stacks store ints in a std::vector.
#pragma once
#include <cstddef>
#include <stdexcept>
#include <vector>

// By inheritance: every vector operation is public too, including the ones that break "pop returns the last push".
class VecStack : public std::vector<int> {
public:
    void push(int v) { push_back(v); }
    int pop() {
        if (empty()) throw std::out_of_range("pop on an empty stack");
        int v = back();
        pop_back();
        return v;
    }
};

// By composition: the vector is private; only the operations written here exist.
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
        if (items_.empty()) throw std::out_of_range("top of an empty stack");
        return items_.back();
    }
    std::size_t size() const { return items_.size(); }
    bool empty() const { return items_.empty(); }
private:
    std::vector<int> items_;
};

template <class T> concept CanErase = requires(T t) { t.erase(t.begin()); };
template <class T> concept CanIndex = requires(T t) { t[0]; };
