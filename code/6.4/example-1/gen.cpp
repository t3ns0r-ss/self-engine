#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int sigma = randInt(1, 3), n = randInt(1, 12);
    auto word = [&](int len) {
        string w(len, 'a');
        for (char& c : w) c = 'a' + randInt(0, sigma - 1);
        return w;
    };
    string s = word(n);
    int n2 = s.size();
    set<string> all;
    for (int i = 0; i < n2; i++)
        for (int len = 1; i + len <= n2; len++) all.insert(s.substr(i, len));
    printf("%s\n%d\n", s.c_str(), randInt(1, (int)all.size()));
}
