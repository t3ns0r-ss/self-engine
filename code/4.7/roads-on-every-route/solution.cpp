/*
Problem: roads on every route.
Input: n m, then m lines "a b": a two-way road. The towns are connected.
Output: the number of roads that lie on every route from town 1 to town n.
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
// Theorem 4.7.2 and subtree sizes (topic 4.5). A bridge lies on every route from the first town to the target exactly when the target is in the
// subtree below it. The walk starts at town 1, and the entry times of a subtree are tin[v] .. tin[v] + size[v] - 1.
int roadsOnEveryRoute(const Graph& adj, int target) {
    LowLink L(adj);
    int n = adj.size() - 1, count = 0;
    vector<int> size(n + 1, 1);
    for (int i = n - 1; i > 0; i--) size[L.parent[L.order[i]]] += size[L.order[i]];  // children before parents
    for (int v = 2; v <= n; v++)
        if (L.low[v] > L.tin[L.parent[v]] && L.tin[v] <= L.tin[target] && L.tin[target] < L.tin[v] + size[v]) count++;
    return count;
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
    cout << roadsOnEveryRoute(adj, n) << "\n";
}
