#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int t = randInt(1, 3);
    printf("%d\n", t);
    for (int i = 0; i < t; i++) printf("%d\n", randInt(1, 16));
}
