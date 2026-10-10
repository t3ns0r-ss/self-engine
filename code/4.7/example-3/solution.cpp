/*
Problem: LeetCode, Critical Connections in a Network.
Input: n m, then m lines "a b" (servers numbered from 0): the connections. Every server can reach every other.
Output: the critical connections, one per line "a b", in the order of the input.
*/
#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<pair<int, int>>>;

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
// Theorem 4.7.2. The edge from a vertex to its parent is a bridge exactly when low[v] > tin[parent]; non-tree edges are never bridges.
vector<int> findBridges(const Graph& adj) {
    LowLink L(adj);
    vector<int> bridges;
    for (int v = 1; v < (int)adj.size(); v++)
        if (L.parent[v] && L.low[v] > L.tin[L.parent[v]]) bridges.push_back(L.parentEdge[v]);
    sort(bridges.begin(), bridges.end());
    return bridges;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    Graph adj(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first++, edges[i].second++;
        adj[edges[i].first].push_back({edges[i].second, i});
        adj[edges[i].second].push_back({edges[i].first, i});
    }
    for (int e : findBridges(adj)) cout << edges[e].first - 1 << " " << edges[e].second - 1 << "\n";
}
