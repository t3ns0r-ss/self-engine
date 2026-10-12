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
// Theorem 7.1.3. For every vertex v as the root: the number of connected sets of black vertices that contain v, modulo M
// (M is any number, so nothing is divided). down[v]: inside the subtree of v. up[c]: the part above c, seen from its parent p.
vector<long long> rerootCount(const vector<vector<int>>& children, const vector<int>& order, long long M) {
    int n = order.size();
    vector<long long> down(n, 1 % M), up(n, 0), answer(n);
    for (int i = n - 1; i >= 0; i--)
        for (int c : children[order[i]]) down[order[i]] = down[order[i]] * ((down[c] + 1) % M) % M;
    for (int v : order) {  // a parent is finished before its children
        int k = children[v].size();
        vector<long long> suffix(k + 1, 1 % M);
        for (int i = k - 1; i >= 0; i--) suffix[i] = suffix[i + 1] * ((down[children[v][i]] + 1) % M) % M;
        long long prefix = (up[v] + 1) % M;  // the part above v and the children in front of the current one
        for (int i = 0; i < k; i++) {
            int c = children[v][i];
            up[c] = prefix * suffix[i + 1] % M;  // all neighbours of v except c
            prefix = prefix * ((down[c] + 1) % M) % M;
        }
        answer[v] = down[v] * ((up[v] + 1) % M) % M;
    }
    return answer;
}
// snippet:end

vector<pair<int, int>> sampleEdges = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};

// Rooting the tree at r and using only the downward values: the plain subtree DP, run once for each root.
long long countFrom(int n, const vector<pair<int, int>>& edges, int r, long long M) {
    vector<vector<int>> adj(n);
    for (auto [a, b] : edges) adj[a].push_back(b), adj[b].push_back(a);
    function<long long(int, int)> go = [&](int v, int p) {
        long long x = 1 % M;
        for (int u : adj[v])
            if (u != p) x = x * ((go(u, v) + 1) % M) % M;
        return x;
    };
    return go(r, -1);
}

int main() {
    Rooted t(5, sampleEdges);
    cout << "sample tree, M = 1000000007:";
    for (long long x : rerootCount(t.children, t.order, 1000000007)) cout << " " << x;
    cout << "\n";
    cout << "sample tree, M = 6:";
    for (long long x : rerootCount(t.children, t.order, 6)) cout << " " << x;
    cout << "\n";
    Rooted path(3, {{0, 1}, {1, 2}});
    cout << "path of 3 vertices, M = 100:";
    for (long long x : rerootCount(path.children, path.order, 100)) cout << " " << x;
    cout << "\n";
    // Check (not printed): the same as the plain DP run from every vertex as the root, for 2000 random trees of up to 12 vertices
    // and random moduli (including ones for which a factor is 0 modulo M).
    mt19937 rng(13);
    for (int it = 0; it < 2000; it++) {
        int n = 1 + rng() % 12;
        auto edges = randomTree(n, rng);
        Rooted r(n, edges);
        long long M = 1 + rng() % 50;
        auto got = rerootCount(r.children, r.order, M);
        for (int v = 0; v < n; v++)
            if (got[v] != countFrom(n, edges, v, M)) return 1;
    }
}
