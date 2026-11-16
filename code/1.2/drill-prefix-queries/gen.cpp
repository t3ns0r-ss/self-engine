#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](long long lo, long long hi) {
        return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo;
    };
    int n = randInt(1, 8), q = randInt(1, 6);
    cout << n << " " << q << "\n";
    int big = randInt(0, 2) == 0 ? 1000000000 : 9;
    for (int i = 0; i < n; i++) cout << randInt(-big, big) << (i + 1 < n ? ' ' : '\n');
    while (q--) {
        int l = randInt(1, n), r = randInt(1, n);
        if (l > r) swap(l, r);
        cout << l << " " << r << "\n";
    }
}
