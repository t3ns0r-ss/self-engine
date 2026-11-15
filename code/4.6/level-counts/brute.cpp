#include <bits/stdc++.h>
using namespace std;

// Relax the distances from vertex 1 along all edges, again and again, and count the vertices at each distance.
int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> edges(n - 1);
    for (auto& e : edges) cin >> e.first >> e.second;
    vector<int> dist(n + 1, 1000000);
    dist[1] = 0;
    for (int round = 0; round < n; round++)
        for (auto [a, b] : edges) dist[a] = min(dist[a], dist[b] + 1), dist[b] = min(dist[b], dist[a] + 1);
    int deepest = *max_element(dist.begin() + 1, dist.end());
    for (int d = 0; d <= deepest; d++) cout << count(dist.begin() + 1, dist.end(), d) << (d < deepest ? " " : "\n");
}
