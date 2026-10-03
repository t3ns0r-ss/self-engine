#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randLL = [&](long long lo, long long hi) {
        return lo + (long long)(rng() % (unsigned long long)(hi - lo + 1));
    };
    int n = randLL(1, 8);
    int mode = randLL(0, 3);
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        long long x;
        if (mode == 0) x = randLL(-10, 10);                         // small
        else if (mode == 1) x = randLL(900000000, 1000000000);      // large positive: sum passes int
        else if (mode == 2) x = -randLL(900000000, 1000000000);     // large negative
        else x = randLL(-1000000000, 1000000000);
        cout << x << (i + 1 < n ? ' ' : '\n');
    }
}
