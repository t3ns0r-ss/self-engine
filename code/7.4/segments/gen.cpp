#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 8), k = randInt(1, 3);
    printf("%d %d\n", n, k);
    for (int i = 0; i < n; i++) {
        int l = randInt(1, 10), r = l + randInt(0, 2);
        printf("%d %d\n", l, r);
    }
}
