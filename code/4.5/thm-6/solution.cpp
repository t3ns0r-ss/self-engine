#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.5.6. The sum of the distances over all pairs of vertices {u, v} of a weighted tree: an edge of weight w whose lower side has
// s vertices lies on s * (n - s) of the paths. adj[u] holds {neighbour, weight}; vertices are 1..n.
long long sumOfAllDistances(const vector<vector<pair<int, long long>>>& adj) {
    int n = adj.size() - 1;
    vector<int> parent(n + 1, 0), order, size(n + 1, 1);
    vector<long long> up(n + 1, 0);  // the weight of the edge from v to its parent
    vector<int> stack = {1};
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        order.push_back(u);
        for (auto [v, w] : adj[u])
            if (v != parent[u]) parent[v] = u, up[v] = w, stack.push_back(v);
    }
    long long total = 0;
    for (int i = n - 1; i > 0; i--) {  // children before parents
        int v = order[i];
        size[parent[v]] += size[v];
        total += up[v] * size[v] * (n - size[v]);  // the pairs on both sides of the edge to the parent
    }
    return total;
}
// snippet:end

int main() {
    auto build = [](int n, vector<array<long long, 3>> es) {
        vector<vector<pair<int, long long>>> adj(n + 1);
        for (auto [a, b, w] : es) adj[a].push_back({(int)b, w}), adj[b].push_back({(int)a, w});
        return adj;
    };
    cout << "path 1-2-3 (weights 1, 1): " << sumOfAllDistances(build(3, {{1, 2, 1}, {2, 3, 1}})) << "\n";
    cout << "star with centre 1 and leaves 2, 3, 4 (weights 5, 2, 3): " << sumOfAllDistances(build(4, {{1, 2, 5}, {1, 3, 2}, {1, 4, 3}})) << "\n";
    cout << "one vertex: " << sumOfAllDistances(build(1, {})) << "\n";
    // Check against: Floyd-Warshall, the sum over all pairs u < v.
    mt19937 rng(4506);
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
        long long expected = 0;
        for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) expected += d[i][j];
        if (sumOfAllDistances(adj) != expected) return 1;
    }
}
