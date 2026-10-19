#include <cstdio>
#include <vector>

// A stack that reuses std::vector by inheriting from it.
class Stack : public std::vector<int> {
public:
    void push(int v) { push_back(v); }
    int pop() { int v = back(); pop_back(); return v; }
};

// A helper written elsewhere for any vector: it keeps only the first 2 elements.
void keep_first_two(std::vector<int>& v) {
    if (v.size() > 2) v.resize(2);
}

int main() {
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    keep_first_two(s);                                      // compiles: a Stack is a vector
    int top = s.pop();
    std::printf("popped %d (expected 3), then %d (expected 2)\n", top, s.pop());
    return top == 3 ? 0 : 1;
}
