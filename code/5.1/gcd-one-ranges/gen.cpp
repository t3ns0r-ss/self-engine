#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 9), top = rng() % 4 == 0 ? 1 : randInt(2, 30);
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        int v = randInt(1, top);
        if (rng() % 3 == 0) v = 6 * randInt(1, 4) * (rng() % 2 ? 5 : 1);  // many shared factors
        printf("%d%c", v, i + 1 < n ? ' ' : '\n');
    }
}
