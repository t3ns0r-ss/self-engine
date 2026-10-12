#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int sigma = randInt(1, 3);
    auto word = [&](int len) {
        string w(len, 'a');
        for (char& c : w) c = 'a' + randInt(0, sigma - 1);
        return w;
    };
    string s = word(randInt(1, 14)), t = word(randInt(1, 4));
    printf("%s\n%s\n", s.c_str(), t.c_str());
}
