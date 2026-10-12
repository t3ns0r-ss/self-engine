#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<array<long long, 3>> edges(m);
    for (auto& e : edges) cin >> e[0] >> e[1] >> e[2];
    const long long INF = 4e18;
    vector<long long> best(n + 1, INF);  // best[v] = the least weight of a walk of the current length from the node 1 to v
    best[1] = 0;
    for (long long step = 0; step < k; step++) {
        vector<long long> next(n + 1, INF);
        for (auto& e : edges)
            if (best[e[0]] < INF) next[e[1]] = min(next[e[1]], best[e[0]] + e[2]);
        best = next;
    }
    cout << (best[n] < INF ? best[n] : -1) << "\n";
}
