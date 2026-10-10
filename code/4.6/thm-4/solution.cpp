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
// Theorem 4.6.4. The smallest edge weight on the path from u to v. mn[j][v] is the smallest weight among the 2^j edges going up from
// v (INF if there are fewer); mn[0][v] is the weight of the edge from v to its parent.
struct MinOnPaths {
    const Lifting& L;
    vector<vector<long long>> mn;
    MinOnPaths(const Lifting& lifting, const vector<long long>& upWeight) : L(lifting), mn(lifting.up.size(), upWeight) {
        for (size_t j = 1; j < mn.size(); j++)
            for (size_t v = 1; v < upWeight.size(); v++) {
                int mid = L.up[j - 1][v];
                mn[j][v] = mid == 0 ? mn[j - 1][v] : min(mn[j - 1][v], mn[j - 1][mid]);  // the first half, then the second half
            }
    }
    long long query(int u, int v) const {  // INF if u == v
        const long long INF = LLONG_MAX / 4;
        long long best = INF;
        if (L.depth[u] < L.depth[v]) swap(u, v);
        for (int j = 0; j < (int)mn.size(); j++)
            if ((L.depth[u] - L.depth[v]) >> j & 1) best = min(best, mn[j][u]), u = L.up[j][u];  // lift u, collecting the minimum
        if (u == v) return best;
        for (int j = (int)mn.size() - 1; j >= 0; j--)
            if (L.up[j][u] != L.up[j][v]) best = min({best, mn[j][u], mn[j][v]}), u = L.up[j][u], v = L.up[j][v];
        return min({best, mn[0][u], mn[0][v]});  // the last edge on each side
    }
};
// snippet:end

int main() {
    const long long INF = LLONG_MAX / 4;
    auto upWeights = [](const vector<vector<int>>& adj, int root, const vector<array<int, 3>>& edges) {
        int n = adj.size() - 1;
        map<pair<int, int>, long long> w;
        for (auto [a, b, c] : edges) w[{a, b}] = w[{b, a}] = c;
        auto t = rootAt(adj, root);
        vector<long long> up(n + 1, LLONG_MAX / 4);
        for (int v : t.order) if (t.parent[v]) up[v] = w[{v, t.parent[v]}];
        return up;
    };
    {
        vector<array<int, 3>> edges = {{1, 2, 3}, {2, 3, 4}, {2, 4, 1}, {4, 5, 6}, {1, 6, 2}};
        vector<vector<int>> adj(7);
        for (auto [a, b, c] : edges) adj[a].push_back(b), adj[b].push_back(a);
        Lifting L(adj, 1);
        MinOnPaths M(L, upWeights(adj, 1, edges));
        cout << "tree 1-2 (3), 2-3 (4), 2-4 (1), 4-5 (6), 1-6 (2): min(3, 5) = " << M.query(3, 5) << ", min(6, 3) = " << M.query(6, 3) << ", min(3, 2) = " << M.query(3, 2) << ", min(3, 3) = " << (M.query(3, 3) == INF ? string("none") : to_string(M.query(3, 3))) << "\n";
    }
    mt19937 rng(4604);
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
        auto adj = randomWeighted(rng, n, 9, edges);
        Lifting L(adj, root);
        MinOnPaths M(L, upWeights(adj, root, edges));
        // reference: the walk from u to v along the unique path, found by a search that records the smallest weight on the way
        for (int u = 1; u <= n; u++) {
            vector<long long> low(n + 1, -1);
            low[u] = INF;
            vector<int> stack = {u};
            while (!stack.empty()) {
                int x = stack.back();
                stack.pop_back();
                for (auto [a, b, c] : edges) {
                    int y = a == x ? b : (b == x ? a : 0);
                    if (y && low[y] < 0) low[y] = min<long long>(low[x], c), stack.push_back(y);
                }
            }
            for (int v = 1; v <= n; v++) if (M.query(u, v) != low[v]) return 1;
        }
    }
}
