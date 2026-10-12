#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1680, Longest Flight Route. A directed acyclic graph of n cities and m flights (n up to 10^5, m up to 2·10^5). Find a route
from the city 1 to the city n through the largest number of cities. Print that number and the route, or IMPOSSIBLE.
(This program prints the route in which every city has the smallest possible predecessor, so that the answer is unique.)
Input: n, m, then the flights "a b".
*/

vector<int> topologicalOrder(const vector<vector<int>>& out, vector<int> indeg) {
    int n = out.size();
    vector<int> order;
    for (int v = 0; v < n; v++)
        if (indeg[v] == 0) order.push_back(v);
    for (size_t i = 0; i < order.size(); i++)
        for (int u : out[order[i]])
            if (--indeg[u] == 0) order.push_back(u);
    return order;
}

// snippet:begin
// Theorem 7.2.1: dp[v] = the largest number of cities on a route from the city 0 to v (or -1 if v cannot be reached), and
// before[v] = the smallest city u with an edge u -> v and dp[u] + 1 = dp[v], from which the route is read backwards.
vector<int> longestRoute(const vector<vector<int>>& out, const vector<int>& order) {
    int n = out.size();
    vector<int> dp(n, -1), before(n, -1);
    dp[0] = 1;
    for (int v : order) {
        if (dp[v] < 0) continue;
        for (int u : out[v]) {
            if (dp[v] + 1 > dp[u]) dp[u] = dp[v] + 1, before[u] = v;
            else if (dp[v] + 1 == dp[u]) before[u] = min(before[u], v);
        }
    }
    vector<int> route;
    if (dp[n - 1] < 0) return route;
    for (int v = n - 1; v >= 0; v = before[v]) route.push_back(v);
    reverse(route.begin(), route.end());
    return route;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> out(n);
    vector<int> indeg(n, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        out[a - 1].push_back(b - 1), indeg[b - 1]++;
    }
    vector<int> route = longestRoute(out, topologicalOrder(out, indeg));
    if (route.empty()) return cout << "IMPOSSIBLE\n", 0;
    cout << route.size() << "\n";
    for (size_t i = 0; i < route.size(); i++) cout << route[i] + 1 << (i + 1 < route.size() ? " " : "\n");
}
