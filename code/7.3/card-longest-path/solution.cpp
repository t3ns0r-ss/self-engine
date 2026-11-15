#include <bits/stdc++.h>
using namespace std;

vector<int> kahn(const vector<vector<pair<int, int>>>& out) {
    int n = out.size();
    vector<int> indeg(n, 0), order;
    for (int v = 0; v < n; v++)
        for (auto [u, w] : out[v]) indeg[u]++;
    for (int v = 0; v < n; v++)
        if (indeg[v] == 0) order.push_back(v);
    for (size_t i = 0; i < order.size(); i++)
        for (auto [u, w] : out[order[i]])
            if (--indeg[u] == 0) order.push_back(u);
    return order;
}
// method: the largest total weight of a path, over the vertices that Kahn's algorithm takes; brute: all paths (simple paths).
long long method(const vector<vector<pair<int, int>>>& out) {
    vector<int> order = kahn(out);
    vector<long long> dp(out.size(), 0);
    long long best = 0;
    for (int v : order) {
        best = max(best, dp[v]);
        for (auto [u, w] : out[v]) dp[u] = max(dp[u], dp[v] + w);
    }
    return best;
}
long long brute(const vector<vector<pair<int, int>>>& out) {
    long long best = 0;
    vector<char> on(out.size(), 0);
    function<void(int, long long)> go = [&](int v, long long sum) {
        best = max(best, sum);
        on[v] = 1;
        for (auto [u, w] : out[v])
            if (!on[u]) go(u, sum + w);
        on[v] = 0;
    };
    for (size_t s = 0; s < out.size(); s++) go(s, 0);
    return best;
}

int main() {
    vector<vector<pair<int, int>>> g1(6), g2(4), g3(3);
    for (auto [a, b] : vector<pair<int, int>>{{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {2, 5}}) g1[a].push_back({b, 1});  // the number of edges
    for (auto [a, b, x] : vector<array<int, 3>>{{0, 1, 5}, {1, 2, -3}, {0, 2, 1}, {2, 3, 4}}) g2[a].push_back({b, x});
    for (auto [a, b] : vector<pair<int, int>>{{0, 1}, {1, 0}, {1, 2}}) g3[a].push_back({b, 1});  // a cycle 0 -> 1 -> 0
    cout << "P1 brute=" << brute(g1) << " method=" << method(g1) << "\n";
    cout << "P2 brute=" << brute(g2) << " method=" << method(g2) << "\n";
    cout << "N1 brute=" << brute(g3) << " method=" << method(g3) << "\n";
}
