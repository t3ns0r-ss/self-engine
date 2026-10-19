// cp-1: a temporary file that is always deleted.
#pragma once
#include <filesystem>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <utility>

class TempFile {
public:
    explicit TempFile(const std::string& name) : path_(std::filesystem::temp_directory_path() / name) {
        std::ofstream out(path_);
        if (!out) throw std::runtime_error("cannot create " + path_.string());
    }
    TempFile(const TempFile&) = delete;
    TempFile& operator=(const TempFile&) = delete;
    TempFile(TempFile&& other) noexcept : path_(other.path_) {}
    TempFile& operator=(TempFile&&) = delete;
    ~TempFile() {
        if (!path_.empty()) {
            std::error_code ignored;
            std::filesystem::remove(path_, ignored);   // a destructor must not throw
        }
    }
    const std::filesystem::path& path() const { return path_; }
    void write(const std::string& text) {
        std::ofstream out(path_, std::ios::app);
        out << text;
    }
    std::string read() const {
        std::ifstream in(path_);
        return {std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()};
    }
private:
    std::filesystem::path path_;
};
