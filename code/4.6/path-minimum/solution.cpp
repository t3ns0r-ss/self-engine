/*
Problem: the weakest road.
Input: n q, then n - 1 lines "a b w": a road with weight limit w (1 <= w <= 10^9) between towns a and b, forming a tree; then q lines "a b" (a != b).
Output: for each query, the smallest limit on the trip between a and b.
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

// snippet:begin
// Theorem 4.6.4. mn[j][v] is the smallest limit on the 2^j roads going up from v (valid when that jump exists). upWeight[v] is the limit of
// the road from v to its parent. Returns the smallest limit between a and b.
struct WeakestRoad {
    const Lifting& L;
    vector<vector<long long>> mn;
    WeakestRoad(const Lifting& lifting, const vector<long long>& upWeight) : L(lifting), mn(lifting.up.size(), upWeight) {
        for (size_t j = 1; j < mn.size(); j++)
            for (size_t v = 1; v < upWeight.size(); v++) {
                int mid = L.up[j - 1][v];
                mn[j][v] = mid == 0 ? mn[j - 1][v] : min(mn[j - 1][v], mn[j - 1][mid]);
            }
    }
    long long query(int a, int b) const {
        long long best = LLONG_MAX;
        if (L.depth[a] < L.depth[b]) swap(a, b);
        for (int j = 0; j < (int)mn.size(); j++)
            if ((L.depth[a] - L.depth[b]) >> j & 1) best = min(best, mn[j][a]), a = L.up[j][a];
        if (a == b) return best;
        for (int j = (int)mn.size() - 1; j >= 0; j--)
            if (L.up[j][a] != L.up[j][b]) best = min({best, mn[j][a], mn[j][b]}), a = L.up[j][a], b = L.up[j][b];
        return min({best, mn[0][a], mn[0][b]});
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    map<pair<int, int>, long long> weight;
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        adj[a].push_back(b);
        adj[b].push_back(a);
        weight[{a, b}] = weight[{b, a}] = w;
    }
    Lifting L(adj, 1);
    auto t = rootAt(adj, 1);
    vector<long long> upWeight(n + 1, LLONG_MAX);
    for (int v : t.order) if (t.parent[v]) upWeight[v] = weight[{v, t.parent[v]}];
    WeakestRoad M(L, upWeight);
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << M.query(a, b) << "\n";
    }
}
