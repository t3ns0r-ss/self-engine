#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 5), q = randInt(1, 8);
    printf("%d %d\n", n, q);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) putchar('0' + (int)(rng() % 2));
        putchar('\n');
    }
    for (int i = 0; i < q; i++) {
        if (rng() % 2) printf("1 %d %d\n", randInt(1, n), randInt(1, n));
        else {
            int r1 = randInt(1, n), c1 = randInt(1, n);
            printf("2 %d %d %d %d\n", r1, c1, randInt(r1, n), randInt(c1, n));
        }
    }
}
