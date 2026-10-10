#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.5.4. The diameter of a tree with non-negative weights: walk from any vertex to its farthest vertex a, then from a to
// its farthest vertex b; d(a, b) is the length of the longest path. adj[u] holds {neighbour, weight}; vertices are 1..n.
// Distances from s to every vertex of a weighted tree; returns a vertex at the largest distance.
int farthestFrom(const vector<vector<pair<int, long long>>>& adj, int s, vector<long long>& dist) {
    dist.assign(adj.size(), -1);
    dist[s] = 0;
    vector<int> stack = {s};
    int far = s;
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        if (dist[u] > dist[far]) far = u;
        for (auto [v, w] : adj[u])
            if (dist[v] < 0) dist[v] = dist[u] + w, stack.push_back(v);
    }
    return far;
}
long long diameter(const vector<vector<pair<int, long long>>>& adj, int& a, int& b) {
    vector<long long> dist;
    a = farthestFrom(adj, 1, dist);
    b = farthestFrom(adj, a, dist);
    return dist[b];
}
// snippet:end

int main() {
    auto build = [](int n, vector<array<long long, 3>> es) {
        vector<vector<pair<int, long long>>> adj(n + 1);
        for (auto [a, b, w] : es) adj[a].push_back({(int)b, w}), adj[b].push_back({(int)a, w});
        return adj;
    };
    int a, b;
    {
        auto adj = build(6, {{1, 2, 3}, {2, 3, 4}, {2, 4, 1}, {4, 5, 6}, {1, 6, 2}});
        long long d = diameter(adj, a, b);
        cout << "tree 1-2 (3), 2-3 (4), 2-4 (1), 4-5 (6), 1-6 (2): diameter " << d << " between " << min(a, b) << " and " << max(a, b) << "\n";
    }
    {
        auto adj = build(1, {});
        cout << "one vertex: diameter " << diameter(adj, a, b) << "\n";
    }
    {
        auto adj = build(4, {{1, 2, 0}, {2, 3, 0}, {3, 4, 0}});
        cout << "all weights 0: diameter " << diameter(adj, a, b) << "\n";
    }
    // Check against: Floyd-Warshall, the largest entry of the table of all distances.
    mt19937 rng(4504);
    auto randomTree = [](mt19937& rng, int n, int maxW) {
        vector<int> label(n);
        iota(label.begin(), label.end(), 1);
        shuffle(label.begin(), label.end(), rng);
        vector<vector<pair<int, long long>>> adj(n + 1);
        for (int i = 1; i < n; i++) {
            int a = label[i], b = label[rng() % i];
            long long w = rng() % (maxW + 1);
            adj[a].push_back({b, w});
            adj[b].push_back({a, w});
        }
        return adj;
    };
    auto floyd = [](const vector<vector<pair<int, long long>>>& adj) {
        int n = adj.size() - 1;
        const long long INF = LLONG_MAX / 4;
        vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));
        for (int v = 1; v <= n; v++) d[v][v] = 0;
        for (int u = 1; u <= n; u++) for (auto [v, w] : adj[u]) d[u][v] = min(d[u][v], w);
        for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        return d;
    };
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 9 + 1;
        auto adj = randomTree(rng, n, rng() % 2 ? 1 : 9);
        auto d = floyd(adj);
        long long best = 0;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) best = max(best, d[i][j]);
        long long got = diameter(adj, a, b);
        if (got != best || d[a][b] != best) return 1;
    }
}
