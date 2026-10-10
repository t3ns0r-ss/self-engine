/*
Problem: towns cut off.
Input: n m, then m lines "a b": a two-way road. The towns are connected.
Output: m numbers, in the order of the roads: when the road is closed, how many towns can no longer be reached from town 1 (0 if all can).
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
// Theorem 4.7.2 with subtree sizes (topic 4.5). Closing a bridge cuts off its lower part, whose size is the size of the subtree below it.
vector<int> townsCutOff(const Graph& adj, int m) {
    LowLink L(adj);
    int n = adj.size() - 1;
    vector<int> size(n + 1, 1), cutOff(m, 0);
    for (int i = n - 1; i > 0; i--) size[L.parent[L.order[i]]] += size[L.order[i]];
    for (int v = 2; v <= n; v++)
        if (L.low[v] > L.tin[L.parent[v]]) cutOff[L.parentEdge[v]] = size[v];
    return cutOff;
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
    auto cutOff = townsCutOff(adj, m);
    for (int i = 0; i < m; i++) cout << cutOff[i] << (i + 1 < m ? ' ' : '\n');
    if (m == 0) cout << "\n";
}
