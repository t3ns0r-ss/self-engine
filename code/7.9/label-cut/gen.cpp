#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 8), m = n == 1 ? 0 : randInt(0, 12), top = randInt(1, 9);
    cout << n << " " << m << "\n";
    for (int i = 0; i < n; i++) cout << randInt(0, top) << " " << randInt(0, top) << "\n";
    for (int k = 0; k < m; k++) {
        int i = randInt(1, n), j = randInt(1, n);
        while (j == i) j = randInt(1, n);
        cout << i << " " << j << " " << randInt(0, top) << "\n";
    }
}
