// rev-1-3: the Stack below has a public size field and trusts its callers. Make it protect its own rule:
// 0 <= size <= capacity (4), and a refused call changes nothing. Add a size() function; push on a full stack throws
// std::length_error and pop on an empty one throws std::out_of_range.
#pragma once
#include <stdexcept>

class Stack {
public:
    void push(int v) {
        if (size_ == 4) throw std::length_error("stack is full");
        items_[size_++] = v;
    }
    int pop() {
        if (size_ == 0) throw std::out_of_range("stack is empty");
        return items_[--size_];
    }
    int size() const { return size_; }
private:
    int items_[4];
    int size_ = 0;
};
