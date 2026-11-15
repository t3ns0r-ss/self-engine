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
    vector<vector<int>> adj(9);
    auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
    edge(1, 2), edge(2, 3), edge(3, 4), edge(4, 5), edge(5, 6), edge(2, 7), edge(7, 8);
    Lifting L(adj, 1);
    auto t = rootAt(adj, 1);
    auto byMarking = [&](const Rooted& r, int u, int v) {  // brute force: mark the ancestors of u, climb from v to the first marked one
        vector<bool> mark(adj.size(), false);
        for (int x = u; x != 0; x = r.parent[x]) mark[x] = true;
        int x = v;
        while (!mark[x]) x = r.parent[x];
        return x;
    };
    // P1: the lowest common ancestor of 6 and 8.
    cout << "P1 brute=" << byMarking(t, 6, 8) << " method=" << lca(L, 6, 8) << "\n";
    // P2: the lowest common ancestor of 8 and 7: vertex 7 is an ancestor of 8, so it is its own answer.
    cout << "P2 brute=" << byMarking(t, 8, 7) << " method=" << lca(L, 8, 7) << "\n";
    // N1: the tree 1-2, 1-3, 3-4, 3-5; the lowest common ancestor of 2 and 5 when the tree is rooted at vertex 4 (the table was made for the root 1).
    {
        vector<vector<int>> g(6);
        auto e = [&](int a, int b) { g[a].push_back(b), g[b].push_back(a); };
        e(1, 2), e(1, 3), e(3, 4), e(3, 5);
        Lifting root1(g, 1);
        auto rooted4 = rootAt(g, 4);
        vector<bool> mark(6, false);
        for (int x = 2; x != 0; x = rooted4.parent[x]) mark[x] = true;
        int x = 5;
        while (!mark[x]) x = rooted4.parent[x];
        cout << "N1 brute=" << x << " method=" << lca(root1, 2, 5) << "\n";
    }
}
