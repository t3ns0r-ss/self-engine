// Brute force: build every sum part by part; for t = 1 the parts are chosen in non-decreasing
// order so that each multiset is built once.
#include <bits/stdc++.h>
using namespace std;

int t, n, d;
vector<int> parts;

long long build(int left, int minPart, bool hasBig) {
    if (left == 0) return hasBig ? 1 : 0;
    long long ways = 0;
    for (int p : parts)
        if (p <= left && (t == 0 || p >= minPart)) ways += build(left - p, p, hasBig || p >= d);
    return ways;
}

int main() {
    int m;
    cin >> t >> n >> d >> m;
    parts.resize(m);
    for (int& p : parts) cin >> p;
    cout << build(n, 0, false) % 1'000'000'007 << "\n";
}
