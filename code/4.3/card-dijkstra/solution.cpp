#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX / 4;
typedef vector<vector<pair<int, long long>>> Graph;

// Method: Dijkstra's algorithm, a vertex is finished the first time it comes out of the heap (Theorem 4.3.1).
long long dijkstraTo(const Graph& adj, int s, int t) {
    vector<long long> dist(adj.size(), INF);
    vector<bool> done(adj.size(), false);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> heap;
    dist[s] = 0;
    heap.push({0, s});
    while (!heap.empty()) {
        auto [d, u] = heap.top();
        heap.pop();
        if (done[u]) continue;
        done[u] = true;
        for (auto [v, w] : adj[u])
            if (d + w < dist[v]) dist[v] = d + w, heap.push({dist[v], v});
    }
    return dist[t];
}

// Brute force: repeated relaxation of all edges (n rounds), no heap; fine for any sign of weights without negative cycles.
long long relaxTo(const Graph& adj, int s, int t) {
    int n = adj.size() - 1;
    vector<long long> dist(n + 1, INF);
    dist[s] = 0;
    for (int round = 0; round < n; round++)
        for (int u = 1; u <= n; u++)
            for (auto [v, w] : adj[u])
                if (dist[u] < INF && dist[u] + w < dist[v]) dist[v] = dist[u] + w;
    return dist[t];
}

int main() {
    // P1: seven roads, both ways: 1-2 (7), 1-3 (9), 1-6 (14), 2-3 (10), 2-4 (15), 3-4 (11), 3-6 (2), 4-5 (6), 5-6 (9); from 1 to 5.
    Graph roads(7);
    auto edge = [&](int a, int b, long long w) {
        roads[a].push_back({b, w});
        roads[b].push_back({a, w});
    };
    edge(1, 2, 7), edge(1, 3, 9), edge(1, 6, 14), edge(2, 3, 10), edge(2, 4, 15), edge(3, 4, 11), edge(3, 6, 2), edge(4, 5, 6), edge(5, 6, 9);
    cout << "P1 brute=" << relaxTo(roads, 1, 5) << " method=" << dijkstraTo(roads, 1, 5) << "\n";
    // N1: arrows 1>2 (2), 1>3 (3), 3>2 (-2), 2>4 (1); distance from 1 to 4. One weight is negative.
    Graph negative(5);
    negative[1] = {{2, 2}, {3, 3}};
    negative[3] = {{2, -2}};
    negative[2] = {{4, 1}};
    cout << "N1 brute=" << relaxTo(negative, 1, 4) << " method=" << dijkstraTo(negative, 1, 4) << "\n";
}
