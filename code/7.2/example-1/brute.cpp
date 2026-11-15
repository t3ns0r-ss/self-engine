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
    for (int s = 0; s < n; s++) {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[s] = 0, q.push(s);
        long long sum = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            sum += dist[v];
            for (int u : adj[v])
                if (dist[u] < 0) dist[u] = dist[v] + 1, q.push(u);
        }
        cout << sum << (s + 1 < n ? " " : "\n");
    }
}
