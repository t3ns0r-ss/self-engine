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

// snippet:begin
// Theorem 4.6.1. The table of the 2^j-th ancestors, and the k-th ancestor from the binary digits of k. Vertices are 1..n, 0 means "none".
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
// snippet:end

int main() {
    {
        vector<vector<int>> adj(9);
        auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
        edge(1, 2), edge(2, 3), edge(3, 4), edge(4, 5), edge(5, 6), edge(2, 7), edge(7, 8);
        Lifting L(adj, 1);
        cout << "path 1-2-3-4-5-6 with 2-7-8, rooted at 1: ancestors of 6 at k = 0..6:";
        for (int k = 0; k <= 6; k++) cout << ' ' << L.kthAncestor(6, k);
        cout << "\n";
        cout << "4th ancestor of 8: " << L.kthAncestor(8, 4) << ", 2nd ancestor of 8: " << L.kthAncestor(8, 2) << ", table levels: " << L.up.size() << "\n";
    }
    {
        vector<vector<int>> adj(2);
        Lifting L(adj, 1);
        cout << "one vertex: 0th ancestor " << L.kthAncestor(1, 0) << ", 1st ancestor " << L.kthAncestor(1, 1) << "\n";
    }
    // Check against: climbing the parents k times, on random trees.
    mt19937 rng(4601);
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
        for (int v = 1; v <= n; v++)
            for (int k = 0; k <= n + 1; k++) {
                int x = v;
                for (int i = 0; i < k && x != 0; i++) x = t.parent[x];
                if (L.kthAncestor(v, k) != x) return 1;
            }
    }
}
