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
    vector<int> a(n);
    for (auto& x : a) x = randInt(1, maxV);
    if (randInt(0, 4) == 0) fill(a.begin(), a.end(), a[0]);  // all equal
    int total = accumulate(a.begin(), a.end(), 0);
    int K = randInt(0, total + 2);
    if (randInt(0, 4) == 0) K = a[randInt(0, n - 1)];  // boundary: exactly one element's value
    cout << n << " " << K << "\n";
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');
}
