// rev-1-3: this Stack reuses std::vector by inheriting from it, so every vector operation (erase, insert, operator[])
// is also a Stack operation and can break "pop returns the last push".
// Rewrite it so that the vector is a private member and only push, pop, top, size, empty and clear exist.
// pop and top on an empty stack throw std::out_of_range. Stack must not derive from std::vector.
#pragma once
#include <cstddef>
#include <stdexcept>
#include <vector>

class Stack : public std::vector<int> {
public:
    void push(int v) { push_back(v); }
    int pop() {
        if (empty()) throw std::out_of_range("pop on an empty stack");
        int v = back();
        pop_back();
        return v;
    }
    int top() const {
        if (empty()) throw std::out_of_range("top of an empty stack");
        return back();
    }
};
