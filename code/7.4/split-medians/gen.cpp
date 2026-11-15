#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 9), k = randInt(1, n);
    printf("%d %d\n", n, k);
    int x = randInt(0, 3);
    for (int i = 0; i < n; i++) {
        printf("%d ", x);
        x += randInt(1, 7);
    }
    printf("\n");
}
