// A Document owns its paragraphs (composition) and refers to fonts kept in a FontTable that outlives it (aggregation).
#pragma once
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

struct Font {
    std::string name;
    int size;
};

class FontTable {
public:
    void add(const std::string& name, int size) { fonts_[name] = Font{name, size}; }
    const Font* find(const std::string& name) const {
        auto it = fonts_.find(name);
        return it == fonts_.end() ? nullptr : &it->second;   // std::map nodes keep their address as the map grows
    }
private:
    std::map<std::string, Font> fonts_;
};

struct Paragraph {
    std::string text;
    const Font* font;                                         // aggregation: the paragraph does not own its font
};

class Document {
public:
    explicit Document(const FontTable& fonts) : fonts_(&fonts) {}
    void add_paragraph(const std::string& text, const std::string& font_name) {
        const Font* f = fonts_->find(font_name);
        if (!f) throw std::out_of_range("unknown font: " + font_name);
        paragraphs_.push_back(Paragraph{text, f});            // composition: the paragraph is stored by value
    }
    std::size_t paragraph_count() const { return paragraphs_.size(); }
    const Paragraph& paragraph(std::size_t i) const { return paragraphs_.at(i); }
    std::string render() const {
        std::string out;
        for (const Paragraph& p : paragraphs_)
            out += "[" + p.font->name + " " + std::to_string(p.font->size) + "] " + p.text + "\n";
        return out;
    }
private:
    const FontTable* fonts_;
    std::vector<Paragraph> paragraphs_;
};
