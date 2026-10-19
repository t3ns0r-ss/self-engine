#include <string>

class Settings {                       // OVER-ENGINEERED: five unrelated fields, any combination valid
public:
    bool dark_mode() const { return dark_mode_; }
    void set_dark_mode(bool v) { dark_mode_ = v; }
    int font_size() const { return font_size_; }
    void set_font_size(int v) { font_size_ = v; }
    const std::string& language() const { return language_; }
    void set_language(std::string v) { language_ = std::move(v); }
    bool show_tips() const { return show_tips_; }
    void set_show_tips(bool v) { show_tips_ = v; }
    int sidebar_width() const { return sidebar_width_; }
    void set_sidebar_width(int v) { sidebar_width_ = v; }
private:
    bool dark_mode_ = false;
    int font_size_ = 14;
    std::string language_ = "en";
    bool show_tips_ = true;
    int sidebar_width_ = 250;
};

int main() { Settings s; s.set_font_size(16); return s.font_size() - 16; }
