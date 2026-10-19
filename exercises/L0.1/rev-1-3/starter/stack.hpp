// rev-1-3: the Stack below has a public size field and trusts its callers. Make it protect its own rule:
// 0 <= size <= capacity (4), and a refused call changes nothing. Add a size() function; push on a full stack throws
// std::length_error and pop on an empty one throws std::out_of_range.
#pragma once
#include <stdexcept>

struct Stack {
    int items[4];
    int size = 0;
    void push(int v) { items[size++] = v; }
    int pop() { return items[--size]; }
};
