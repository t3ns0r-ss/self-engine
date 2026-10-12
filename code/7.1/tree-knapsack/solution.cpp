#include <bits/stdc++.h>
using namespace std;

/*
Problem: a tree of n vertices (n up to 3000) with an integer value on each vertex, and a number k. Print the largest sum of the
values of a connected set of exactly k vertices.
Input: n, k, the n values, then the n - 1 edges.
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
// Theorem 7.1.4: dp[v][j] = the largest sum of a connected set that contains v, lies in the subtree of v and has j vertices.
// A child is merged with a double loop over the sizes; the sum of all such loops is n(n-1)/2. The top vertex of the best set may be any v.
long long bestConnectedSet(const Rooted& t, const vector<long long>& w, int k) {
    const long long NEG = LLONG_MIN / 4;
    vector<vector<long long>> dp(t.n);
    long long best = NEG;
    for (int i = t.n - 1; i >= 0; i--) {
        int v = t.order[i];
        dp[v] = {NEG, w[v]};
        for (int c : t.children[v]) {
            vector<long long> merged(dp[v].size() + dp[c].size() - 1, NEG);
            for (size_t a = 1; a < dp[v].size(); a++) {
                merged[a] = max(merged[a], dp[v][a]);
                for (size_t b = 1; b < dp[c].size(); b++) merged[a + b] = max(merged[a + b], dp[v][a] + dp[c][b]);
            }
            dp[v] = merged;
            vector<long long>().swap(dp[c]);  // the child is finished: free its table
        }
        if ((int)dp[v].size() > k) best = max(best, dp[v][k]);
    }
    return best;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> w(n);
    for (auto& x : w) cin >> x;
    vector<pair<int, int>> edges(n - 1);
    for (auto& [a, b] : edges) cin >> a >> b, a--, b--;
    Rooted t(n, edges);
    cout << bestConnectedSet(t, w, k) << "\n";
}
