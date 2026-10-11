#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 8), q = randInt(1, 10);
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) printf("%d%c", randInt(-5, 9), i + 1 < n ? ' ' : '\n');
    for (int i = 0; i < q; i++) {
        if (rng() % 2) {
            int l = randInt(1, n);
            printf("1 %d %d %d\n", l, randInt(l, n), randInt(-9, 9));
        } else printf("2 %d\n", randInt(1, n));
    }
}
