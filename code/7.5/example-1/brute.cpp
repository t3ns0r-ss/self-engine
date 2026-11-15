#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> c(n);
    for (auto& [d, l] : c) cin >> d >> l;
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return c[a].second < c[b].second; });
    int best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long time = 0;
        bool ok = true;
        for (int i : order)
            if (mask >> i & 1) time += c[i].first, ok &= time <= c[i].second;
        if (ok) best = max(best, __builtin_popcount(mask));
    }
    cout << best << "\n";
}
