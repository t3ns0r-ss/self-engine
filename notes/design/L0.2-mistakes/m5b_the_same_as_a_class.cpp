#include <cstdio>
#include <string>
#include <vector>

class Logger {
public:
    void info(const std::string& message) { lines_.push_back("INFO " + message); }
    const std::vector<std::string>& lines() const { return lines_; }
private:
    std::vector<std::string> lines_;
};

int main() {
    Logger l;
    l.info("hello");
    std::printf("%zu line(s), object size %zu bytes\n", l.lines().size(), sizeof(l));
}
