#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.3.1. Shortest distance from s to every vertex when no weight is negative (INF if unreachable), and for each vertex the
// previous vertex on one shortest path.
vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& adj, int s, vector<int>& parent) {
    const long long INF = LLONG_MAX / 4;  // large, but d + w cannot overflow
    vector<long long> dist(adj.size(), INF);
    vector<bool> done(adj.size(), false);
    parent.assign(adj.size(), 0);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> heap;  // (distance, vertex), smallest first
    dist[s] = 0;
    heap.push({0, s});
    while (!heap.empty()) {
        auto [d, u] = heap.top();
        heap.pop();
        if (done[u]) continue;  // an older, larger entry of a vertex that is final already
        done[u] = true;
        for (auto [v, w] : adj[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                parent[v] = u;
                heap.push({dist[v], v});
            }
        }
    }
    return dist;
}
// snippet:end

string show(const vector<long long>& dist, int n) {
    string out = "dist:";
    for (int v = 1; v <= n; v++) out += " " + (dist[v] >= LLONG_MAX / 4 ? string("-") : to_string(dist[v]));
    return out;
}

int main() {
    {
        vector<vector<pair<int, long long>>> adj(6);
        adj[1] = {{2, 4}, {3, 1}};
        adj[3] = {{2, 2}, {4, 5}};
        adj[2] = {{4, 1}};
        vector<int> parent;
        auto dist = dijkstra(adj, 1, parent);
        vector<int> path;
        for (int v = 4; v != 1; v = parent[v]) path.push_back(v);
        path.push_back(1);
        reverse(path.begin(), path.end());
        cout << "arrows 1>2 (4), 1>3 (1), 3>2 (2), 2>4 (1), 3>4 (5), from 1: " << show(dist, 5) << "; path to 4:";
        for (int v : path) cout << ' ' << v;
        cout << "\n";
    }
    {
        vector<vector<pair<int, long long>>> adj(4);
        adj[1] = {{2, 0}};
        adj[2] = {{3, 0}};
        vector<int> parent;
        cout << "arrows 1>2 (0), 2>3 (0), from 1: " << show(dijkstra(adj, 1, parent), 3) << "\n";
    }
    {
        vector<vector<pair<int, long long>>> adj(4);
        auto edge = [&](int a, int b, long long w) {
            adj[a].push_back({b, w});
            adj[b].push_back({a, w});
        };
        edge(1, 2, 5);
        edge(2, 3, 1);
        edge(1, 3, 10);
        vector<int> parent;
        cout << "edges 1-2 (5), 2-3 (1), 1-3 (10), from 1: " << show(dijkstra(adj, 1, parent), 3) << "\n";
    }
    // Check against the Floyd-Warshall table on random directed graphs with 6 vertices and weights 0..9.
    mt19937 rng(12345);
    for (int trial = 0; trial < 20000; trial++) {
        int n = 6;
        const long long INF = LLONG_MAX / 4;
        vector<vector<pair<int, long long>>> adj(n + 1);
        vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));
        for (int v = 1; v <= n; v++) d[v][v] = 0;
        int edges = rng() % 14;
        for (int i = 0; i < edges; i++) {
            int a = rng() % n + 1, b = rng() % n + 1;
            long long w = rng() % 10;
            adj[a].push_back({b, w});
            d[a][b] = min(d[a][b], w);
        }
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (d[i][k] < INF && d[k][j] < INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        int s = rng() % n + 1;
        vector<int> parent;
        auto dist = dijkstra(adj, s, parent);
        for (int v = 1; v <= n; v++) {
            if (dist[v] != d[s][v]) return 1;
            if (v != s && dist[v] < INF) {  // the parent chain has the right length
                long long length = 0;
                for (int x = v; x != s; x = parent[x]) {
                    long long best = INF;
                    for (auto [to, w] : adj[parent[x]])
                        if (to == x) best = min(best, w);
                    if (dist[x] != dist[parent[x]] + best) return 1;
                    length += best;
                }
                if (length != dist[v]) return 1;
            }
        }
    }
}
