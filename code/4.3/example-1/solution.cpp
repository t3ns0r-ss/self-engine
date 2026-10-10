/*
Problem: AtCoder ABC 340 D, Super Takahashi Bros.
Input: N, then N-1 lines "A B X": at stage i, pay A seconds to open stage i+1 or B seconds to open stage X.
Output: the fewest seconds until stage N can be played.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Example 1. Stages are vertices, each way of clearing a stage is an edge with its time as weight; the answer is the
// cheapest cost from stage 1 to stage n.
long long fewestSeconds(const vector<vector<pair<int, long long>>>& adj) {
    int n = adj.size() - 1;
    const long long INF = LLONG_MAX / 4;
    vector<long long> dist(n + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> heap;
    dist[1] = 0;
    heap.push({0, 1});
    while (!heap.empty()) {
        auto [d, u] = heap.top();
        heap.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u])
            if (d + w < dist[v]) dist[v] = d + w, heap.push({dist[v], v});
    }
    return dist[n];
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        long long a, b;
        int x;
        cin >> a >> b >> x;
        adj[i].push_back({i + 1, a});
        adj[i].push_back({x, b});
    }
    cout << fewestSeconds(adj) << "\n";
}
