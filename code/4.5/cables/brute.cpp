#include <bits/stdc++.h>
using namespace std;

// Try every set of n - 1 cables and keep the cheapest one that connects all computers.
int main() {
    int n, m;
    cin >> n >> m;
    vector<array<long long, 3>> cables(m);
    for (auto& c : cables) cin >> c[0] >> c[1] >> c[2];
    long long best = -1;
    for (int mask = 0; mask < (1 << m); mask++) {
        if (__builtin_popcount(mask) != n - 1) continue;
        vector<int> label(n + 1);
        iota(label.begin(), label.end(), 0);
        long long total = 0;
        for (int i = 0; i < m; i++)
            if (mask >> i & 1) {
                int x = label[cables[i][0]], y = label[cables[i][1]];
                for (int& l : label) if (l == y) l = x;
                total += cables[i][2];
            }
        set<int> groups(label.begin() + 1, label.end());
        if (groups.size() == 1 && (best == -1 || total < best)) best = total;
    }
    if (best < 0) cout << "IMPOSSIBLE\n";
    else cout << best << "\n";
}
