#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 9), q = randInt(1, 12);
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) printf("%d%c", randInt(-5, 20), i + 1 < n ? ' ' : '\n');
    while (q--) {
        int l = randInt(1, n), r = randInt(l, n);
        if (randInt(0, 1)) printf("1 %d %d %d\n", l, r, randInt(-9, 9));
        else printf("2 %d %d\n", l, r);
    }
}
