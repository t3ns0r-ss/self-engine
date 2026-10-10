/*
Problem: cheapest tickets.
Input: n m, then m lines "a b w": a one-way flight from city a to city b costs w (0 <= w <= 10^9; flights may repeat).
Output: n numbers: the cheapest cost from city 1 to cities 1..n, or -1 for a city that cannot be reached.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.3.1. Cheapest cost from s to every vertex, -1 when unreachable; edges are {to, weight} with weight >= 0.
vector<long long> cheapestCosts(const vector<vector<pair<int, long long>>>& adj, int s) {
    const long long INF = LLONG_MAX / 4;
    vector<long long> dist(adj.size(), INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> heap;  // (distance, vertex), smallest first
    dist[s] = 0;
    heap.push({0, s});
    while (!heap.empty()) {
        auto [d, u] = heap.top();
        heap.pop();
        if (d > dist[u]) continue;  // an old entry: a shorter one was already taken
        for (auto [v, w] : adj[u])
            if (d + w < dist[v]) dist[v] = d + w, heap.push({dist[v], v});
    }
    for (auto& d : dist) if (d == INF) d = -1;
    return dist;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
    }
    auto dist = cheapestCosts(adj, 1);
    for (int v = 1; v <= n; v++) cout << dist[v] << (v < n ? " " : "\n");
}
