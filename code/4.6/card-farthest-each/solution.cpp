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

int main() {
    auto build = [](int n, vector<array<long long, 3>> es) {
        vector<vector<pair<int, long long>>> adj(n + 1);
        for (auto [a, b, w] : es) adj[a].push_back({(int)b, w}), adj[b].push_back({(int)a, w});
        return adj;
    };
    auto floyd = [](const vector<vector<pair<int, long long>>>& adj) {
        int n = adj.size() - 1;
        const long long INF = LLONG_MAX / 4;
        vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));
        for (int v = 1; v <= n; v++) d[v][v] = 0;
        for (int u = 1; u <= n; u++) for (auto [v, w] : adj[u]) d[u][v] = min(d[u][v], w);
        for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        return d;
    };
    auto farthestDistances = [&](const vector<vector<pair<int, long long>>>& adj) {
        vector<long long> first, fromA, fromB;
        int a = farthestFrom(adj, 1, first);
        int b = farthestFrom(adj, a, fromA);
        farthestFrom(adj, b, fromB);
        vector<long long> best(adj.size(), 0);
        for (int v = 1; v < (int)adj.size(); v++) best[v] = max(fromA[v], fromB[v]);
        return best;
    };
    auto join = [](const vector<long long>& v) { string s; for (size_t i = 1; i < v.size(); i++) s += (i > 1 ? "," : "") + to_string(v[i]); return s; };
    // P1: the farthest distance from each vertex of the star with centre 1 and leaves 2, 3, 4 at the distances 5, 2, 3.
    {
        auto adj = build(4, {{1, 2, 5}, {1, 3, 2}, {1, 4, 3}});
        auto d = floyd(adj);
        vector<long long> brute(5, 0);
        for (int i = 1; i <= 4; i++) for (int j = 1; j <= 4; j++) brute[i] = max(brute[i], d[i][j]);
        cout << "P1 brute=" << join(brute) << " method=" << join(farthestDistances(adj)) << "\n";
    }
    // P2: the path 1-2-3-4-5 (weights 1): which vertex has the smallest farthest distance (the best meeting point)?
    {
        auto adj = build(5, {{1, 2, 1}, {2, 3, 1}, {3, 4, 1}, {4, 5, 1}});
        auto d = floyd(adj);
        int brute = 1, method = 1;
        auto far = farthestDistances(adj);
        long long bestBrute = LLONG_MAX;
        for (int i = 1; i <= 5; i++) {
            long long e = 0;
            for (int j = 1; j <= 5; j++) e = max(e, d[i][j]);
            if (e < bestBrute) bestBrute = e, brute = i;
            if (far[i] < far[method]) method = i;
        }
        cout << "P2 brute=" << brute << " method=" << method << "\n";
    }
    // N1: the cycle of six cities 1-2-3-4-5-6-1 (distances count edges): how far is the city farthest from city 2? The two walks
    // pick the ends 1 and 4, and city 2 is at distance 1 and 2 from them, but city 5 is at distance 3.
    {
        vector<vector<int>> g(7);
        for (int v = 1; v <= 6; v++) { int w = v % 6 + 1; g[v].push_back(w), g[w].push_back(v); }
        auto bfs = [&](int s) {
            vector<int> dist(7, -1);
            queue<int> q;
            dist[s] = 0, q.push(s);
            while (!q.empty()) { int u = q.front(); q.pop(); for (int v : g[u]) if (dist[v] < 0) dist[v] = dist[u] + 1, q.push(v); }
            return dist;
        };
        auto from2 = bfs(2);
        int brute = *max_element(from2.begin() + 1, from2.end());
        auto first = bfs(1);
        int a = max_element(first.begin() + 1, first.end()) - first.begin();
        auto fromA = bfs(a);
        int b = max_element(fromA.begin() + 1, fromA.end()) - fromA.begin();
        auto fromB = bfs(b);
        cout << "N1 brute=" << brute << " method=" << max(fromA[2], fromB[2]) << "\n";
    }
}
