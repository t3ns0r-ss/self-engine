/*
Problem: one-way streets.
Input: n m, then m lines "a b": a two-way street. The intersections are connected.
Output: POSSIBLE if every street can be made one-way so that one can drive from any intersection to any other, otherwise IMPOSSIBLE.
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

// Theorem 4.7.4. Label the pieces of the walk tree left after cutting the bridges (they are the 2-edge-connected components), and
// orient every edge: tree edges downwards, back edges upwards. If the graph is connected and has no bridge, the result is strongly connected.
vector<int> edgeComponents(const Graph& adj, int& count) {
    LowLink L(adj);
    vector<int> comp(adj.size(), 0);
    count = 0;
    for (int v : L.order) {  // parents come before children
        int p = L.parent[v];
        comp[v] = (p && L.low[v] <= L.tin[p]) ? comp[p] : ++count;  // the edge above v is not a bridge: same piece as the parent
    }
    return comp;
}
vector<pair<int, int>> orientEdges(const Graph& adj, int m) {
    LowLink L(adj);
    vector<pair<int, int>> direction(m);  // (from, to) for each edge number
    for (int v = 1; v < (int)adj.size(); v++)
        for (auto [to, id] : adj[v])
            if (L.parentEdge[to] == id || (L.parentEdge[v] != id && L.tin[v] > L.tin[to])) direction[id] = {v, to};
    return direction;
}

// snippet:begin
// Theorem 4.7.4 (c). It is possible exactly when no street is a bridge.
bool canMakeOneWay(const Graph& adj) {
    LowLink L(adj);
    for (int v = 1; v < (int)adj.size(); v++)
        if (L.parent[v] && L.low[v] > L.tin[L.parent[v]]) return false;
    return true;
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
    bool possible = canMakeOneWay(adj);
    if (possible) {  // build the orientation of Theorem 4.7.4 and check it: from town 1 and back to town 1 every town is reached
        auto direction = orientEdges(adj, m);
        Digraph forward(n + 1), backward(n + 1);
        for (auto [a, b] : direction) forward[a].push_back(b), backward[b].push_back(a);
        for (auto* g : {&forward, &backward}) {
            vector<bool> seen(n + 1, false);
            vector<int> stack = {1};
            seen[1] = true;
            while (!stack.empty()) {
                int v = stack.back();
                stack.pop_back();
                for (int u : (*g)[v])
                    if (!seen[u]) seen[u] = true, stack.push_back(u);
            }
            for (int v = 1; v <= n; v++)
                if (!seen[v]) return 1;
        }
    }
    cout << (possible ? "POSSIBLE" : "IMPOSSIBLE") << "\n";
}
