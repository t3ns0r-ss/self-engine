// A logger used by every module and never replaced: a concrete class does the whole job.
#pragma once
#include <string>
#include <vector>

class Logger {
public:
    void info(const std::string& message) { lines_.push_back("INFO " + message); }
    void error(const std::string& message) { lines_.push_back("ERROR " + message); }
    const std::vector<std::string>& lines() const { return lines_; }
private:
    std::vector<std::string> lines_;
};

// The same thing behind an interface, written only to compare cost: one more class, one more file, one more pointer.
class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void info(const std::string& message) = 0;
    virtual void error(const std::string& message) = 0;
    virtual const std::vector<std::string>& lines() const = 0;
};
class LoggerImpl final : public ILogger {
public:
    void info(const std::string& message) override { lines_.push_back("INFO " + message); }
    void error(const std::string& message) override { lines_.push_back("ERROR " + message); }
    const std::vector<std::string>& lines() const override { return lines_; }
private:
    std::vector<std::string> lines_;
};
