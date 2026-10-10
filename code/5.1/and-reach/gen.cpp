#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 9), q = randInt(1, 9);
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) printf("%d%c", randInt(0, 15), i + 1 < n ? ' ' : '\n');
    for (int i = 0; i < q; i++) printf("%d %d\n", randInt(1, n), randInt(0, 16));
}
