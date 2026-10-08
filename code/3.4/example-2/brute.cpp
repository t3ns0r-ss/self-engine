// Brute force: choose which elements to keep on each side (same number), as two bitmasks.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    int best = INT_MAX;
    for (int ma = 0; ma < (1 << n); ma++)
        for (int mb = 0; mb < (1 << m); mb++) {
            if (__builtin_popcount(ma) != __builtin_popcount(mb)) continue;
            vector<long long> x, y;
            for (int i = 0; i < n; i++)
                if ((ma >> i) & 1) x.push_back(a[i]);
            for (int j = 0; j < m; j++)
                if ((mb >> j) & 1) y.push_back(b[j]);
            int cost = (n - (int)x.size()) + (m - (int)y.size());
            for (size_t k = 0; k < x.size(); k++) cost += (x[k] != y[k]);
            best = min(best, cost);
        }
    cout << best << "\n";
}
