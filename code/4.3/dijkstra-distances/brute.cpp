#include <bits/stdc++.h>
using namespace std;

// Relax every flight n times (the cheapest route has at most n - 1 flights).
int main() {
    int n, m;
    cin >> n >> m;
    vector<array<long long, 3>> e(m);
    for (auto& x : e) cin >> x[0] >> x[1] >> x[2];
    const long long INF = LLONG_MAX / 4;
    vector<long long> d(n + 1, INF);
    d[1] = 0;
    for (int r = 0; r < n; r++)
        for (auto& x : e)
            if (d[x[0]] < INF) d[x[1]] = min(d[x[1]], d[x[0]] + x[2]);
    for (int v = 1; v <= n; v++) cout << (d[v] == INF ? -1 : d[v]) << (v < n ? " " : "\n");
}
