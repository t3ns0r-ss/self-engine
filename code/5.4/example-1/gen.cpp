#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 12), m = randInt(1, 10);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) printf("%d%c", randInt(1, 5), i + 1 < n ? ' ' : '\n');
    while (m--) {
        int l = randInt(1, n), r = randInt(l, n);
        printf("%d %d\n", l, r);
    }
}
