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

int main() {
    // P1: the 5th ancestor of vertex 6 in the tree 1-2-3-4-5-6 (with 2-7-8), rooted at 1. Brute force: climb five parents.
    {
        vector<vector<int>> adj(9);
        auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
        edge(1, 2), edge(2, 3), edge(3, 4), edge(4, 5), edge(5, 6), edge(2, 7), edge(7, 8);
        Lifting L(adj, 1);
        auto t = rootAt(adj, 1);
        int x = 6;
        for (int i = 0; i < 5; i++) x = t.parent[x];
        cout << "P1 brute=" << x << " method=" << L.kthAncestor(6, 5) << "\n";
    }
    // P2: four planets with teleporters 1->2, 2->1, 3->1, 4->4; start on planet 3 and use 4 teleporters. Brute force: simulate.
    {
        vector<int> next = {0, 2, 1, 1, 4};
        int n = 4;
        vector<vector<int>> up(3, next);  // k <= 4 < 2^3
        for (int j = 1; j < 3; j++) for (int v = 1; v <= n; v++) up[j][v] = up[j - 1][up[j - 1][v]];
        int simulated = 3, jumped = 3, k = 4;
        for (int i = 0; i < k; i++) simulated = next[simulated];
        for (int j = 0; j < 3; j++) if (k >> j & 1) jumped = up[j][jumped];
        cout << "P2 brute=" << simulated << " method=" << jumped << "\n";
    }
    // N1: the teleporter depends on the number of the step: on odd steps use t = (1->2, 2->3, 3->1), on even steps use u = (everything to 1).
    // From planet 1 after 2 steps the true place is 1; one table for t alone says 3.
    {
        vector<int> t = {0, 2, 3, 1}, u = {0, 1, 1, 1};
        int x = 1;
        for (int step = 1; step <= 2; step++) x = (step % 2 == 1) ? t[x] : u[x];
        int y = 1;
        for (int j = 0; j < 2; j++) y = t[y];  // what a table of t alone gives for 2 steps
        cout << "N1 brute=" << x << " method=" << y << "\n";
    }
}
