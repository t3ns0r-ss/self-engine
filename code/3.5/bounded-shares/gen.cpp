#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) {
        return (int)(rng() % (unsigned)(hi - lo + 1)) + lo;
    };
    int n = randInt(1, 6), k = randInt(0, 12);
    cout << n << " " << k << "\n";
    for (int i = 0; i < n; i++) {
        int a = randInt(0, k), b = randInt(0, k);
        if (a > b) swap(a, b);
        if (randInt(0, 2) == 0) a = 0;
        cout << a << " " << b << "\n";
    }
}
