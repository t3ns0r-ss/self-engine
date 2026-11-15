#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> reach(n, vector<char>(n, 0));
    vector<pair<int, int>> edges(m);
    for (auto& [a, b] : edges) cin >> a >> b, a--, b--, reach[a][b] = 1;
    for (int v = 0; v < n; v++) reach[v][v] = 1;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (reach[i][k] && reach[k][j]) reach[i][j] = 1;
    vector<int> id(n, -1);
    int comps = 0;
    for (int v = 0; v < n; v++) {
        if (id[v] >= 0) continue;
        for (int u = 0; u < n; u++)
            if (reach[v][u] && reach[u][v]) id[u] = comps;
        comps++;
    }
    set<pair<int, int>> between;
    for (auto [a, b] : edges)
        if (id[a] != id[b]) between.insert({id[a], id[b]});
    cout << comps << " " << between.size() << "\n";
}
