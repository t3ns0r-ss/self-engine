#include <bits/stdc++.h>
using namespace std;

// The structure of Theorem 4.4.1.
struct Dsu {
    vector<int> parent, size;
    Dsu(int n) : parent(n), size(n, 1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) {
        while (parent[x] != x) parent[x] = parent[parent[x]], x = parent[x];
        return x;
    }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

// snippet:begin
// Theorem 4.4.4. Kruskal's algorithm. Edges are {a, b, weight} on vertices 0..n-1. Returns the weight of a minimum spanning tree,
// or -1 if the graph is not connected.
long long kruskal(int n, vector<array<long long, 3>> edges) {
    sort(edges.begin(), edges.end(), [](const auto& x, const auto& y) { return x[2] < y[2]; });  // lightest first
    Dsu dsu(n);
    long long total = 0;
    int taken = 0;
    for (auto [a, b, w] : edges)
        if (dsu.unite(a, b)) total += w, taken++;  // joins two groups: it is in the tree
    return taken == n - 1 ? total : -1;
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
    cout << "triangle 0-1 (1), 1-2 (2), 0-2 (3): " << kruskal(3, {{0, 1, 1}, {1, 2, 2}, {0, 2, 3}}) << "\n";
    cout << "square with a diagonal: " << kruskal(4, {{0, 1, 4}, {1, 2, 2}, {2, 3, 4}, {3, 0, 3}, {0, 2, 5}}) << "\n";
    cout << "two separate edges on 4 vertices: " << kruskal(4, {{0, 1, 1}, {2, 3, 1}}) << "\n";
    cout << "one vertex: " << kruskal(1, {}) << "\n";
    mt19937 rng(4404);
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 6 + 1;
        int m = n > 1 ? rng() % 10 : 0;
        vector<array<long long, 3>> es;
        for (int i = 0; i < m; i++) {
            long long a = rng() % n, b = rng() % n;
            if (a != b) es.push_back({a, b, (long long)(rng() % 7 + 1)});
        }
        if (kruskal(n, es) != bruteMst(n, es)) return 1;
    }
}
