/*
Problem: where to meet.
Input: n, then n - 1 lines "a b w": a road of length w (0 <= w <= 10^9) between towns a and b; the roads form a tree.
Output: the town whose farthest town is as near as possible (the smallest number on a tie), and that distance.
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
// Theorems 4.5.4 and 4.5.5. The town with the smallest farthest distance; adj[u] holds {neighbour, length}.
pair<int, long long> meetingPlace(const vector<vector<pair<int, long long>>>& adj) {
    vector<long long> first, fromA, fromB;
    int a = farthestFrom(adj, 1, first);
    int b = farthestFrom(adj, a, fromA);
    farthestFrom(adj, b, fromB);
    pair<int, long long> best = {1, max(fromA[1], fromB[1])};
    for (int v = 2; v < (int)adj.size(); v++)
        if (max(fromA[v], fromB[v]) < best.second) best = {v, max(fromA[v], fromB[v])};  // strict: the smallest number wins ties
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
    auto [town, distance] = meetingPlace(adj);
    cout << town << " " << distance << "\n";
}
