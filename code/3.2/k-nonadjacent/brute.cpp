// Brute force: every bitmask with k bits and no two adjacent bits (Theorem 0.5.2).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    bool found = false;
    long long best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (__builtin_popcount(mask) != k || (mask & (mask >> 1))) continue;
        long long s = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) s += a[i];
        if (!found || s > best) best = s;
        found = true;
    }
    if (!found) cout << "impossible\n";
    else cout << best << "\n";
}
