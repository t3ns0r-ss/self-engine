#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a - 1].push_back(b - 1), adj[b - 1].push_back(a - 1);
    }
    vector<int> parent(n, -1), sz(n, 1);
    function<void(int)> go = [&](int v) {
        for (int u : adj[v])
            if (u != parent[v]) parent[u] = v, go(u), sz[v] += sz[u];
    };
    go(0);
    for (int v = 0; v < n; v++) cout << parent[v] + 1 << " " << sz[v] << "\n";
}
