#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.9.3. The fewest moves of a walk that visits every vertex of a connected graph (it may start anywhere and may reuse
// vertices and edges). A state is (vertex, set of vertices seen so far), the set stored as a bitmask: n * 2^n states.
int shortestWalkVisitingAll(const vector<vector<int>>& adj) {
    int n = adj.size(), full = (1 << n) - 1;
    vector<vector<int>> dist(n, vector<int>(1 << n, -1));
    queue<pair<int, int>> q;  // (vertex, set seen)
    for (int v = 0; v < n; v++) {
        dist[v][1 << v] = 0;  // start at v having seen only v; all starts enter together
        q.push({v, 1 << v});
    }
    while (!q.empty()) {
        auto [v, seen] = q.front();
        q.pop();
        if (seen == full) return dist[v][seen];
        for (int w : adj[v]) {
            int next = seen | (1 << w);  // entering w adds w to the set
            if (dist[w][next] != -1) continue;
            dist[w][next] = dist[v][seen] + 1;
            q.push({w, next});
        }
    }
    return -1;  // only when the graph is not connected
}
// snippet:end

// Reference: try every order of first visits and add up the shortest distances between consecutive vertices.
int viaOrders(const vector<vector<int>>& adj) {
    int n = adj.size();
    const int INF = 1000000;  // small enough that sums of a few of them do not overflow
    vector<vector<int>> d(n, vector<int>(n, INF));
    for (int v = 0; v < n; v++) {
        d[v][v] = 0;
        for (int w : adj[v]) d[v][w] = 1;
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    int best = INF;
    do {
        int total = 0;
        for (int i = 0; i + 1 < n; i++) total += d[order[i]][order[i + 1]];
        best = min(best, total);
    } while (next_permutation(order.begin(), order.end()));
    return best >= INF ? -1 : best;
}

int main() {
    auto build = [&](int n, vector<pair<int, int>> edges) {
        vector<vector<int>> adj(n);
        for (auto [a, b] : edges) adj[a].push_back(b), adj[b].push_back(a);
        return adj;
    };
    cout << "path 0-1-2-3: " << shortestWalkVisitingAll(build(4, {{0, 1}, {1, 2}, {2, 3}})) << "\n";
    cout << "star with centre 0 and leaves 1, 2, 3: " << shortestWalkVisitingAll(build(4, {{0, 1}, {0, 2}, {0, 3}})) << "\n";
    cout << "one vertex: " << shortestWalkVisitingAll(build(1, {})) << "\n";
    // Check against the order-based reference on every graph with up to 5 vertices (a disconnected graph gives -1 in both).
    for (int n = 1; n <= 5; n++) {
        vector<pair<int, int>> all;
        for (int a = 0; a < n; a++)
            for (int b = a + 1; b < n; b++) all.push_back({a, b});
        for (int mask = 0; mask < (1 << all.size()); mask++) {
            vector<pair<int, int>> edges;
            for (size_t i = 0; i < all.size(); i++)
                if (mask >> i & 1) edges.push_back(all[i]);
            auto adj = build(n, edges);
            if (shortestWalkVisitingAll(adj) != viaOrders(adj)) return 1;
        }
    }
}
