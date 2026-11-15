#include <bits/stdc++.h>
using namespace std;

/*
Problem: a tree of n vertices (n up to 2·10^5) whose edges are directed. For every vertex v, the fewest edges to reverse so that
every vertex can be reached from v.
Input: n, then n - 1 lines "u v" meaning the edge u -> v.
Output: the n answers on one line.
*/

// snippet:begin
// Theorem 7.2.3. edges[i] = {u, v} is the directed edge u -> v of a tree. r[v] = the fewest edges to reverse so that every
// vertex can be reached from v: the number of edges that point toward v.
vector<int> reversalsFromEach(int n, const vector<pair<int, int>>& edges) {
    vector<vector<pair<int, int>>> adj(n);  // (neighbour, +1 if the edge leaves this vertex, -1 if it enters it)
    for (auto [u, v] : edges) adj[u].push_back({v, 1}), adj[v].push_back({u, -1});
    vector<int> r(n, 0), parent(n, -1), step(n, 0), order = {0};
    for (size_t i = 0; i < order.size(); i++) {
        int p = order[i];
        for (auto [c, dir] : adj[p]) {
            if (c == parent[p]) continue;
            parent[c] = p, step[c] = dir, order.push_back(c);
            if (dir < 0) r[0]++;  // the edge c -> p points toward the root 0
        }
    }
    for (int i = 1; i < n; i++) r[order[i]] = r[parent[order[i]]] + step[order[i]];  // one edge changes its meaning
    return r;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> edges(n - 1);
    for (auto& [u, v] : edges) cin >> u >> v, u--, v--;
    vector<int> r = reversalsFromEach(n, edges);
    for (int v = 0; v < n; v++) cout << r[v] << (v + 1 < n ? " " : "\n");
}
