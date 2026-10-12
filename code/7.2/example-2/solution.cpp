#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1681, Game Routes. A game has n levels connected by m one-way teleporters with no directed cycle (n up to 10^5, m up to
2·10^5). In how many ways can the game be completed, from the level 1 to the level n? Print the number modulo 10^9 + 7.
Input: n, m, then the teleporters "a b".
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
// Theorem 7.2.2: ways[v] = the number of paths from the level 0 to v; the paths into v end with a teleporter u -> v, so
// ways[v] is the sum of ways[u] over the teleporters into v, and a vertex is finished after all its predecessors in the order.
long long gameRoutes(const vector<vector<int>>& out, const vector<int>& order) {
    const long long MOD = 1000000007;
    vector<long long> ways(out.size(), 0);
    ways[0] = 1;
    for (int v : order)
        for (int u : out[v]) ways[u] = (ways[u] + ways[v]) % MOD;
    return ways[out.size() - 1];
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
    cout << gameRoutes(out, topologicalOrder(out, indeg)) << "\n";
}
