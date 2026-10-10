#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.3.4. All shortest distances at once. On entry d[i][j] is the weight of the edge i -> j (INF if none, 0 for i == j);
// on return it is the shortest distance from i to j. Vertex k is allowed as a stop-over one at a time, in the outer loop.
void floydWarshall(vector<vector<long long>>& d) {
    const long long INF = LLONG_MAX / 4;
    int n = d.size();
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][k] < INF && d[k][j] < INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
// snippet:end

int main() {
    const long long INF = LLONG_MAX / 4;
    auto run = [&](int n, vector<array<long long, 3>> edges) {
        vector<vector<long long>> d(n, vector<long long>(n, INF));
        for (int v = 0; v < n; v++) d[v][v] = 0;
        for (auto [a, b, w] : edges) d[a][b] = min(d[a][b], w);
        floydWarshall(d);
        for (int i = 0; i < n; i++) {
            cout << "  from " << i + 1 << ":";
            for (int j = 0; j < n; j++) cout << ' ' << (d[i][j] >= INF ? string("-") : to_string(d[i][j]));
            cout << "\n";
        }
    };
    cout << "arrows 1>2 (3), 2>3 (1), 1>3 (7), 3>1 (2):\n";
    run(3, {{0, 1, 3}, {1, 2, 1}, {0, 2, 7}, {2, 0, 2}});
    cout << "arrows 1>2 (5), 2>3 (-2), 3>4 (1), 1>4 (9):\n";
    run(4, {{0, 1, 5}, {1, 2, -2}, {2, 3, 1}, {0, 3, 9}});
    // Check against a shortest-path search from every vertex (repeated relaxation) on random graphs without negative cycles.
    mt19937 rng(99);
    for (int trial = 0; trial < 20000; trial++) {
        int n = 6;
        vector<long long> p(n);
        for (auto& x : p) x = (long long)(rng() % 9) - 4;
        vector<array<long long, 3>> edges;
        int count = rng() % 14;
        for (int i = 0; i < count; i++) {
            int a = rng() % n, b = rng() % n;
            if (a == b) continue;
            edges.push_back({a, b, (long long)(rng() % 6) + p[a] - p[b]});
        }
        vector<vector<long long>> d(n, vector<long long>(n, INF));
        for (int v = 0; v < n; v++) d[v][v] = 0;
        for (auto [a, b, w] : edges) d[a][b] = min(d[a][b], w);
        floydWarshall(d);
        for (int s = 0; s < n; s++) {
            vector<long long> best(n, INF);
            best[s] = 0;
            for (int round = 0; round < n; round++)
                for (auto [a, b, w] : edges)
                    if (best[a] < INF && best[a] + w < best[b]) best[b] = best[a] + w;
            for (int v = 0; v < n; v++)
                if (best[v] != d[s][v]) return 1;
        }
    }
}
