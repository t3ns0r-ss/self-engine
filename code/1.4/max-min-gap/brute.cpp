// Tries every subset of exactly m positions (bitmask) and keeps the best smallest gap.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> p(n);
    for (auto& x : p) cin >> x;
    sort(p.begin(), p.end());
    long long best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (__builtin_popcount(mask) != m) continue;
        long long gap = LLONG_MAX, last = -1;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) {
                if (last >= 0) gap = min(gap, p[i] - p[last]);
                last = i;
            }
        best = max(best, gap);
    }
    cout << best << "\n";
}
