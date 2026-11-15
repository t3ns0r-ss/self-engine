#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for (int i = 0; i + 1 < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1), adj[v - 1].push_back(u - 1);
    }
    vector<bool> red(n, false);
    red[0] = true;
    while (q--) {
        int type, v;
        cin >> type >> v;
        v--;
        if (type == 1) {
            red[v] = true;
            continue;
        }
        vector<int> d(n, -1);  // a search from v until a red vertex is reached
        queue<int> bfs;
        d[v] = 0, bfs.push(v);
        while (!bfs.empty()) {
            int u = bfs.front();
            bfs.pop();
            if (red[u]) {
                cout << d[u] << "\n";
                break;
            }
            for (int w : adj[u])
                if (d[w] < 0) d[w] = d[u] + 1, bfs.push(w);
        }
    }
}
