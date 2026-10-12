#include <bits/stdc++.h>
using namespace std;

/*
Problem: a directed acyclic graph of n vertices and m edges (up to 2·10^5) with an integer weight on each edge (|weight| up to 10^9).
Print the largest total weight of a path (a path may have no edge: the total 0).
Input: n, m, then the m edges "a b w".
Output: the largest total (it needs 64 bits).
*/

vector<int> topologicalOrder(const vector<vector<pair<int, int>>>& out, vector<int> indeg) {
    int n = out.size();
    vector<int> order;
    for (int v = 0; v < n; v++)
        if (indeg[v] == 0) order.push_back(v);
    for (size_t i = 0; i < order.size(); i++)
        for (auto [u, w] : out[order[i]])
            if (--indeg[u] == 0) order.push_back(u);
    return order;
}

// snippet:begin
// Theorem 7.2.1: dp[v] = the largest total of a path that ends at v (at least 0, the path that starts at v); the edges into v are all
// processed before v is used, because the vertices are taken in a topological order.
long long longestPath(const vector<vector<pair<int, int>>>& out, const vector<int>& order) {
    vector<long long> dp(out.size(), 0);
    long long best = 0;
    for (int v : order) {
        best = max(best, dp[v]);
        for (auto [u, w] : out[v]) dp[u] = max(dp[u], dp[v] + w);
    }
    return best;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> out(n);
    vector<int> indeg(n, 0);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        out[a - 1].push_back({b - 1, w}), indeg[b - 1]++;
    }
    cout << longestPath(out, topologicalOrder(out, indeg)) << "\n";
}
