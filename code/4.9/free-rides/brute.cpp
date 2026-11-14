#include <bits/stdc++.h>
using namespace std;

// Try every simple path from 1 to n; the cost is the sum of its road lengths minus the k longest.
int n, m, k;
vector<vector<pair<int, long long>>> adj;
vector<bool> onPath;
vector<long long> path;
long long best = -1;

void go(int u) {
    if (u == n) {
        vector<long long> p = path;
        sort(p.rbegin(), p.rend());
        long long cost = 0;
        for (size_t i = k; i < p.size(); i++) cost += p[i];
        if (best == -1 || cost < best) best = cost;
        return;
    }
    for (auto [v, w] : adj[u]) {
        if (onPath[v]) continue;
        onPath[v] = true;
        path.push_back(w);
        go(v);
        path.pop_back();
        onPath[v] = false;
    }
}

int main() {
    cin >> n >> m >> k;
    adj.assign(n + 1, {});
    onPath.assign(n + 1, false);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }
    onPath[1] = true;
    go(1);
    cout << best << "\n";
}
