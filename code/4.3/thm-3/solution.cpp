#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.3.3. Shortest distances from s when weights may be negative. Returns false if a negative cycle can be reached from s
// (then the distances mean nothing); each edge is {from, to, weight}.
bool bellmanFord(int n, const vector<array<long long, 3>>& edges, int s, vector<long long>& dist) {
    const long long INF = LLONG_MAX / 4;
    dist.assign(n + 1, INF);
    dist[s] = 0;
    for (int round = 1; round <= n; round++) {
        bool changed = false;
        for (auto [u, v, w] : edges) {
            if (dist[u] < INF && dist[u] + w < dist[v]) {  // relax the edge u -> v
                dist[v] = dist[u] + w;
                changed = true;
            }
        }
        if (!changed) return true;     // a whole round without change: the distances are final
        if (round == n) return false;  // still changing in round n: a reachable negative cycle
    }
    return true;
}
// snippet:end

string run(int n, vector<array<long long, 3>> edges, int s) {
    vector<long long> dist;
    bool ok = bellmanFord(n, edges, s, dist);
    if (!ok) return "negative cycle";
    string out = "dist:";
    for (int v = 1; v <= n; v++) out += " " + (dist[v] >= LLONG_MAX / 4 ? string("-") : to_string(dist[v]));
    return out;
}

int main() {
    cout << "arrows 1>2 (4), 1>3 (5), 3>2 (-3), from 1: " << run(3, {{1, 2, 4}, {1, 3, 5}, {3, 2, -3}}, 1) << "\n";
    cout << "arrows 1>2 (1), 2>3 (-2), 3>2 (1), from 1: " << run(3, {{1, 2, 1}, {2, 3, -2}, {3, 2, 1}}, 1) << "\n";
    cout << "arrows 1>4 (2), 2>3 (-2), 3>2 (1), from 1: " << run(4, {{1, 4, 2}, {2, 3, -2}, {3, 2, 1}}, 1) << "\n";
    // Check against the Floyd-Warshall table with negative edges that cannot form a negative cycle: w = c + p[u] - p[v] with c >= 0,
    // and against the negative-cycle claim on random graphs with arbitrary weights.
    mt19937 rng(4242);
    const long long INF = LLONG_MAX / 4;
    for (int trial = 0; trial < 20000; trial++) {
        int n = 6;
        bool noCycle = trial % 2 == 0;
        vector<long long> p(n + 1);
        for (auto& x : p) x = (long long)(rng() % 11) - 5;
        vector<array<long long, 3>> edges;
        vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));
        for (int v = 1; v <= n; v++) d[v][v] = 0;
        int count = rng() % 12;
        for (int i = 0; i < count; i++) {
            int a = rng() % n + 1, b = rng() % n + 1;
            if (a == b) continue;
            long long w = noCycle ? (long long)(rng() % 6) + p[a] - p[b] : (long long)(rng() % 9) - 3;
            edges.push_back({a, b, w});
            d[a][b] = min(d[a][b], w);
        }
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (d[i][k] < INF && d[k][j] < INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        int s = rng() % n + 1;
        bool negativeCycleReachable = false;
        for (int v = 1; v <= n; v++)
            if (d[v][v] < 0 && d[s][v] < INF) negativeCycleReachable = true;
        vector<long long> dist;
        bool ok = bellmanFord(n, edges, s, dist);
        if (ok == negativeCycleReachable) return 1;
        if (ok)
            for (int v = 1; v <= n; v++)
                if (dist[v] != d[s][v]) return 1;
    }
}
