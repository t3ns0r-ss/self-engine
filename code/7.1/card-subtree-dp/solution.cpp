#include <bits/stdc++.h>
using namespace std;

// Colourings of a tree with no two black neighbours, by the subtree DP, against trying all colourings.
long long method(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n);
    for (auto [a, b] : edges) adj[a].push_back(b), adj[b].push_back(a);
    function<array<long long, 2>(int, int)> go = [&](int v, int p) {
        array<long long, 2> f = {1, 1};
        for (int u : adj[v])
            if (u != p) {
                auto g = go(u, v);
                f[0] *= g[0] + g[1], f[1] *= g[0];
            }
        return f;
    };
    auto f = go(0, -1);
    return f[0] + f[1];
}
long long brute(int n, const vector<pair<int, int>>& edges) {
    long long count = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (auto [a, b] : edges) ok = ok && !((mask >> a & 1) && (mask >> b & 1));
        count += ok;
    }
    return count;
}

int main() {
    vector<pair<int, int>> path3 = {{0, 1}, {1, 2}}, star4 = {{0, 1}, {0, 2}, {0, 3}};
    cout << "P1 brute=" << brute(3, path3) << " method=" << method(3, path3) << "\n";
    cout << "P2 brute=" << brute(4, star4) << " method=" << method(4, star4) << "\n";
    // N1: a cycle of 4 vertices is not a tree: the subtree DP along the path 0-1-2-3 forgets the edge 3-0.
    vector<pair<int, int>> cycle = {{0, 1}, {1, 2}, {2, 3}, {3, 0}}, cutCycle = {{0, 1}, {1, 2}, {2, 3}};
    cout << "N1 brute=" << brute(4, cycle) << " method=" << method(4, cutCycle) << "\n";
}
