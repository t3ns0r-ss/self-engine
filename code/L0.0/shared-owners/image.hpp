// A big object that several widgets may hold at once. Image counts how many are alive.
#pragma once
#include <memory>
#include <string>
#include <unordered_map>

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

// Hands out the same Image for the same name while anyone still holds it. The cache itself does not keep
// images alive: it holds std::weak_ptr, which observes without owning.
class ImageCache {
public:
    std::shared_ptr<Image> get(const std::string& name) {
        if (auto it = images_.find(name); it != images_.end()) {
            if (auto alive = it->second.lock()) return alive;   // lock() gives an owner, or null if it is gone
        }
        auto fresh = std::make_shared<Image>(name);
        images_[name] = fresh;
        return fresh;
    }
private:
    std::unordered_map<std::string, std::weak_ptr<Image>> images_;
};
