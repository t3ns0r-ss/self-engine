#include <bits/stdc++.h>
using namespace std;

/*
Problem: AtCoder ABC 259 F, Select Edges. A tree of N vertices (N up to 3·10^5) with a weight on each edge (|weight| up to 10^9) and a
number d_i for each vertex. Choose some edges so that at most d_i chosen edges touch the vertex i; print the largest total weight.
Input: N, d_1 ... d_N, then the N - 1 edges "u v w".
Output: the largest total (it needs 64 bits).
*/

struct Rooted {
    int n;
    vector<vector<int>> adj, children;
    vector<int> parent, order;
    Rooted(int n, const vector<pair<int, int>>& edges) : n(n), adj(n), children(n), parent(n, -1) {
        for (auto [a, b] : edges) adj[a].push_back(b), adj[b].push_back(a);
        order = {0};
        for (size_t i = 0; i < order.size(); i++) {
            int v = order[i];
            for (int u : adj[v])
                if (u != parent[v]) parent[u] = v, children[v].push_back(u), order.push_back(u);
        }
    }
};

// snippet:begin
// Theorem 7.1.1 with two states. f0[v]: the best inside the subtree of v when v may use d[v] edges to its children.
// f1[v]: the same when v may use only d[v] - 1 of them, because the edge to its parent is taken.
// A child c is worth taking at v when f1[c] + w - f0[c] is positive; v takes the best such gains, at most d[v] (or d[v] - 1) of them.
long long selectEdges(const Rooted& t, const vector<int>& d, const vector<long long>& weightToParent) {
    vector<long long> f0(t.n, 0), f1(t.n, 0);
    for (int i = t.n - 1; i >= 0; i--) {
        int v = t.order[i];
        long long base = 0;
        vector<long long> gains;
        for (int c : t.children[v]) {
            base += f0[c];
            if (d[c] > 0 && f1[c] + weightToParent[c] - f0[c] > 0) gains.push_back(f1[c] + weightToParent[c] - f0[c]);
        }
        sort(gains.rbegin(), gains.rend());
        f0[v] = f1[v] = base;
        for (int j = 0; j < (int)gains.size(); j++) {
            if (j < d[v]) f0[v] += gains[j];
            if (j < d[v] - 1) f1[v] += gains[j];
        }
    }
    return f0[0];
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> d(n);
    for (int& x : d) cin >> x;
    vector<pair<int, int>> edges(n - 1);
    vector<long long> weight(n - 1);
    for (int i = 0; i + 1 < n; i++) cin >> edges[i].first >> edges[i].second >> weight[i], edges[i].first--, edges[i].second--;
    Rooted t(n, edges);
    vector<long long> weightToParent(n, 0);
    for (int i = 0; i + 1 < n; i++) {
        auto [a, b] = edges[i];
        weightToParent[t.parent[b] == a ? b : a] = weight[i];
    }
    cout << selectEdges(t, d, weightToParent) << "\n";
}
