#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) {
        return (int)(rng() % (unsigned)(hi - lo + 1)) + lo;
    };
    int n = randInt(1, 9);
    string s;
    if (randInt(0, 2) == 0) {  // sometimes force the alternating pattern lower, UPPER, lower, ...
        for (int i = 0; i < n; i++) s += (i % 2 == 0) ? "ab"[randInt(0, 1)] : "AB"[randInt(0, 1)];
    } else {
        for (int i = 0; i < n; i++) s += "abAB"[randInt(0, 3)];
    }
    cout << s << "\n";
}
