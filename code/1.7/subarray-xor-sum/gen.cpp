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
    int kind = randInt(0, 3);
    int hi = kind == 0 ? 1 : (kind == 1 ? 7 : (kind == 2 ? 1000 : (1 << 30) - 1));
    cout << n << "\n";
    int same = randInt(0, hi);
    for (int i = 0; i < n; i++) cout << (randInt(0, 5) == 0 ? same : randInt(0, hi)) << (i + 1 < n ? ' ' : '\n');
}
