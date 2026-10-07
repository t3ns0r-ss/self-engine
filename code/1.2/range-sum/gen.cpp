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
    int n = randInt(1, 10), q = randInt(1, 10), hi = randInt(0, 1) ? 5 : 1000000000;
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; i++) cout << randInt(-hi, hi) << (i + 1 < n ? ' ' : '\n');
    for (int i = 0; i < q; i++) {
        int l = randInt(1, n), r = randInt(1, n);
        cout << min(l, r) << " " << max(l, r) << "\n";
    }
}
