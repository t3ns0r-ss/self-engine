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

// snippet:begin
// Theorem 4.6.2. The lowest common ancestor of u and v: lift the deeper vertex to the depth of the other, then jump from the largest
// jump to the smallest whenever the two ancestors reached are different; the parent of the stopping point is the answer.
int lca(const Lifting& L, int u, int v) {
    if (L.depth[u] < L.depth[v]) swap(u, v);
    u = L.kthAncestor(u, L.depth[u] - L.depth[v]);
    if (u == v) return u;
    for (int j = (int)L.up.size() - 1; j >= 0; j--)
        if (L.up[j][u] != L.up[j][v]) u = L.up[j][u], v = L.up[j][v];  // still below the meeting point: take the jump
    return L.up[0][u];
}
// snippet:end

int main() {
    {
        vector<vector<int>> adj(9);
        auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
        edge(1, 2), edge(2, 3), edge(3, 4), edge(4, 5), edge(5, 6), edge(2, 7), edge(7, 8);
        Lifting L(adj, 1);
        cout << "same tree: lca(6, 8) = " << lca(L, 6, 8) << ", lca(6, 4) = " << lca(L, 6, 4) << ", lca(8, 7) = " << lca(L, 8, 7) << ", lca(5, 5) = " << lca(L, 5, 5) << "\n";
    }
    {
        vector<vector<int>> adj(2);
        Lifting L(adj, 1);
        cout << "one vertex: lca(1, 1) = " << lca(L, 1, 1) << "\n";
    }
    // Check against: marking the ancestors of u by climbing, then climbing from v to the first marked vertex.
    mt19937 rng(4602);
    auto randomTree = [](mt19937& rng, int n) {
        vector<int> label(n);
        iota(label.begin(), label.end(), 1);
        shuffle(label.begin(), label.end(), rng);
        vector<vector<int>> adj(n + 1);
        for (int i = 1; i < n; i++) {
            int a = label[i], b = label[rng() % i];
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        return adj;
    };
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 12 + 1, root = rng() % n + 1;
        auto adj = randomTree(rng, n);
        Lifting L(adj, root);
        auto t = rootAt(adj, root);
        for (int u = 1; u <= n; u++)
            for (int v = 1; v <= n; v++) {
                vector<bool> mark(n + 1, false);
                for (int x = u; x != 0; x = t.parent[x]) mark[x] = true;
                int x = v;
                while (!mark[x]) x = t.parent[x];
                if (lca(L, u, v) != x) return 1;
            }
    }
}
