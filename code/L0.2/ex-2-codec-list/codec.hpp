// A codec chosen by name, while the program runs, from a list it reads at start-up: the interface earns its place.
#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Codec {
public:
    virtual ~Codec() = default;
    virtual std::string name() const = 0;
    virtual std::string encode(const std::string& text) const = 0;
};

class Upper final : public Codec {
public:
    std::string name() const override { return "upper"; }
    std::string encode(const std::string& text) const override {
        std::string out = text;
        for (char& c : out) if (c >= 'a' && c <= 'z') c = static_cast<char>(c - 'a' + 'A');
        return out;
    }
};
class Reverse final : public Codec {
public:
    std::string name() const override { return "reverse"; }
    std::string encode(const std::string& text) const override { return std::string(text.rbegin(), text.rend()); }
};

// The names come from outside (a configuration file); which classes exist is decided when the program runs.
inline std::vector<std::unique_ptr<Codec>> load_codecs(const std::vector<std::string>& names) {
    std::vector<std::unique_ptr<Codec>> out;
    for (const std::string& n : names) {
        if (n == "upper") out.push_back(std::make_unique<Upper>());
        else if (n == "reverse") out.push_back(std::make_unique<Reverse>());
        else throw std::invalid_argument("unknown codec: " + n);
    }
    return out;
}
inline std::string run_all(const std::vector<std::unique_ptr<Codec>>& codecs, std::string text) {
    for (const auto& c : codecs) text = c->encode(text);
    return text;
}
