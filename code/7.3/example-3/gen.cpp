#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 9), m = randInt(1, 9);
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; i++) {
        int l = randInt(1, n), r = randInt(1, n);
        if (l > r) swap(l, r);
        printf("%d %d %d\n", l, r, randInt(-5, 10));
    }
}
