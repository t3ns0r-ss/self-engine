// A text editor that saves a document through three collaborators. Every call between objects is recorded in `trace`.
#pragma once
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

inline std::vector<std::string> trace;
inline void call(const char* from, const char* to, const char* what) { trace.push_back(std::string(from) + "->" + to + ": " + what); }
struct DiskFull : std::runtime_error { using std::runtime_error::runtime_error; };

class Document {
public:
    explicit Document(std::string text) : text_(std::move(text)) {}
    std::string serialise() const { return text_; }
private:
    std::string text_;
};
class Storage {
public:
    explicit Storage(std::size_t capacity) : capacity_(capacity) {}
    void write(const std::string& name, const std::string& text) {
        if (text.size() > capacity_) { partial_ = name; throw DiskFull("disk full"); }
        files_[name] = text;
    }
    void remove_partial(const std::string&) { partial_.clear(); }
    bool has(const std::string& name) const { return files_.count(name) > 0; }
private:
    std::size_t capacity_;
    std::string partial_;
    std::map<std::string, std::string> files_;
};
class Notifier {
public:
    void saved(const std::string&) { ++saved_; }
    void failed(const std::string&) { ++failed_; }
private:
    int saved_ = 0;
    int failed_ = 0;
};
class Editor {
public:
    Editor(Document& doc, Storage& storage, Notifier& notifier) : doc_(doc), storage_(storage), notifier_(notifier) {}
    bool save(const std::string& name) {
        call("Editor", "Document", "serialise");
        std::string text = doc_.serialise();
        try {
            call("Editor", "Storage", "write");
            storage_.write(name, text);
        } catch (const DiskFull&) {
            call("Editor", "Storage", "remove_partial");
            storage_.remove_partial(name);
            call("Editor", "Notifier", "failed");
            notifier_.failed(name);
            return false;
        }
        call("Editor", "Notifier", "saved");
        notifier_.saved(name);
        return true;
    }
private:
    Document& doc_;
    Storage& storage_;
    Notifier& notifier_;
};
