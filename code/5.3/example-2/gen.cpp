#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 8), m = randInt(1, 8);
    printf("%d\n", n);
    for (int i = 0; i < n; i++) printf("%d%c", randInt(-5, 20), i + 1 < n ? ' ' : '\n');
    printf("%d\n", m);
    while (m--) {
        int l = randInt(0, n - 1), r = randInt(0, n - 1);
        if (randInt(0, 1)) printf("%d %d %d\n", l, r, randInt(-6, 6));
        else printf("%d %d\n", l, r);
    }
}
