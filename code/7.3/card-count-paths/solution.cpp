#include <bits/stdc++.h>
using namespace std;

vector<int> kahn(const vector<vector<int>>& out) {
    int n = out.size();
    vector<int> indeg(n, 0), order;
    for (int v = 0; v < n; v++)
        for (int u : out[v]) indeg[u]++;
    for (int v = 0; v < n; v++)
        if (indeg[v] == 0) order.push_back(v);
    for (size_t i = 0; i < order.size(); i++)
        for (int u : out[order[i]])
            if (--indeg[u] == 0) order.push_back(u);
    return order;
}
long long method(const vector<vector<int>>& out, int target) {
    vector<long long> ways(out.size(), 0);
    ways[0] = 1;
    for (int v : kahn(out))
        for (int u : out[v]) ways[u] += ways[v];
    return ways[target];
}
long long brute(const vector<vector<int>>& out, int target) {  // simple paths from the vertex 0
    long long count = 0;
    vector<char> on(out.size(), 0);
    function<void(int)> go = [&](int v) {
        if (v == target) count++;
        on[v] = 1;
        for (int u : out[v])
            if (!on[u]) go(u);
        on[v] = 0;
    };
    go(0);
    return count;
}

int main() {
    vector<vector<int>> g1(6), g2(9), g3(4);
    for (auto [a, b] : vector<pair<int, int>>{{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {2, 5}}) g1[a].push_back(b);
    for (int i = 0; i < 3; i++)  // a 3 x 3 grid, moves to the right and downwards; the cell (i, j) is 3i + j
        for (int j = 0; j < 3; j++) {
            if (j + 1 < 3) g2[3 * i + j].push_back(3 * i + j + 1);
            if (i + 1 < 3) g2[3 * i + j].push_back(3 * (i + 1) + j);
        }
    for (auto [a, b] : vector<pair<int, int>>{{0, 1}, {1, 2}, {2, 1}, {2, 3}}) g3[a].push_back(b);
    cout << "P1 brute=" << brute(g1, 4) << " method=" << method(g1, 4) << "\n";
    cout << "P2 brute=" << brute(g2, 8) << " method=" << method(g2, 8) << "\n";
    cout << "N1 brute=" << brute(g3, 3) << " method=" << method(g3, 3) << "\n";
}
