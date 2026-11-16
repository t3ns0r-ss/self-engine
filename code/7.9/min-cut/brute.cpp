#include <bits/stdc++.h>
using namespace std;

// Brute force: try every set of vertices that contains s and not t; keep the smallest capacity, and among equal ones the fewest vertices.
int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<array<long long, 3>> edges(m);
    for (auto& e : edges) cin >> e[0] >> e[1] >> e[2];
    s--; t--;
    long long bestCap = LLONG_MAX;
    int bestSize = 0, bestCrossing = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (!(mask >> s & 1) || (mask >> t & 1)) continue;
        long long total = 0;
        int crossing = 0;
        for (auto& e : edges)
            if ((mask >> (e[0] - 1) & 1) && !(mask >> (e[1] - 1) & 1)) { total += e[2]; crossing++; }
        int size = __builtin_popcount(mask);
        if (total < bestCap || (total == bestCap && size < bestSize)) { bestCap = total; bestSize = size; bestCrossing = crossing; }
    }
    cout << bestCap << " " << bestSize << " " << bestCrossing << "\n";
}
