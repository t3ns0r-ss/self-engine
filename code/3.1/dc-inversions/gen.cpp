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
    int n = randInt(0, 30);
    int mode = randInt(1, 4);
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        int v;
        if (mode == 1) v = randInt(0, 3);  // many equal values
        else if (mode == 2) v = randInt(-1000000000, 1000000000);
        else if (mode == 3) v = n - i;  // reversed
        else v = i / 2;  // sorted with ties
        cout << v << (i + 1 < n ? ' ' : '\n');
    }
    if (n == 0) cout << "\n";
}
