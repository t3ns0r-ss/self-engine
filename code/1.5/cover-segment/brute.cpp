// Tries every subset of segments and checks that their union covers [0, L].
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long L;
    cin >> n >> L;
    vector<pair<long long, long long>> seg(n);
    for (auto& [l, r] : seg) cin >> l >> r;
    sort(seg.begin(), seg.end());
    int best = INT_MAX;
    for (int mask = 1; mask < (1 << n); mask++) {
        long long reach = 0;
        bool gap = false;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) {
                if (seg[i].first > reach) gap = true;
                reach = max(reach, seg[i].second);
            }
        if (!gap && reach >= L) best = min(best, __builtin_popcount(mask));
    }
    cout << (best == INT_MAX ? -1 : best) << "\n";
}
