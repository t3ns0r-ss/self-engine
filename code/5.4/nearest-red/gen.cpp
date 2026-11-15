#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 10), q = randInt(1, 14);
    printf("%d %d\n", n, q);
    for (int v = 2; v <= n; v++) printf("%d %d\n", randInt(1, v - 1), v);
    for (int i = 0; i < q; i++) printf("%d %d\n", randInt(1, 2), randInt(1, n));
}
