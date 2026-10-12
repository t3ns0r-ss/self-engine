#include <bits/stdc++.h>
using namespace std;

struct Rooted {
    int n;
    vector<vector<int>> adj, children;
    vector<int> parent, order;
    Rooted(int n, const vector<pair<int, int>>& edges) : n(n), adj(n), children(n), parent(n, -1) {
        for (auto [a, b] : edges) adj[a].push_back(b), adj[b].push_back(a);
        order = {0};
        for (size_t i = 0; i < order.size(); i++) {
            int v = order[i];
            for (int u : adj[v])
                if (u != parent[v]) parent[u] = v, children[v].push_back(u), order.push_back(u);
        }
    }
};
vector<pair<int, int>> randomTree(int n, mt19937& rng) {
    vector<int> label(n);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin(), label.end(), rng);
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) edges.push_back({label[i], label[rng() % i]});
    return edges;
}

// snippet:begin
// Theorem 7.1.1. Colour the vertices black or white so that no two neighbours are both black.
// For every vertex v: {ways with v white, ways with v black} for its subtree. order lists parents before children.
vector<array<long long, 2>> colourings(const vector<vector<int>>& children, const vector<int>& order, long long M) {
    int n = order.size();
    vector<array<long long, 2>> f(n, {1 % M, 1 % M});
    for (int i = n - 1; i >= 0; i--) {  // a vertex is finished after all its children
        int v = order[i];
        for (int c : children[v]) {
            f[v][0] = f[v][0] * ((f[c][0] + f[c][1]) % M) % M;  // v white: a child may have any colour
            f[v][1] = f[v][1] * f[c][0] % M;                    // v black: every child is white
        }
    }
    return f;
}
// snippet:end

vector<pair<int, int>> sampleEdges = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};

long long bruteColourings(int n, const vector<pair<int, int>>& edges) {
    long long count = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (auto [a, b] : edges) ok = ok && !((mask >> a & 1) && (mask >> b & 1));
        count += ok;
    }
    return count;
}

int main() {
    Rooted t(5, sampleEdges);
    auto f = colourings(t.children, t.order, 1000000007);
    for (int v = 0; v < 5; v++) cout << "vertex " << v << ": white " << f[v][0] << ", black " << f[v][1] << "\n";
    cout << "colourings " << (f[0][0] + f[0][1]) << "\n";
    // The path of 3 vertices and the star of 4 vertices (the samples of AtCoder DP P).
    for (auto edges : {vector<pair<int, int>>{{0, 1}, {1, 2}}, vector<pair<int, int>>{{0, 1}, {0, 2}, {0, 3}}}) {
        int n = edges.size() + 1;
        Rooted r(n, edges);
        auto g = colourings(r.children, r.order, 1000000007);
        cout << "tree of " << n << " vertices: " << g[0][0] + g[0][1] << "\n";
    }
    // Check (not printed): the same as trying all 2^n colourings, for 2000 random trees of up to 12 vertices, with a modulus.
    mt19937 rng(7);
    for (int it = 0; it < 2000; it++) {
        int n = 1 + rng() % 12;
        auto edges = randomTree(n, rng);
        Rooted r(n, edges);
        long long M = 1 + rng() % 1000;
        auto g = colourings(r.children, r.order, M);
        if ((g[0][0] + g[0][1]) % M != bruteColourings(n, edges) % M) return 1;
    }
}
