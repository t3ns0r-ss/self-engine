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
    int n = randInt(1, 9);
    int k = randInt(1, n);
    if (randInt(0, 4) == 0) k = n;  // boundary: one window only
    int maxV = randInt(1, 6);
    vector<int> a(n);
    for (auto& x : a) x = randInt(1, maxV);
    cout << n << " " << k << "\n";
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');
}
