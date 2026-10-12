#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, distance;
    cin >> n >> distance;
    vector<vector<int>> adj(n);
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a - 1].push_back(b - 1), adj[b - 1].push_back(a - 1);
    }
    vector<int> leaves;
    for (int v = 1; v < n; v++)
        if (adj[v].size() == 1) leaves.push_back(v);
    long long count = 0;
    for (size_t i = 0; i < leaves.size(); i++) {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[leaves[i]] = 0, q.push(leaves[i]);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : adj[v])
                if (dist[u] < 0) dist[u] = dist[v] + 1, q.push(u);
        }
        for (size_t j = i + 1; j < leaves.size(); j++) count += dist[leaves[j]] <= distance;
    }
    cout << count << "\n";
}
