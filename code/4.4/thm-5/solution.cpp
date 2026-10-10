#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.4.5. Prim's algorithm from vertex 0. adj[u] holds {neighbour, weight}. Returns the weight of a minimum spanning tree,
// or -1 if the graph is not connected.
long long prim(const vector<vector<pair<int, long long>>>& adj) {
    int n = adj.size();
    vector<bool> inTree(n, false);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> heap;  // (weight of the edge, vertex it leads to)
    heap.push({0, 0});
    long long total = 0;
    int taken = 0;
    while (!heap.empty()) {
        auto [w, u] = heap.top();
        heap.pop();
        if (inTree[u]) continue;  // the edge leads into the tree: skip it
        inTree[u] = true;
        total += w, taken++;
        for (auto [v, c] : adj[u])
            if (!inTree[v]) heap.push({c, v});  // the key is the edge weight itself, not a distance
    }
    return taken == n ? total : -1;
}
// snippet:end

// Weight of a minimum spanning tree by trying every set of n - 1 edges (-1 if the graph is not connected); n <= 7.
long long bruteMst(int n, const vector<array<long long, 3>>& edges) {
    int m = edges.size();
    long long best = -1;
    for (int mask = 0; mask < (1 << m); mask++) {
        if (__builtin_popcount(mask) != n - 1) continue;
        vector<int> label(n);
        iota(label.begin(), label.end(), 0);
        long long total = 0;
        for (int i = 0; i < m; i++)
            if (mask >> i & 1) {
                int a = label[edges[i][0]], b = label[edges[i][1]];
                for (int& x : label) if (x == b) x = a;
                total += edges[i][2];
            }
        if (set<int>(label.begin(), label.end()).size() == 1 && (best == -1 || total < best)) best = total;
    }
    return best;
}

int main() {
    auto build = [](int n, const vector<array<long long, 3>>& es) {
        vector<vector<pair<int, long long>>> adj(n);
        for (auto [a, b, w] : es) adj[a].push_back({(int)b, w}), adj[b].push_back({(int)a, w});
        return adj;
    };
    auto run = [&](int n, const vector<array<long long, 3>>& es) { return prim(build(n, es)); };
    cout << "triangle 0-1 (1), 1-2 (2), 0-2 (3): " << run(3, {{0, 1, 1}, {1, 2, 2}, {0, 2, 3}}) << "\n";
    cout << "square with a diagonal: " << run(4, {{0, 1, 4}, {1, 2, 2}, {2, 3, 4}, {3, 0, 3}, {0, 2, 5}}) << "\n";
    cout << "two separate edges on 4 vertices: " << run(4, {{0, 1, 1}, {2, 3, 1}}) << "\n";
    cout << "one vertex: " << run(1, {}) << "\n";
    mt19937 rng(4405);
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 6 + 1;
        int m = n > 1 ? rng() % 10 : 0;
        vector<array<long long, 3>> es;
        for (int i = 0; i < m; i++) {
            long long a = rng() % n, b = rng() % n;
            if (a != b) es.push_back({a, b, (long long)(rng() % 7 + 1)});
        }
        if (run(n, es) != bruteMst(n, es)) return 1;
    }
}
