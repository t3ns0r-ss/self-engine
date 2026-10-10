/*
Problem: how often is each road used.
Input: n q, then n - 1 lines "a b": the roads of a tree; then q lines "a b": a trip from town a to town b.
Output: n - 1 numbers: for each road in the input order, the number of trips that use it.
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

int lca(const Lifting& L, int u, int v) {
    if (L.depth[u] < L.depth[v]) swap(u, v);
    u = L.kthAncestor(u, L.depth[u] - L.depth[v]);
    if (u == v) return u;
    for (int j = (int)L.up.size() - 1; j >= 0; j--)
        if (L.up[j][u] != L.up[j][v]) u = L.up[j][u], v = L.up[j][v];  // still below the meeting point: take the jump
    return L.up[0][u];
}

// snippet:begin
// Theorem 4.6.5. +1 at both ends of each trip, -2 at the lowest common ancestor, then subtree sums: count[v] is the number of trips using
// the road from v to its parent. Returns the counts for the roads in the input order.
vector<long long> tripsPerRoad(const vector<vector<int>>& adj, const vector<pair<int, int>>& roads, const vector<pair<int, int>>& trips) {
    int n = adj.size() - 1;
    Rooted t = rootAt(adj, 1);
    Lifting L(adj, 1);
    vector<long long> count(n + 1, 0);
    for (auto [a, b] : trips) count[a]++, count[b]++, count[lca(L, a, b)] -= 2;
    for (int i = n - 1; i > 0; i--) count[t.parent[t.order[i]]] += count[t.order[i]];
    vector<long long> answer;
    for (auto [a, b] : roads) answer.push_back(count[t.parent[a] == b ? a : b]);  // the lower end of the road
    return answer;
}
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> roads(n - 1), trips(q);
    for (auto& e : roads) {
        cin >> e.first >> e.second;
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
    for (auto& x : trips) cin >> x.first >> x.second;
    auto answer = tripsPerRoad(adj, roads, trips);
    for (size_t i = 0; i < answer.size(); i++) cout << answer[i] << (i + 1 < answer.size() ? " " : "\n");
    if (n == 1) cout << "\n";
}
