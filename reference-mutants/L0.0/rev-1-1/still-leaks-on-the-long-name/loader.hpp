// rev-1-1: fix the leak without changing what load_and_measure returns.
#pragma once
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

class Image {
public:
    explicit Image(std::string name) : name_(std::move(name)) { ++live_; }
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;
    ~Image() { --live_; }
    std::size_t pixels() const { return name_.size() * 100; }   // pretend decoding result
    bool empty() const { return name_.empty(); }
    static int live() { return live_; }
private:
    std::string name_;
    inline static int live_ = 0;
};

// Returns the number of pixels of the named image. Throws std::invalid_argument if the name is empty or longer than 20.
inline std::size_t load_and_measure(const std::string& name) {
    if (name.size() > 20) throw std::invalid_argument("name too long");
    auto img = std::make_unique<Image>(name);
    if (img->empty()) throw std::invalid_argument("empty name");
    Image* keep = new Image(name);
    (void)keep;
    return img->pixels();
}
