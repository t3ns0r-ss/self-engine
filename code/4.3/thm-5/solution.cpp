#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.3.5. Cheapest route from 1 to n when ONE edge may be used for free. The state is (vertex, free edge already used),
// and Dijkstra runs on these pairs; edges are {to, weight}.
long long cheapestWithOneFreeEdge(const vector<vector<pair<int, long long>>>& adj) {
    int n = adj.size() - 1;
    const long long INF = LLONG_MAX / 4;
    vector<array<long long, 2>> dist(n + 1, {INF, INF});
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> heap;  // (distance, vertex, used)
    dist[1][0] = 0;
    heap.push({0, 1, 0});
    while (!heap.empty()) {
        auto [d, u, used] = heap.top();
        heap.pop();
        if (d > dist[u][used]) continue;
        for (auto [v, w] : adj[u]) {
            if (d + w < dist[v][used]) dist[v][used] = d + w, heap.push({d + w, v, used});  // pay for the edge
            if (!used && d < dist[v][1]) dist[v][1] = d, heap.push({d, v, 1});              // or use the free edge now
        }
    }
    return min(dist[n][0], dist[n][1]);
}
// snippet:end

int main() {
    auto run = [&](int n, vector<array<long long, 3>> edges) {
        vector<vector<pair<int, long long>>> adj(n + 1);
        for (auto [a, b, w] : edges) {
            adj[a].push_back({(int)b, w});
            adj[b].push_back({(int)a, w});
        }
        return cheapestWithOneFreeEdge(adj);
    };
    cout << "path 1-2 (4), 2-3 (6): " << run(3, {{1, 2, 4}, {2, 3, 6}}) << "\n";
    cout << "edges 1-2 (5), 2-4 (5), 1-3 (2), 3-4 (9): " << run(4, {{1, 2, 5}, {2, 4, 5}, {1, 3, 2}, {3, 4, 9}}) << "\n";
    cout << "one vertex: " << run(1, {}) << "\n";
    // Check against: free each edge in turn, run a plain shortest-path search, take the best (also without any free edge).
    mt19937 rng(31337);
    const long long INF = LLONG_MAX / 4;
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 6 + 1;
        vector<array<long long, 3>> edges;
        int count = rng() % 10;
        for (int i = 0; i < count && n > 1; i++) {
            int a = rng() % n + 1, b = rng() % n + 1;
            if (a != b) edges.push_back({a, b, (long long)(rng() % 10)});
        }
        auto plain = [&](int freeEdge) {
            vector<long long> best(n + 1, INF);
            best[1] = 0;
            for (int round = 0; round < n; round++)
                for (size_t i = 0; i < edges.size(); i++) {
                    auto [a, b, w] = edges[i];
                    if ((int)i == freeEdge) w = 0;
                    if (best[a] < INF && best[a] + w < best[b]) best[b] = best[a] + w;
                    if (best[b] < INF && best[b] + w < best[a]) best[a] = best[b] + w;
                }
            return best[n];
        };
        long long expected = plain(-1);
        for (size_t i = 0; i < edges.size(); i++) expected = min(expected, plain(i));
        if (run(n, edges) != expected) return 1;
    }
}
