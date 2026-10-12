#include <bits/stdc++.h>
using namespace std;

/*
Problem: a tree of n vertices (n up to 2·10^5) is rooted at the vertex 1. For every vertex print its parent (0 for the root)
and the size of its subtree. The traversal must not use recursion (a path of 2·10^5 vertices would overflow the stack).
Input: n, then the n - 1 edges.
Output: n lines "parent size".
*/


// snippet:begin
// The order of a traversal that visits every parent before its children; going through it backwards visits every child before
// its parent. Then the subtree sizes are made by adding each size to the parent (Theorem 7.1.1, with the sum as the rule).
// (In the code below the struct Rooted is built from the edge list; vertices are counted from 0.)
struct Rooted {
    int n;
    vector<vector<int>> adj, children;
    vector<int> parent, order;
    Rooted(int n, const vector<pair<int, int>>& edges) : n(n), adj(n), children(n), parent(n, -1) {
        for (auto [a, b] : edges) adj[a].push_back(b), adj[b].push_back(a);
        order = {0};
        for (size_t i = 0; i < order.size(); i++) {  // order grows while it is read: a breadth-first search
            int v = order[i];
            for (int u : adj[v])
                if (u != parent[v]) parent[u] = v, children[v].push_back(u), order.push_back(u);
        }
    }
    vector<int> subtreeSizes() const {
        vector<int> size(n, 1);
        for (int i = n - 1; i > 0; i--) size[parent[order[i]]] += size[order[i]];
        return size;
    }
};
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> edges(n - 1);
    for (auto& [a, b] : edges) cin >> a >> b, a--, b--;
    Rooted t(n, edges);
    vector<int> size = t.subtreeSizes();
    for (int v = 0; v < n; v++) cout << t.parent[v] + 1 << " " << size[v] << "\n";
}
