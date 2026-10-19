// A text editor that saves a document through three collaborators. Every call between objects is recorded in `trace`.
#pragma once
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

inline std::vector<std::string> trace;
inline void call(const char* from, const char* to, const char* what) { trace.push_back(std::string(from) + "->" + to + ": " + what); }

class Document {
public:
    explicit Document(std::string text) : text_(std::move(text)) {}
    std::string serialise() const { return text_; }
private:
    std::string text_;
};
class Storage {
public:
    void write(const std::string& name, const std::string& text) { files_[name] = text; }
    bool has(const std::string& name) const { return files_.count(name) > 0; }
private:
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
    void save(const std::string& name) {
        call("Editor", "Document", "serialise");
        std::string text = doc_.serialise();
        call("Editor", "Storage", "write");
        storage_.write(name, text);
        call("Editor", "Notifier", "saved");
        notifier_.saved(name);
    }
private:
    Document& doc_;
    Storage& storage_;
    Notifier& notifier_;
};
