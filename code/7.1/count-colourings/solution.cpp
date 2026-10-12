#include <bits/stdc++.h>
using namespace std;

/*
Problem: AtCoder DP P, Independent Set. A tree of n vertices; paint each vertex white or black so that no two black vertices are
adjacent. Print the number of ways modulo M.
Input: n, M, then the n - 1 edges (n up to 10^5).
Output: the number.
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
// Theorem 7.1.1: f[v] = {ways with v white, ways with v black} for the subtree of v, finished children first.
long long countColourings(const Rooted& t, long long M) {
    vector<array<long long, 2>> f(t.n, {1 % M, 1 % M});
    for (int i = t.n - 1; i >= 0; i--) {
        int v = t.order[i];
        for (int c : t.children[v]) {
            f[v][0] = f[v][0] * ((f[c][0] + f[c][1]) % M) % M;
            f[v][1] = f[v][1] * f[c][0] % M;
        }
    }
    return (f[0][0] + f[0][1]) % M;
}
// snippet:end

int main() {
    int n;
    long long M;
    cin >> n >> M;
    vector<pair<int, int>> edges(n - 1);
    for (auto& [a, b] : edges) cin >> a >> b, a--, b--;
    Rooted t(n, edges);
    cout << countColourings(t, M) << "\n";
}
