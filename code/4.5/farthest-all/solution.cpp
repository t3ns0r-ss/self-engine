/*
Problem: how far is the farthest town.
Input: n, then n - 1 lines "a b w": a road of length w (0 <= w <= 10^9) between towns a and b; the roads form a tree.
Output: n numbers: for each town, the distance to the town farthest from it.
*/
#include <bits/stdc++.h>
using namespace std;

// Distances from s to every vertex of a weighted tree; returns a vertex at the largest distance.
int farthestFrom(const vector<vector<pair<int, long long>>>& adj, int s, vector<long long>& dist) {
    dist.assign(adj.size(), -1);
    dist[s] = 0;
    vector<int> stack = {s};
    int far = s;
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        if (dist[u] > dist[far]) far = u;
        for (auto [v, w] : adj[u])
            if (dist[v] < 0) dist[v] = dist[u] + w, stack.push_back(v);
    }
    return far;
}

// snippet:begin
// Theorem 4.5.5. Distances from the two ends a and b of a diameter; the answer for a town is the larger of its two distances.
vector<long long> farthestDistances(const vector<vector<pair<int, long long>>>& adj) {
    vector<long long> first, fromA, fromB;
    int a = farthestFrom(adj, 1, first);
    int b = farthestFrom(adj, a, fromA);
    farthestFrom(adj, b, fromB);
    vector<long long> best(adj.size(), 0);
    for (int v = 1; v < (int)adj.size(); v++) best[v] = max(fromA[v], fromB[v]);
    return best;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }
    auto best = farthestDistances(adj);
    for (int v = 1; v <= n; v++) cout << best[v] << (v < n ? " " : "\n");
}
