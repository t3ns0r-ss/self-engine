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
// Theorem 4.6.5. Many paths {u, v} are known in advance. Returns, for every vertex v other than the root, the number of paths that use
// the edge between v and its parent: +1 at u and at v, -2 at their lowest common ancestor, then the sums over the subtrees.
vector<long long> pathsPerEdge(const vector<vector<int>>& adj, int root, const vector<pair<int, int>>& paths) {
    int n = adj.size() - 1;
    Rooted t = rootAt(adj, root);
    Lifting L(adj, root);
    vector<long long> count(n + 1, 0);
    for (auto [u, v] : paths) count[u]++, count[v]++, count[lca(L, u, v)] -= 2;
    for (int i = n - 1; i > 0; i--) count[t.parent[t.order[i]]] += count[t.order[i]];  // the subtree sums of Theorem 4.5.2
    return count;
}
// snippet:end

int main() {
    {
        vector<vector<int>> adj(7);
        auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
        edge(1, 2), edge(1, 3), edge(2, 4), edge(2, 5), edge(3, 6);
        auto c = pathsPerEdge(adj, 1, {{4, 5}, {4, 6}, {5, 6}});
        cout << "tree 1-2, 1-3, 2-4, 2-5, 3-6, paths 4-5, 4-6, 5-6: edge to parent of 2..6 used by";
        for (int v = 2; v <= 6; v++) cout << ' ' << c[v];
        cout << "\n";
        auto e = pathsPerEdge(adj, 1, {});
        cout << "no paths:";
        for (int v = 2; v <= 6; v++) cout << ' ' << e[v];
        cout << "\n";
    }
    mt19937 rng(4605);
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
        int n = rng() % 12 + 1, root = rng() % n + 1, q = rng() % 6;
        auto adj = randomTree(rng, n);
        vector<pair<int, int>> paths;
        for (int i = 0; i < q; i++) paths.push_back({(int)(rng() % n + 1), (int)(rng() % n + 1)});
        auto got = pathsPerEdge(adj, root, paths);
        auto t = rootAt(adj, root);
        // reference: climb from both ends of each path, counting every edge on the way
        vector<long long> expected(n + 1, 0);
        for (auto [u, v] : paths) {
            int a = u, b = v;
            while (a != b) {
                if (t.depth[a] >= t.depth[b]) expected[a]++, a = t.parent[a];
                else expected[b]++, b = t.parent[b];
            }
        }
        for (int v = 1; v <= n; v++) if (v != root && got[v] != expected[v]) return 1;
    }
}
