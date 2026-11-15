/*
Problem: AtCoder ABC 361 E, Tree and Hamilton Path 2.
Input: N, then N - 1 lines "A B C": a road of length C (1 <= C <= 10^9) between cities A and B; the roads form a tree.
Output: the least total distance of a trip that visits every city at least once; it may start anywhere and need not return.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Example 2. Visiting everything and coming back uses every road twice; not coming back saves the path from the start to the end,
// best the longest one: 2 * (sum of all lengths) - diameter. adj[u] holds {neighbour, length}.
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
long long shortestTrip(const vector<vector<pair<int, long long>>>& adj) {
    long long total = 0;
    for (auto& edges : adj) for (auto [v, w] : edges) total += w;  // every road is counted from both ends: this is twice the sum
    vector<long long> dist;
    int a = farthestFrom(adj, 1, dist);
    int b = farthestFrom(adj, a, dist);
    return total - dist[b];
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    cout << shortestTrip(adj) << "\n";
}
