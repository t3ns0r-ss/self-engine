#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int len = randInt(1, 8), letters = randInt(1, 4);
    string s;
    for (int i = 0; i < len; i++) s += (char)('a' + (randInt(0, 2) == 0 ? 0 : randInt(0, letters - 1)));
    cout << s << "\n";
}
