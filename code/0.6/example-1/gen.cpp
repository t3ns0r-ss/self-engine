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
    int n = randInt(1, 8), hi = randInt(0, 1) ? 10 : 1000000000;
    vector<int> a(n);
    for (auto& v : a) v = randInt(1, hi);
    int x = randInt(1, 3) == 1 || n < 2 ? randInt(1, hi) : a[randInt(0, n - 1)] + a[randInt(0, n - 1)];
    if (x > 1000000000) x = 1000000000;
    cout << n << " " << x << "\n";
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');
}
