#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 9), C = randInt(1, 30);
    printf("%d %d\n", n, C);
    int h = randInt(1, 3);
    for (int i = 0; i < n; i++) {
        printf("%d ", h);
        h += randInt(1, 6);
    }
    printf("\n");
}
