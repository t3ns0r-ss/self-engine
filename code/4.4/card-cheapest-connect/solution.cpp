#include <bits/stdc++.h>
using namespace std;

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

long long kruskal(int n, vector<array<long long, 3>> edges) {
    sort(edges.begin(), edges.end(), [](const auto& x, const auto& y) { return x[2] < y[2]; });
    Dsu dsu(n + 1);
    long long total = 0;
    for (auto [a, b, w] : edges) if (dsu.unite(a, b)) total += w;
    return total;
}

// Brute force: try every set of n - 1 edges and keep the cheapest one that connects all vertices.
long long bruteTree(int n, const vector<array<long long, 3>>& edges) {
    int m = edges.size();
    long long best = LLONG_MAX;
    for (int mask = 0; mask < (1 << m); mask++) {
        if (__builtin_popcount(mask) != n - 1) continue;
        Dsu dsu(n + 1);
        long long total = 0;
        int joined = 0;
        for (int i = 0; i < m; i++) if (mask >> i & 1) joined += dsu.unite(edges[i][0], edges[i][1]), total += edges[i][2];
        if (joined == n - 1) best = min(best, total);
    }
    return best;
}

// Brute force for N1: the cheapest route from s to t, trying every simple path.
long long cheapestRoute(int n, const vector<array<long long, 3>>& edges, int s, int t) {
    long long best = LLONG_MAX;
    vector<int> perm;
    for (int v = 1; v <= n; v++) if (v != s && v != t) perm.push_back(v);
    do {
        for (int len = 0; len <= (int)perm.size(); len++) {
            vector<int> path = {s};
            path.insert(path.end(), perm.begin(), perm.begin() + len);
            path.push_back(t);
            long long total = 0;
            bool ok = true;
            for (size_t i = 0; i + 1 < path.size() && ok; i++) {
                long long w = LLONG_MAX;
                for (auto [a, b, c] : edges) if ((a == path[i] && b == path[i + 1]) || (b == path[i] && a == path[i + 1])) w = min(w, c);
                if (w == LLONG_MAX) ok = false;
                else total += w;
            }
            if (ok) best = min(best, total);
        }
    } while (next_permutation(perm.begin(), perm.end()));
    return best;
}

int main() {
    // P1: 5 offices and 7 possible cables (a, b, price); the cheapest set of cables that connects all offices.
    vector<array<long long, 3>> cables = {{1, 2, 4}, {1, 3, 2}, {2, 3, 1}, {2, 4, 5}, {3, 4, 8}, {3, 5, 10}, {4, 5, 3}};
    cout << "P1 brute=" << bruteTree(5, cables) << " method=" << kruskal(5, cables) << "\n";
    // N1: the cheapest ROUTE from 1 to 3 on the triangle 1-2 (3), 2-3 (3), 1-3 (5); the spanning tree 1-2, 2-3 has total 6, and the
    // path between 1 and 3 inside it costs 6, but the direct edge costs 5.
    vector<array<long long, 3>> tri = {{1, 2, 3}, {2, 3, 3}, {1, 3, 5}};
    sort(tri.begin(), tri.end(), [](const auto& x, const auto& y) { return x[2] < y[2]; });
    Dsu dsu(4);
    vector<array<long long, 3>> kept;
    for (auto e : tri) if (dsu.unite(e[0], e[1])) kept.push_back(e);
    long long inTree = 0;  // the path 1 - 2 - 3 inside the tree: both kept edges
    for (auto e : kept) inTree += e[2];
    cout << "N1 brute=" << cheapestRoute(3, tri, 1, 3) << " method=" << inTree << "\n";
}
