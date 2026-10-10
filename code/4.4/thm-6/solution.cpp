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
// Theorem 4.4.6. The smallest possible largest edge on a path from s to t (-1 if there is none): the weight of the edge at which
// Kruskal's algorithm first puts s and t into one group.
long long smallestLargestEdge(int n, vector<array<long long, 3>> edges, int s, int t) {
    if (s == t) return 0;  // the empty path has no edge
    sort(edges.begin(), edges.end(), [](const auto& x, const auto& y) { return x[2] < y[2]; });
    Dsu dsu(n);
    for (auto [a, b, w] : edges) {
        dsu.unite(a, b);
        if (dsu.find(s) == dsu.find(t)) return w;  // every earlier edge was lighter or equal, and they did not connect s and t
    }
    return -1;
}
// snippet:end

int main() {
    cout << "path 0-1 (5), 1-2 (3); 0 to 2: " << smallestLargestEdge(3, {{0, 1, 5}, {1, 2, 3}}, 0, 2) << "\n";
    cout << "direct 0-2 (9) or via 1 (4 and 6); 0 to 2: " << smallestLargestEdge(3, {{0, 2, 9}, {0, 1, 4}, {1, 2, 6}}, 0, 2) << "\n";
    cout << "no road between 0 and 3: " << smallestLargestEdge(4, {{0, 1, 1}, {2, 3, 1}}, 0, 3) << "\n";
    // Check against: for each limit L from 1 up, look for a path using edges of weight at most L with a plain walk.
    mt19937 rng(4406);
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 6 + 1;
        int m = n > 1 ? rng() % 10 : 0;
        vector<array<long long, 3>> es;
        for (int i = 0; i < m; i++) {
            long long a = rng() % n, b = rng() % n;
            if (a != b) es.push_back({a, b, (long long)(rng() % 7 + 1)});
        }
        int s = rng() % n, t = rng() % n;
        long long expected = s == t ? 0 : -1;
        for (long long limit = 1; limit <= 7 && s != t; limit++) {
            vector<bool> seen(n, false);
            vector<int> stack = {s};
            seen[s] = true;
            while (!stack.empty()) {
                int u = stack.back();
                stack.pop_back();
                for (auto [a, b, w] : es) {
                    if (w > limit) continue;
                    int v = a == u ? b : (b == u ? a : -1);
                    if (v >= 0 && !seen[v]) seen[v] = true, stack.push_back(v);
                }
            }
            if (seen[t]) { expected = limit; break; }
        }
        if (smallestLargestEdge(n, es, s, t) != expected) return 1;
    }
}
