/*
Problem: the longest road trip.
Input: n, then n - 1 lines "a b w": a road of length w (0 <= w <= 10^9) between towns a and b; the roads form a tree.
Output: the largest distance between two towns.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.5.4. adj[u] holds {neighbour, length}. Walk from town 1 to the farthest town a, and from a to the farthest town b.
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
long long longestTrip(const vector<vector<pair<int, long long>>>& adj) {
    vector<long long> dist;
    int a = farthestFrom(adj, 1, dist);
    int b = farthestFrom(adj, a, dist);
    return dist[b];
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
    cout << longestTrip(adj) << "\n";
}
