#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(2, 8), top = rng() % 4 == 0 ? 1 : randInt(1, 40);
    printf("%d\n", n);
    for (int i = 0; i < n; i++) printf("%d%c", randInt(0, top), i + 1 < n ? ' ' : '\n');
}
