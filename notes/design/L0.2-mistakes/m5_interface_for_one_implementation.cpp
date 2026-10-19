// MISTAKE: an interface and an Impl for a class that will only ever have one implementation.
#include <cstdio>
#include <string>
#include <vector>

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void info(const std::string& message) = 0;
    virtual const std::vector<std::string>& lines() const = 0;
};
class LoggerImpl final : public ILogger {
public:
    void info(const std::string& message) override { lines_.push_back("INFO " + message); }
    const std::vector<std::string>& lines() const override { return lines_; }
private:
    std::vector<std::string> lines_;
};

int main() {
    LoggerImpl l;
    l.info("hello");
    std::printf("%zu line(s), object size %zu bytes\n", l.lines().size(), sizeof(l));
}
