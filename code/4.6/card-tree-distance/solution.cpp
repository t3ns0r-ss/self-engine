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

int main() {
    // P1: the weighted tree 1-2 (3), 2-3 (4), 2-4 (1), 4-5 (6), 1-6 (2); the distance between 3 and 5. Brute force: Floyd-Warshall.
    {
        vector<array<int, 3>> edges = {{1, 2, 3}, {2, 3, 4}, {2, 4, 1}, {4, 5, 6}, {1, 6, 2}};
        int n = 6;
        vector<vector<int>> adj(n + 1);
        const long long INF = 1e9;
        vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));
        for (int v = 1; v <= n; v++) d[v][v] = 0;
        for (auto [a, b, w] : edges) adj[a].push_back(b), adj[b].push_back(a), d[a][b] = d[b][a] = w;
        for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        Lifting L(adj, 1);
        auto t = rootAt(adj, 1);
        vector<long long> wd(n + 1, 0);
        for (int v : t.order) if (t.parent[v]) for (auto [a, b, w] : edges) if ((a == v && b == t.parent[v]) || (b == v && a == t.parent[v])) wd[v] = wd[t.parent[v]] + w;
        cout << "P1 brute=" << d[3][5] << " method=" << wd[3] + wd[5] - 2 * wd[lca(L, 3, 5)] << "\n";
    }
    // P2: the tree 1-2, 1-3, 3-4, 3-5 and the questions (1, 3), (2, 5), (1, 4). Brute force: a walk from each first vertex.
    {
        vector<vector<int>> adj(6);
        auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
        edge(1, 2), edge(1, 3), edge(3, 4), edge(3, 5);
        Lifting L(adj, 1);
        string brute, method;
        for (auto [a, b] : vector<pair<int, int>>{{1, 3}, {2, 5}, {1, 4}}) {
            auto t = rootAt(adj, a);
            brute += (brute.empty() ? "" : ",") + to_string(t.depth[b]);
            method += (method.empty() ? "" : ",") + to_string(L.depth[a] + L.depth[b] - 2 * L.depth[lca(L, a, b)]);
        }
        cout << "P2 brute=" << brute << " method=" << method << "\n";
    }
    // N1: the triangle 1-2, 2-3, 1-3 (every edge 1). The tree of a walk from vertex 1 has the edges 1-2 and 1-3, so the formula
    // says d(2, 3) = 1 + 1 - 0 = 2, but the edge 2-3 gives 1.
    {
        // the formula on the tree {1-2, 1-3} rooted at 1
        vector<vector<int>> tree(4);
        tree[1] = {2, 3}, tree[2] = {1}, tree[3] = {1};
        Lifting L(tree, 1);
        cout << "N1 brute=1 method=" << L.depth[2] + L.depth[3] - 2 * L.depth[lca(L, 2, 3)] << "\n";
    }
}
