/*
Problem: is the town on the way?
Input: n q, then n - 1 lines "a b w": a road of length w (1 <= w <= 10^9) between towns a and b, forming a tree; then q lines "a b c".
Output: for each query YES if town c lies on the trip between a and b, otherwise NO.
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
// Theorem 4.6.3. c is on the path between a and b exactly when d(a, c) + d(c, b) = d(a, b). wd[v] is the weighted depth of v.
bool onTheWay(const Lifting& L, const vector<long long>& wd, int a, int b, int c) {
    auto dist = [&](int u, int v) { return wd[u] + wd[v] - 2 * wd[lca(L, u, v)]; };
    return dist(a, c) + dist(c, b) == dist(a, b);
}
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    map<pair<int, int>, long long> weight;
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        adj[a].push_back(b);
        adj[b].push_back(a);
        weight[{a, b}] = weight[{b, a}] = w;
    }
    Lifting L(adj, 1);
    auto t = rootAt(adj, 1);
    vector<long long> wd(n + 1, 0);
    for (int v : t.order) if (t.parent[v]) wd[v] = wd[t.parent[v]] + weight[{v, t.parent[v]}];
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << (onTheWay(L, wd, a, b, c) ? "YES" : "NO") << "\n";
    }
}
