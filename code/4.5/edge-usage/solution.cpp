/*
Problem: how busy is each road.
Input: n, then n - 1 lines "a b": a road between towns a and b; the roads form a tree.
Output: n - 1 numbers: for each road in the input order, the number of pairs of towns {u, v} (u < v) whose trip uses the road.
*/
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
// Theorem 4.5.6. For every edge (a, b), the number of pairs whose path uses it: s * (n - s), where s is the size of the side below it.
vector<long long> pairsPerEdge(const vector<vector<int>>& adj, const vector<pair<int, int>>& edges) {
    int n = adj.size() - 1;
    auto t = rootAt(adj, 1);
    vector<long long> size(n + 1, 1);
    for (int i = n - 1; i > 0; i--) size[t.parent[t.order[i]]] += size[t.order[i]];
    vector<long long> used;
    for (auto [a, b] : edges) {
        int child = t.parent[a] == b ? a : b;  // the endpoint farther from the root
        used.push_back(size[child] * (n - size[child]));
    }
    return used;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> edges(n - 1);
    for (auto& e : edges) {
        cin >> e.first >> e.second;
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
    auto used = pairsPerEdge(adj, edges);
    for (size_t i = 0; i < used.size(); i++) cout << used[i] << (i + 1 < used.size() ? " " : "\n");
    if (n == 1) cout << "\n";
}
