#include <bits/stdc++.h>
using namespace std;

// For each town, relax all roads n times in both directions (the cheapest route has at most n - 1 roads).
int main() {
    int n, m;
    cin >> n >> m;
    vector<array<long long, 3>> e(m);
    for (auto& x : e) cin >> x[0] >> x[1] >> x[2];
    const long long INF = LLONG_MAX / 4;
    int bestTown = -1;
    long long bestTotal = 0;
    for (int s = 1; s <= n; s++) {
        vector<long long> d(n + 1, INF);
        d[s] = 0;
        for (int r = 0; r < n; r++)
            for (auto& x : e) {
                if (d[x[0]] < INF) d[x[1]] = min(d[x[1]], d[x[0]] + x[2]);
                if (d[x[1]] < INF) d[x[0]] = min(d[x[0]], d[x[1]] + x[2]);
            }
        long long total = 0;
        bool all = true;
        for (int v = 1; v <= n; v++) {
            if (d[v] == INF) all = false;
            else total += d[v];
        }
        if (all && (bestTown == -1 || total < bestTotal)) bestTown = s, bestTotal = total;
    }
    if (bestTown == -1) cout << -1 << "\n";
    else cout << bestTown << " " << bestTotal << "\n";
}
