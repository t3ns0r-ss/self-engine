#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int len = randInt(1, 6);
    string s;
    for (int i = 0; i < len; i++) s += (char)('a' + randInt(0, 25));
    if (randInt(0, 3) == 0) s = string(len, 'z');
    int t = randInt(1, 12);
    cout << s << "\n" << t << "\n";
    int top = randInt(1, 25);
    for (int i = 0; i < 26; i++) cout << randInt(1, top) << (i < 25 ? " " : "\n");
}
