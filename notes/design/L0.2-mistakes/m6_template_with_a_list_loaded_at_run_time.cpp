#include <cstdio>
#include <string>
#include <vector>

struct Upper   { std::string encode(const std::string& s) const { return s + "U"; } };
struct Reverse { std::string encode(const std::string& s) const { return s + "R"; } };

template <class C>
std::string run_all(const std::vector<C>& codecs, std::string text) {
    for (const C& c : codecs) text = c.encode(text);
    return text;
}

int main() {
    std::vector<Upper> a;                          // one vector holds one type
    a.push_back(Upper{});
    a.push_back(Reverse{});                        // MISTAKE: the list chosen at run time needs two types in one vector
    std::printf("%s\n", run_all(a, "x").c_str());
}
