#include <bits/stdc++.h>
using namespace std;

// List all links, try every set of n - 1 of them and keep the cheapest one that connects all points (n <= 6).
int main() {
    int n;
    cin >> n;
    vector<pair<long long, long long>> p(n);
    for (auto& q : p) cin >> q.first >> q.second;
    vector<array<long long, 3>> links;
    for (int a = 0; a < n; a++)
        for (int b = a + 1; b < n; b++) links.push_back({a, b, llabs(p[a].first - p[b].first) + llabs(p[a].second - p[b].second)});
    int m = links.size();
    long long best = LLONG_MAX;
    for (int mask = 0; mask < (1 << m); mask++) {
        if (__builtin_popcount(mask) != n - 1) continue;
        vector<int> label(n);
        iota(label.begin(), label.end(), 0);
        long long total = 0;
        for (int i = 0; i < m; i++)
            if (mask >> i & 1) {
                int x = label[links[i][0]], y = label[links[i][1]];
                for (int& l : label) if (l == y) l = x;
                total += links[i][2];
            }
        if (set<int>(label.begin(), label.end()).size() == 1) best = min(best, total);
    }
    cout << (n == 1 ? 0 : best) << "\n";
}
