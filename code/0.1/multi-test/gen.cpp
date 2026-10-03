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
    int t = randInt(1, 4);
    cout << t << "\n";
    for (int test = 0; test < t; test++) {
        int n = randInt(1, 7);
        bool big = randInt(0, 2) == 0;  // values near 10^9, so x * n passes int
        int maxV = randInt(1, 6);
        cout << n << "\n";
        for (int i = 0; i < n; i++) {
            int x = big ? randInt(999999990, 1000000000) : randInt(1, maxV);
            cout << x << (i + 1 < n ? ' ' : '\n');
        }
    }
}
