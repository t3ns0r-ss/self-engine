/*
Problem: CSES 1135, Distance Queries.
Input: n q, then n - 1 lines "a b": the roads of a tree; then q lines "a b".
Output: for each query, the number of roads on the trip between a and b.
*/
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
// Theorem 4.6.3. The number of edges between a and b: depth[a] + depth[b] - 2 * depth[lca]. L is the lifting table of the tree rooted at 1.
vector<int> distances(const Lifting& L, const vector<pair<int, int>>& queries) {
    vector<int> answer;
    for (auto [a, b] : queries) answer.push_back(L.depth[a] + L.depth[b] - 2 * L.depth[lca(L, a, b)]);
    return answer;
}
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    Lifting L(adj, 1);
    vector<pair<int, int>> queries(q);
    for (auto& x : queries) cin >> x.first >> x.second;
    for (int d : distances(L, queries)) cout << d << "\n";
}
