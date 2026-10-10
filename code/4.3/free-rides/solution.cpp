/*
Problem: coupons for roads.
Input: n m k, then m lines "a b w": a two-way road of length w (1 <= w <= 10^9) between towns a and b (roads may repeat).
You may drive up to k roads of your trip for free.
Output: the least cost of a trip from town 1 to town n, or -1 if town n cannot be reached.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.3.5. Least cost from 1 to n when up to k edges are free. The state is (vertex, free edges used so far).
long long cheapestWithFreeEdges(const vector<vector<pair<int, long long>>>& adj, int k) {
    int n = adj.size() - 1;
    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> dist(n + 1, vector<long long>(k + 1, INF));
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> heap;  // (distance, vertex, used)
    dist[1][0] = 0;
    heap.push({0, 1, 0});
    while (!heap.empty()) {
        auto [d, u, used] = heap.top();
        heap.pop();
        if (d > dist[u][used]) continue;
        for (auto [v, w] : adj[u]) {
            if (d + w < dist[v][used]) dist[v][used] = d + w, heap.push({d + w, v, used});
            if (used < k && d < dist[v][used + 1]) dist[v][used + 1] = d, heap.push({d, v, used + 1});
        }
    }
    long long best = INF;
    for (int used = 0; used <= k; used++) best = min(best, dist[n][used]);
    return best == INF ? -1 : best;
}
// snippet:end

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }
    cout << cheapestWithFreeEdges(adj, k) << "\n";
}
