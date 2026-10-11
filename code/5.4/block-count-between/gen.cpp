#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 12), q = randInt(1, 12);
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) printf("%d%c", randInt(1, 9), i + 1 < n ? ' ' : '\n');
    while (q--) {
        if (randInt(0, 1)) printf("1 %d %d\n", randInt(1, n), randInt(1, 9));
        else {
            int l = randInt(1, n), r = randInt(l, n), lo = randInt(1, 9), hi = randInt(lo, 9);
            printf("2 %d %d %d %d\n", l, r, lo, hi);
        }
    }
}
