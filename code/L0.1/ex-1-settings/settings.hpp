// Worked example 1: display preferences with no rule between the fields. Any combination is valid,
// so there is nothing for a class to protect: a plain struct is the right size.
#pragma once
#include <string>
#include <type_traits>

struct Settings {
    bool dark_mode = false;
    int font_size = 14;
    std::string language = "en";
    bool show_tips = true;
};

inline std::string describe(const Settings& s) {
    return std::string(s.dark_mode ? "dark" : "light") + "/" + std::to_string(s.font_size) + "/" + s.language + (s.show_tips ? "/tips" : "");
}

static_assert(std::is_aggregate_v<Settings>, "a plain bag of fields: no constructor, no rules");
