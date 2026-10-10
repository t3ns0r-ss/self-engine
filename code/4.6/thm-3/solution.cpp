#include <bits/stdc++.h>
using namespace std;

struct Rooted {
    vector<int> order, parent, depth;
};
Rooted rootAt(const vector<vector<int>>& adj, int root) {
    int n = adj.size() - 1;
    Rooted t{{}, vector<int>(n + 1, 0), vector<int>(n + 1, 0)};
    vector<int> stack = {root};
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        t.order.push_back(u);
        for (int v : adj[u])
            if (v != t.parent[u]) {  // in a tree the only visited neighbour of u is its parent
                t.parent[v] = u;
                t.depth[v] = t.depth[u] + 1;
                stack.push_back(v);
            }
    }
    return t;
}

struct Lifting {
    vector<vector<int>> up;  // up[j][v]: the 2^j-th ancestor of v, or 0 if there is none (up[j][0] = 0)
    vector<int> depth;
    Lifting(const vector<vector<int>>& adj, int root) {
        int n = adj.size() - 1, levels = 1;
        while ((1 << levels) <= n) levels++;
        Rooted t = rootAt(adj, root);
        depth = t.depth;
        up.assign(levels, t.parent);  // up[0] is the parent
        for (int j = 1; j < levels; j++)
            for (int v = 1; v <= n; v++) up[j][v] = up[j - 1][up[j - 1][v]];  // two jumps of 2^(j-1)
    }
    int kthAncestor(int v, int k) const {  // 0 if v has fewer than k ancestors
        if (k > depth[v]) return 0;
        for (int j = 0; j < (int)up.size(); j++)
            if (k >> j & 1) v = up[j][v];
        return v;
    }
};

int lca(const Lifting& L, int u, int v) {
    if (L.depth[u] < L.depth[v]) swap(u, v);
    u = L.kthAncestor(u, L.depth[u] - L.depth[v]);
    if (u == v) return u;
    for (int j = (int)L.up.size() - 1; j >= 0; j--)
        if (L.up[j][u] != L.up[j][v]) u = L.up[j][u], v = L.up[j][v];  // still below the meeting point: take the jump
    return L.up[0][u];
}

// snippet:begin
// Theorem 4.6.3. The distance between u and v: wdepth[v] is the sum of the weights on the path from the root to v (the depth when
// every weight is 1). The path goes up from u to the lowest common ancestor and down to v.
long long treeDistance(const Lifting& L, const vector<long long>& wdepth, int u, int v) {
    return wdepth[u] + wdepth[v] - 2 * wdepth[lca(L, u, v)];
}
// snippet:end

int main() {
    auto weightedDepths = [](const vector<vector<int>>& adj, int root, const vector<array<int, 3>>& edges) {
        int n = adj.size() - 1;
        map<pair<int, int>, long long> w;
        for (auto [a, b, c] : edges) w[{a, b}] = w[{b, a}] = c;
        auto t = rootAt(adj, root);
        vector<long long> wd(n + 1, 0);
        for (int v : t.order) if (t.parent[v]) wd[v] = wd[t.parent[v]] + w[{v, t.parent[v]}];
        return wd;
    };
    {
        vector<array<int, 3>> edges = {{1, 2, 3}, {2, 3, 4}, {2, 4, 1}, {4, 5, 6}, {1, 6, 2}};
        vector<vector<int>> adj(7);
        for (auto [a, b, c] : edges) adj[a].push_back(b), adj[b].push_back(a);
        Lifting L(adj, 1);
        auto wd = weightedDepths(adj, 1, edges);
        cout << "tree 1-2 (3), 2-3 (4), 2-4 (1), 4-5 (6), 1-6 (2): d(3, 5) = " << treeDistance(L, wd, 3, 5) << ", d(6, 5) = " << treeDistance(L, wd, 6, 5)
             << ", d(3, 3) = " << treeDistance(L, wd, 3, 3) << ", d(1, 4) = " << treeDistance(L, wd, 1, 4) << "\n";
    }
    mt19937 rng(4603);
    auto randomWeighted = [](mt19937& rng, int n, int maxW, vector<array<int, 3>>& edges) {
        vector<int> label(n);
        iota(label.begin(), label.end(), 1);
        shuffle(label.begin(), label.end(), rng);
        vector<vector<int>> adj(n + 1);
        edges.clear();
        for (int i = 1; i < n; i++) {
            int a = label[i], b = label[rng() % i], w = rng() % (maxW + 1);
            adj[a].push_back(b);
            adj[b].push_back(a);
            edges.push_back({a, b, w});
        }
        return adj;
    };
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 12 + 1, root = rng() % n + 1;
        vector<array<int, 3>> edges;
        auto adj = randomWeighted(rng, n, rng() % 2 ? 1 : 9, edges);
        Lifting L(adj, root);
        auto wd = weightedDepths(adj, root, edges);
        // reference: Floyd-Warshall
        const long long INF = LLONG_MAX / 4;
        vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));
        for (int v = 1; v <= n; v++) d[v][v] = 0;
        for (auto [a, b, c] : edges) d[a][b] = d[b][a] = min<long long>(d[a][b], c);
        for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        for (int u = 1; u <= n; u++) for (int v = 1; v <= n; v++) if (treeDistance(L, wd, u, v) != d[u][v]) return 1;
    }
}
