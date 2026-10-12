#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int r = randInt(1, 4), c = randInt(1, 4), top = randInt(1, 9);
    printf("%d %d\n", r, c);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) printf("%d%c", randInt(0, top), j + 1 < c ? ' ' : '\n');
}
