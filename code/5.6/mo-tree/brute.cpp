#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> colour(n);
    for (int& c : colour) cin >> c;
    vector<vector<int>> adj(n);
    for (int i = 0; i + 1 < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1), adj[v - 1].push_back(u - 1);
    }
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        vector<int> from(n, -2);  // the path by a search from u
        queue<int> bfs;
        from[u] = -1, bfs.push(u);
        while (!bfs.empty()) {
            int x = bfs.front();
            bfs.pop();
            for (int w : adj[x])
                if (from[w] == -2) from[w] = x, bfs.push(w);
        }
        map<int, int> c;
        for (int x = v; x != -1; x = from[x]) c[colour[x]]++;
        int once = 0;
        for (auto [col, k] : c) once += k == 1;
        cout << once << "\n";
    }
}
