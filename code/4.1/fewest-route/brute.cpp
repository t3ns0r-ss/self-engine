#include <bits/stdc++.h>
using namespace std;

// Repeated relaxation: dist[b] = min(dist[b], dist[a] + 1) over all edges, n times.
int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<pair<int, int>> edges(m);
    for (auto& e : edges) cin >> e.first >> e.second;
    const int INF = 1e9;
    vector<int> dist(n + 1, INF);
    dist[s] = 0;
    for (int round = 0; round < n; round++)
        for (auto [a, b] : edges) {
            if (dist[a] + 1 < dist[b]) dist[b] = dist[a] + 1;
            if (dist[b] + 1 < dist[a]) dist[a] = dist[b] + 1;
        }
    cout << (dist[t] >= INF ? -1 : dist[t]) << "\n";
}
