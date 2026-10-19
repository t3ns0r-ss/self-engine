#include <string>

struct Settings {                      // the same five fields, no rule between them
    bool dark_mode = false;
    int font_size = 14;
    std::string language = "en";
    bool show_tips = true;
    int sidebar_width = 250;
};

int main() { Settings s; s.font_size = 16; return s.font_size - 16; }
