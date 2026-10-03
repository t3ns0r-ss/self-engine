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
    int n = randInt(1, 8);
    int maxV = randInt(1, 10);
    vector<int> a(n);  // values before scaling
    for (auto& x : a) x = randInt(1, maxV);
    if (randInt(0, 4) == 0) fill(a.begin(), a.end(), a[0]);  // all equal
    long long scale = randInt(0, 4) == 0 ? 100000000 : 1;    // sometimes values up to 10^9, sums past int
    long long total = 0;
    for (int x : a) total += x * scale;
    long long K = (long long)(rng() % (unsigned long long)(total + 3));
    if (randInt(0, 4) == 0) K = a[randInt(0, n - 1)] * scale;  // boundary: exactly one element's value
    cout << n << " " << K << "\n";
    for (int i = 0; i < n; i++) cout << a[i] * scale << (i + 1 < n ? ' ' : '\n');
}
