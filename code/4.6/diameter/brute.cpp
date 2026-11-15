#include <bits/stdc++.h>
using namespace std;

// Floyd-Warshall, then the largest entry.
vector<vector<long long>> allDistances(int n, const vector<array<long long, 3>>& edges) {
    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));
    for (int v = 1; v <= n; v++) d[v][v] = 0;
    for (auto [a, b, w] : edges) d[a][b] = d[b][a] = min(d[a][b], w);
    for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    return d;
}

int main() {
    int n;
    cin >> n;
    vector<array<long long, 3>> edges(n - 1);
    for (auto& e : edges) cin >> e[0] >> e[1] >> e[2];
    auto d = allDistances(n, edges);
    long long best = 0;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) best = max(best, d[i][j]);
    cout << best << "\n";
}
