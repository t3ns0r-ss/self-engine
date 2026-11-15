#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int q = randInt(1, 14);
    printf("%d\n", q);
    for (int i = 0; i < q; i++) {
        if (randInt(0, 2) == 0) printf("2 %d\n", randInt(0, 63));
        else printf("1 %d %d\n", randInt(-8, 8), randInt(-100, 100));
    }
}
