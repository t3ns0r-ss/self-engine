#include <bits/stdc++.h>
using namespace std;

/*
Problem: a tree of n vertices (n up to 2·10^5) with an integer value on each vertex (|value| up to 10^9). Print the largest
sum of values on a path (a path may be a single vertex).
Input: n, the n values, then the n - 1 edges.
Output: the sum.
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
// Theorem 7.1.2: down[v] = the best path that starts at v and goes down; the best path whose top is v adds the two best
// child paths (a child path below 0 is left out).
long long bestPath(const Rooted& t, const vector<long long>& w) {
    vector<long long> down(t.n);
    long long best = LLONG_MIN;
    for (int i = t.n - 1; i >= 0; i--) {
        int v = t.order[i];
        long long top1 = 0, top2 = 0;
        for (int c : t.children[v]) {
            long long d = max(0LL, down[c]);
            if (d > top1) top2 = top1, top1 = d;
            else top2 = max(top2, d);
        }
        down[v] = w[v] + top1;
        best = max(best, w[v] + top1 + top2);
    }
    return best;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> w(n);
    for (auto& x : w) cin >> x;
    vector<pair<int, int>> edges(n - 1);
    for (auto& [a, b] : edges) cin >> a >> b, a--, b--;
    Rooted t(n, edges);
    cout << bestPath(t, w) << "\n";
}
