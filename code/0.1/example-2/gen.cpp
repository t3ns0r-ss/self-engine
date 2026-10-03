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
    int t = randInt(1, 5);
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        int n = randInt(1, 6);
        cout << n << "\n";
        for (int j = 0; j < n; j++) cout << (randInt(0, 3) ? randInt(1, 20) : randInt(999999990, 1000000000)) << (j + 1 < n ? ' ' : '\n');
    }
}
