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
    int n = randInt(1, 12), m = randInt(1, min(n, 4));
    string s, t;
    for (int i = 0; i < n; i++) s += "ab"[randInt(0, 1)];  // two letters make overlaps likely
    for (int i = 0; i < m; i++) t += "ab"[randInt(0, 1)];
    cout << s << "\n" << t << "\n";
}
