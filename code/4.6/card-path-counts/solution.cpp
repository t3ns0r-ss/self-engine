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
    auto counts = [&](const vector<vector<int>>& adj, const vector<pair<int, int>>& paths) {
        int n = adj.size() - 1;
        auto t = rootAt(adj, 1);
        Lifting L(adj, 1);
        vector<long long> c(n + 1, 0);
        for (auto [u, v] : paths) c[u]++, c[v]++, c[lca(L, u, v)] -= 2;
        for (int i = n - 1; i > 0; i--) c[t.parent[t.order[i]]] += c[t.order[i]];
        return c;
    };
    auto climbing = [&](const vector<vector<int>>& adj, const vector<pair<int, int>>& paths) {
        int n = adj.size() - 1;
        auto t = rootAt(adj, 1);
        vector<long long> e(n + 1, 0);
        for (auto [u, v] : paths) {
            int a = u, b = v;
            while (a != b) {
                if (t.depth[a] >= t.depth[b]) e[a]++, a = t.parent[a];
                else e[b]++, b = t.parent[b];
            }
        }
        return e;
    };
    auto show = [](const vector<long long>& c) { string s; for (size_t v = 2; v < c.size(); v++) s += (v > 2 ? "," : "") + to_string(c[v]); return s; };
    // P1: the tree 1-2, 1-3, 2-4, 2-5, 3-6 and the paths 4-5, 4-6, 5-6: how many paths use the edge above each of 2, ..., 6?
    {
        vector<vector<int>> adj(7);
        auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
        edge(1, 2), edge(1, 3), edge(2, 4), edge(2, 5), edge(3, 6);
        vector<pair<int, int>> paths = {{4, 5}, {4, 6}, {5, 6}};
        cout << "P1 brute=" << show(climbing(adj, paths)) << " method=" << show(counts(adj, paths)) << "\n";
    }
    // P2: the path 1-2-3-4 and the paths 1-4 and 2-3.
    {
        vector<vector<int>> adj(5);
        auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
        edge(1, 2), edge(2, 3), edge(3, 4);
        vector<pair<int, int>> paths = {{1, 4}, {2, 3}};
        cout << "P2 brute=" << show(climbing(adj, paths)) << " method=" << show(counts(adj, paths)) << "\n";
    }
    // N1: the path 1-2-3 and the single path 2-3: how many paths pass through the VERTEX 2? The numbers above count EDGES: the edge above 2 is not used.
    {
        vector<vector<int>> adj(4);
        auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
        edge(1, 2), edge(2, 3);
        vector<pair<int, int>> paths = {{2, 3}};
        auto c = counts(adj, paths);
        int through = 0;  // brute force: does the path contain the vertex 2?
        for (auto [u, v] : paths) through += (u == 2 || v == 2);
        cout << "N1 brute=" << through << " method=" << c[2] << "\n";
    }
}
