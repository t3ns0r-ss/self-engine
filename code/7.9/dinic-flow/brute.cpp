#include <bits/stdc++.h>
using namespace std;

// Brute force: the smallest capacity of a cut, over all sets of vertices that contain s and not t (max-flow = min-cut).
int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<array<long long, 3>> edges(m);
    for (auto& e : edges) cin >> e[0] >> e[1] >> e[2];
    s--; t--;
    long long best = LLONG_MAX;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (!(mask >> s & 1) || (mask >> t & 1)) continue;
        long long total = 0;
        for (auto& e : edges)
            if ((mask >> (e[0] - 1) & 1) && !(mask >> (e[1] - 1) & 1)) total += e[2];
        best = min(best, total);
    }
    cout << best << "\n";
}
