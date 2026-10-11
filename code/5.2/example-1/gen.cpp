#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int tests = randInt(1, 3);
    printf("%d\n", tests);
    while (tests--) {
        int n = randInt(1, 9);
        printf("%d\n", n);
        for (int i = 0; i < n; i++) printf("%d%c", randInt(1, n), i + 1 < n ? ' ' : '\n');
    }
}
