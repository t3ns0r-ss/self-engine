#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.9.4. Cheapest trip from 1 to n when up to k roads may be driven for free; edges are {to, weight}. A state is
// (vertex, free roads left). A state is skipped when a finished state at the same vertex has at least as many roads left.
long long cheapestWithFreeRoads(const vector<vector<pair<int, long long>>>& adj, int k) {
    int n = adj.size() - 1;
    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> dist(n + 1, vector<long long>(k + 1, INF));
    vector<int> bestLeft(n + 1, -1);  // most free roads left among the finished states of each vertex
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> heap;  // (cost, vertex, left)
    dist[1][k] = 0;
    heap.push({0, 1, k});
    while (!heap.empty()) {
        auto [d, u, left] = heap.top();
        heap.pop();
        if (d > dist[u][left]) continue;  // an old entry
        if (left <= bestLeft[u]) continue;  // dominated: a finished state costs no more and has at least as many left
        bestLeft[u] = left;
        if (u == n) return d;
        for (auto [v, w] : adj[u]) {
            if (d + w < dist[v][left]) dist[v][left] = d + w, heap.push({d + w, v, left});
            if (left > 0 && d < dist[v][left - 1]) dist[v][left - 1] = d, heap.push({d, v, left - 1});
        }
    }
    return -1;
}
// snippet:end

// Reference: the same search with no skipping, over all states, taking the cheapest state at vertex n.
long long withoutSkipping(const vector<vector<pair<int, long long>>>& adj, int k) {
    int n = adj.size() - 1;
    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> dist(n + 1, vector<long long>(k + 1, INF));
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> heap;
    dist[1][k] = 0;
    heap.push({0, 1, k});
    while (!heap.empty()) {
        auto [d, u, left] = heap.top();
        heap.pop();
        if (d > dist[u][left]) continue;
        for (auto [v, w] : adj[u]) {
            if (d + w < dist[v][left]) dist[v][left] = d + w, heap.push({d + w, v, left});
            if (left > 0 && d < dist[v][left - 1]) dist[v][left - 1] = d, heap.push({d, v, left - 1});
        }
    }
    long long best = INF;
    for (int left = 0; left <= k; left++) best = min(best, dist[n][left]);
    return best == INF ? -1 : best;
}

int main() {
    auto run = [&](int n, vector<array<long long, 3>> edges, int k) {
        vector<vector<pair<int, long long>>> adj(n + 1);
        for (auto [a, b, w] : edges) {
            adj[a].push_back({(int)b, w});
            adj[b].push_back({(int)a, w});
        }
        return make_pair(cheapestWithFreeRoads(adj, k), withoutSkipping(adj, k));
    };
    auto show = [&](const char* text, int n, vector<array<long long, 3>> edges, int k) {
        auto [fast, slow] = run(n, edges, k);
        if (fast != slow) exit(1);
        cout << text << ": " << fast << "\n";
    };
    show("roads 1-2 (4), 2-3 (6), up to 1 free", 3, {{1, 2, 4}, {2, 3, 6}}, 1);
    show("roads 1-2 (4), 2-3 (6), up to 2 free", 3, {{1, 2, 4}, {2, 3, 6}}, 2);
    show("roads 1-2 (4), 2-3 (6), 0 free", 3, {{1, 2, 4}, {2, 3, 6}}, 0);
    // Compare with no skipping on random small graphs.
    mt19937 rng(4242);
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 6 + 1, k = rng() % 4;
        vector<array<long long, 3>> edges;
        int count = rng() % 10;
        for (int i = 0; i < count && n > 1; i++) {
            int a = rng() % n + 1, b = rng() % n + 1;
            if (a != b) edges.push_back({a, b, (long long)(rng() % 10)});
        }
        auto [fast, slow] = run(n, edges, k);
        if (fast != slow) return 1;
    }
}
