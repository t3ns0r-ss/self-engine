// cp-1: a temporary file that is always deleted.
#pragma once
#include <filesystem>
#include <stdexcept>
#include <string>

// TempFile(name) creates an empty file called `name` in std::filesystem::temp_directory_path() and throws
// std::runtime_error if it cannot. The file is deleted when its owner goes away, on every way out of the scope.
// A TempFile cannot be copied but can be moved; after a move the new owner has the file and the old one has nothing.
// write(text) appends text; read() returns the whole content; path() is where the file lives.
class TempFile {
public:
    explicit TempFile(const std::string& name) { throw std::logic_error("not implemented"); }
    const std::filesystem::path& path() const { throw std::logic_error("not implemented"); }
    void write(const std::string& text) { throw std::logic_error("not implemented"); }
    std::string read() const { throw std::logic_error("not implemented"); }
};
