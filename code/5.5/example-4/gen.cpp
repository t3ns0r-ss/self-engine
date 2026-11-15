#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 14), q = randInt(1, 12);
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) printf("%d%c", randInt(1, 4), i + 1 < n ? ' ' : '\n');
    while (q--) {
        if (randInt(0, 1)) {
            int l = randInt(1, n), r = randInt(l, n);
            printf("1 %d %d %d\n", l, r, randInt(1, 3));
        } else printf("2 %d\n", randInt(1, 8));
    }
}
