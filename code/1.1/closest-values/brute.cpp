// Tries every pair, and every subset of exactly k elements (bitmask, n small).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long minDiff = LLONG_MAX, minSpread = LLONG_MAX;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) minDiff = min(minDiff, llabs(a[i] - a[j]));
    for (int mask = 0; mask < (1 << n); mask++) {
        if (__builtin_popcount(mask) != k) continue;
        long long lo = LLONG_MAX, hi = LLONG_MIN;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) lo = min(lo, a[i]), hi = max(hi, a[i]);
        minSpread = min(minSpread, hi - lo);
    }
    cout << minDiff << " " << minSpread << "\n";
}
