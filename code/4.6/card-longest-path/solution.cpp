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
    auto diameter = [&](const vector<vector<pair<int, long long>>>& adj) {
        vector<long long> dist;
        int a = farthestFrom(adj, 1, dist);
        int b = farthestFrom(adj, a, dist);
        return dist[b];
    };
    // P1: the longest path of the tree 1-2 (3), 2-3 (4), 2-4 (1), 4-5 (6), 1-6 (2). Brute force: the largest entry of the table of all distances.
    {
        auto adj = build(6, {{1, 2, 3}, {2, 3, 4}, {2, 4, 1}, {4, 5, 6}, {1, 6, 2}});
        auto d = floyd(adj);
        long long brute = 0;
        for (int i = 1; i <= 6; i++) for (int j = 1; j <= 6; j++) brute = max(brute, d[i][j]);
        cout << "P1 brute=" << brute << " method=" << diameter(adj) << "\n";
    }
    // P2: the shortest walk that visits all four towns of the tree 1-2 (1), 2-3 (1), 2-4 (5), starting anywhere, no return needed.
    // Brute force: every start and every order of visiting, adding the distances. Method: twice the total weight minus the diameter.
    {
        auto adj = build(4, {{1, 2, 1}, {2, 3, 1}, {2, 4, 5}});
        auto d = floyd(adj);
        vector<int> order = {1, 2, 3, 4};
        long long brute = LLONG_MAX;
        do {
            long long total = 0;
            for (int i = 0; i + 1 < 4; i++) total += d[order[i]][order[i + 1]];
            brute = min(brute, total);
        } while (next_permutation(order.begin(), order.end()));
        cout << "P2 brute=" << brute << " method=" << 2 * (1 + 1 + 5) - diameter(adj) << "\n";
    }
    // N1: the longest simple path in the triangle 1-2-3 with a pendant vertex 4 on vertex 3 (edges count 1). The two walks give
    // the largest shortest distance, 2, but the path 1-2-3-4 has 3 edges.
    {
        vector<vector<int>> g(5);
        auto edge = [&](int a, int b) { g[a].push_back(b), g[b].push_back(a); };
        edge(1, 2), edge(2, 3), edge(1, 3), edge(3, 4);
        int brute = 0;
        vector<int> path;
        function<void(int)> go = [&](int u) {
            brute = max(brute, (int)path.size() - 1);
            for (int v : g[u]) if (find(path.begin(), path.end(), v) == path.end()) path.push_back(v), go(v), path.pop_back();
        };
        for (int s = 1; s <= 4; s++) path = {s}, go(s);
        auto bfs = [&](int s) {
            vector<int> dist(5, -1);
            queue<int> q;
            dist[s] = 0, q.push(s);
            while (!q.empty()) { int u = q.front(); q.pop(); for (int v : g[u]) if (dist[v] < 0) dist[v] = dist[u] + 1, q.push(v); }
            return dist;
        };
        auto first = bfs(1);
        int a = max_element(first.begin() + 1, first.end()) - first.begin();
        auto second = bfs(a);
        cout << "N1 brute=" << brute << " method=" << *max_element(second.begin() + 1, second.end()) << "\n";
    }
}
