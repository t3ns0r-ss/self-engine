#include <bits/stdc++.h>
using namespace std;

/*
Problem: a directed acyclic graph of n vertices and m edges (up to 2·10^5) with a weight 1 to 10^9 on each edge. Among the paths from the
vertex 1 to the vertex n find the least total weight and the number of paths with that weight, modulo 10^9 + 7.
Input: n, m, then the m edges "a b w".
Output: "weight count", or IMPOSSIBLE if there is no path.
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
// Theorem 7.2.2: the least weight and the number of ways to reach it are kept together. A better weight replaces the pair, an equal
// weight adds the numbers of ways.
pair<long long, long long> cheapestPaths(const vector<vector<pair<int, int>>>& out, const vector<int>& order) {
    const long long MOD = 1000000007;
    int n = out.size();
    vector<long long> cost(n, LLONG_MAX), ways(n, 0);
    cost[0] = 0, ways[0] = 1;
    for (int v : order) {
        if (cost[v] == LLONG_MAX) continue;  // not reachable from the vertex 0
        for (auto [u, w] : out[v]) {
            if (cost[v] + w < cost[u]) cost[u] = cost[v] + w, ways[u] = ways[v];
            else if (cost[v] + w == cost[u]) ways[u] = (ways[u] + ways[v]) % MOD;
        }
    }
    return {cost[n - 1], ways[n - 1]};
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
    auto [cost, ways] = cheapestPaths(out, topologicalOrder(out, indeg));
    if (cost == LLONG_MAX) cout << "IMPOSSIBLE\n";
    else cout << cost << " " << ways << "\n";
}
