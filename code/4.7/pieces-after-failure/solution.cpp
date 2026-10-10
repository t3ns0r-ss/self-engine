/*
Problem: pieces after a failure.
Input: n m, then m lines "a b": a two-way cable. The machines are connected.
Output: n numbers: for each machine, the number of connected pieces the other machines fall into when it fails (0 when there are no other machines).
*/
#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<pair<int, int>>>;
using Digraph = vector<vector<int>>;

// Theorem 4.7.1. adj[v] holds (neighbour, edge number) pairs, vertices are 1..n, edges 0..m-1 (parallel edges differ); parentEdge is -1 at a root.
struct LowLink {
    vector<int> tin, low, parent, parentEdge, order;
    LowLink(const vector<vector<pair<int, int>>>& adj) {
        int n = adj.size() - 1, timer = 0;
        tin.assign(n + 1, -1), low.assign(n + 1, 0), parent.assign(n + 1, 0), parentEdge.assign(n + 1, -1);
        vector<int> next(n + 1, 0);  // next[v]: how many neighbours of v were looked at
        for (int root = 1; root <= n; root++) {
            if (tin[root] != -1) continue;
            vector<int> stack = {root};
            tin[root] = low[root] = timer++, order.push_back(root);
            while (!stack.empty()) {
                int v = stack.back();
                if (next[v] < (int)adj[v].size()) {
                    auto [to, id] = adj[v][next[v]++];
                    if (id == parentEdge[v]) continue;  // the edge we came by, not a second one to the parent
                    if (tin[to] != -1) low[v] = min(low[v], tin[to]);  // a back edge
                    else {
                        parent[to] = v, parentEdge[to] = id;
                        tin[to] = low[to] = timer++, order.push_back(to);
                        stack.push_back(to);
                    }
                } else {
                    stack.pop_back();
                    if (parent[v]) low[parent[v]] = min(low[parent[v]], low[v]);  // the subtree of v is done
                }
            }
        }
    }
};


// snippet:begin
// Theorem 4.7.3, counted. Without a vertex v that is not the first of the walk, the part outside its subtree is one piece and every child c with
// low[c] >= tin[v] is a piece of its own; without the first vertex, every child subtree is a piece.
vector<int> piecesAfterFailure(const Graph& adj) {
    LowLink L(adj);
    int n = adj.size() - 1;
    vector<int> children(n + 1, 0), cutOff(n + 1, 0), pieces(n + 1, 0);
    for (int c = 1; c <= n; c++) {
        int p = L.parent[c];
        if (!p) continue;
        children[p]++;
        if (L.parent[p] && L.low[c] >= L.tin[p]) cutOff[p]++;
    }
    for (int v = 1; v <= n; v++) pieces[v] = L.parent[v] ? 1 + cutOff[v] : children[v];
    return pieces;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    Graph adj(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
        adj[edges[i].first].push_back({edges[i].second, i});
        adj[edges[i].second].push_back({edges[i].first, i});
    }
    auto pieces = piecesAfterFailure(adj);
    for (int v = 1; v <= n; v++) cout << pieces[v] << (v < n ? ' ' : '\n');
}
