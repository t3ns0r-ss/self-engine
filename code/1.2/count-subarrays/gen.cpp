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
    int n = randInt(1, 10), hi = randInt(0, 2) ? 3 : 1000000000;
    long long K = randInt(-6, 6), m = randInt(1, 5);
    if (hi > 3) K = 0;  // with large values, mostly the empty-sum-like case K = 0 has hits
    cout << n << " " << K << " " << m << "\n";
    for (int i = 0; i < n; i++) cout << randInt(-hi, hi) << (i + 1 < n ? ' ' : '\n');
}
