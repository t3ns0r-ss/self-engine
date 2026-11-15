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

int main() {
    vector<vector<int>> adj(6);
    auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
    edge(1, 2), edge(1, 3), edge(3, 4), edge(3, 5);
    auto subtreeSizes = [](const vector<vector<int>>& g, int root, vector<int>& tin, vector<int>& tout) {
        auto t = rootAt(g, root);
        int n = t.order.size();
        vector<int> size(n + 1, 1);
        tin.assign(n + 1, 0), tout.assign(n + 1, 0);
        for (int i = 0; i < n; i++) tin[t.order[i]] = i;
        for (int i = n - 1; i > 0; i--) size[t.parent[t.order[i]]] += size[t.order[i]];
        for (int v = 1; v <= n; v++) tout[v] = tin[v] + size[v] - 1;
        return t;
    };
    vector<int> tin, tout;
    auto t = subtreeSizes(adj, 1, tin, tout);
    // P1: is vertex 3 an ancestor of vertex 4, and of vertex 2? Brute force: climb the parents.
    {
        auto climb = [&](int u, int v) { for (int x = v; x != 0; x = t.parent[x]) if (x == u) return true; return false; };
        auto range = [&](int u, int v) { return tin[u] <= tin[v] && tin[v] <= tout[u]; };
        auto word = [](bool b) { return b ? "yes" : "no"; };
        cout << "P1 brute=" << word(climb(3, 4)) << "," << word(climb(3, 2)) << " method=" << word(range(3, 4)) << "," << word(range(3, 2)) << "\n";
    }
    // N1: how many vertices does the subtree of vertex 3 have when the tree is rooted at vertex 4 (not at vertex 1)?
    // The ranges were made for the root 1: they say 3.
    {
        vector<int> a, b;
        subtreeSizes(adj, 4, a, b);
        int brute = b[3] - a[3] + 1;                 // the ranges recomputed for the root 4
        int method = tout[3] - tin[3] + 1;           // the ranges made for the root 1
        cout << "N1 brute=" << brute << " method=" << method << "\n";
    }
}
