#include <string>

const std::string& longest(const std::string& a, const std::string& b) {
    return a.size() >= b.size() ? a : b;
}

const std::string& make_label(int n) {
    std::string label = "item-" + std::to_string(n);
    return label;                      // MISTAKE: a reference to a local that dies at the closing brace
}

int main() {
    const std::string& s = make_label(7);
    return static_cast<int>(s.size()) - 6;   // reads a dead object
}
