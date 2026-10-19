#include <string>

class Label {                          // MISTAKE: keeps a reference to something the caller may destroy first
public:
    explicit Label(const std::string& text) : text_(text) {}
    std::size_t size() const { return text_.size(); }
private:
    const std::string& text_;
};

int main() {
    Label l(std::string(40, 'x'));     // the temporary string dies at the end of this statement
    return static_cast<int>(l.size()) - 40;   // reads through a dead reference
}
