// The public header of the L0.0 ladder: every rung adds one piece to this file.
#pragma once
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

// Rung 1: a connection that closes itself.
struct Log {                     // counts what happened, so the tests can see it
    int opened = 0;
    int closed = 0;
};

class Connection {
public:
    explicit Connection(Log& log) : log_(&log) { ++log_->opened; }
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    Connection(Connection&& other) noexcept : log_(std::exchange(other.log_, nullptr)) {}
    Connection& operator=(Connection&&) = delete;
    ~Connection() { if (log_) ++log_->closed; }
private:
    Log* log_;
};

// Rung 2: a function that returns a heap object.
class Report {
public:
    explicit Report(int total) : total_(total) { ++live_; }
    Report(const Report&) = delete;
    Report& operator=(const Report&) = delete;
    ~Report() { --live_; }
    int total() const { return total_; }
    static int live() { return live_; }
private:
    int total_;
    inline static int live_ = 0;
};

inline std::unique_ptr<Report> make_report(int n) {
    if (n < 1) throw std::invalid_argument("n must be at least 1");
    int sum = 0;
    for (int i = 1; i <= n; ++i) sum += i;
    return std::make_unique<Report>(sum);
}

// Rung 3: two owners really need the same object.
class Image {
public:
    explicit Image(std::string name) : name_(std::move(name)) { ++live_; }
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;
    ~Image() { --live_; }
    const std::string& name() const { return name_; }
    static int live() { return live_; }
private:
    std::string name_;
    inline static int live_ = 0;
};

class ImageCache {
public:
    std::shared_ptr<Image> get(const std::string& name) {
        if (auto it = images_.find(name); it != images_.end()) {
            if (auto alive = it->second.lock()) return alive;
        }
        auto fresh = std::make_shared<Image>(name);
        images_[name] = fresh;
        return fresh;
    }
private:
    std::unordered_map<std::string, std::weak_ptr<Image>> images_;
};

// Rung 4: a function that only reads an object it does not own.
inline std::size_t name_length(const Image& image) { return image.name().size(); }

// Rung 5: a small value type that is copied freely.
struct Point {
    int x = 0;
    int y = 0;
};

inline Point midpoint(Point a, Point b) { return {(a.x + b.x) / 2, (a.y + b.y) / 2}; }

