#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(2, 8);
    printf("%d\n", n);
    for (int who = 0; who < 2; who++) {
        int k = randInt(1, 3);
        printf("%d", k);
        for (int i = 0; i < k; i++) printf(" %d", randInt(1, n - 1));
        printf("\n");
    }
}
