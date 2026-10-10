#include <bits/stdc++.h>
using namespace std;

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

// snippet:begin
// Theorem 4.5.5. For every vertex, the distance to the vertex farthest from it: the larger of its distances to the two ends a and b of
// a diameter. adj[u] holds {neighbour, weight} (weights >= 0); vertices are 1..n.
vector<long long> farthestDistances(const vector<vector<pair<int, long long>>>& adj) {
    vector<long long> fromFirst, fromA, fromB;
    int a = farthestFrom(adj, 1, fromFirst);   // an end of a diameter
    int b = farthestFrom(adj, a, fromA);       // the other end
    farthestFrom(adj, b, fromB);
    vector<long long> best(adj.size(), 0);
    for (int v = 1; v < (int)adj.size(); v++) best[v] = max(fromA[v], fromB[v]);
    return best;
}
// snippet:end

int main() {
    auto build = [](int n, vector<array<long long, 3>> es) {
        vector<vector<pair<int, long long>>> adj(n + 1);
        for (auto [a, b, w] : es) adj[a].push_back({(int)b, w}), adj[b].push_back({(int)a, w});
        return adj;
    };
    auto show = [](const vector<long long>& d) {
        string s;
        for (size_t v = 1; v < d.size(); v++) s += " " + to_string(d[v]);
        return s;
    };
    cout << "path 1-2-3-4 (weights 1): farthest distances" << show(farthestDistances(build(4, {{1, 2, 1}, {2, 3, 1}, {3, 4, 1}}))) << "\n";
    cout << "star with centre 1 and leaves 2, 3, 4 (weights 5, 2, 3):" << show(farthestDistances(build(4, {{1, 2, 5}, {1, 3, 2}, {1, 4, 3}}))) << "\n";
    cout << "one vertex:" << show(farthestDistances(build(1, {}))) << "\n";
    // Check against: Floyd-Warshall, the largest entry in each row.
    mt19937 rng(4505);
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
        auto got = farthestDistances(adj);
        for (int i = 1; i <= n; i++) {
            long long best = 0;
            for (int j = 1; j <= n; j++) best = max(best, d[i][j]);
            if (got[i] != best) return 1;
        }
    }
}
