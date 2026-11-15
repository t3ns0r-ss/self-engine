#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> seg(n);
    for (auto& [l, r] : seg) cin >> l >> r;
    int best = n;
    for (int mask = 0; mask < (1 << n); mask++) {  // the set of segments that stay
        bool ok = true;
        for (int p = 1; p <= 12 && ok; p++) {
            int cover = 0;
            for (int i = 0; i < n; i++)
                if (mask >> i & 1) cover += seg[i].first <= p && p <= seg[i].second;
            ok &= cover <= k;
        }
        if (ok) best = min(best, n - __builtin_popcount(mask));
    }
    cout << best << "\n";
}
