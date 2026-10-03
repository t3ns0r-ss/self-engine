#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937_64 rng(atoi(argv[1]));
    auto randLL = [&](long long lo, long long hi) {
        return lo + (long long)(rng() % (unsigned long long)(hi - lo + 1));
    };
    int n = randLL(1, 6);
    const long long E18 = 1000000000000000000LL;
    vector<long long> pool = {0, 1, 2, 3, 10, 1000, 999999999, 1000000000, 1000000001, 999999999999999999LL, E18, E18 / 2, E18 / 3};
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        long long x;
        int mode = randLL(0, 9);
        if (mode < 6) x = pool[randLL(0, pool.size() - 1)];
        else if (mode < 8) x = randLL(1, 2000000);
        else x = randLL(0, E18);
        if (x == 0 && randLL(0, 2) != 0) x = 1;  // zeros sometimes, not always
        cout << x << (i + 1 < n ? ' ' : '\n');
    }
}
