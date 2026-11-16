#include <bits/stdc++.h>
using namespace std;

/*
Problem: a directed network with n vertices and m edges, edge i from u to v with capacity c. Find the largest flow from s to t.
Input: n m s t, then m lines u v c (vertices 1..n).
Output: the value of the maximum flow.
*/

// snippet:begin
// Dinic's algorithm (Theorem 7.9.4). addEdge(u, v, c) adds an edge with capacity c; maxFlow(s, t) returns the largest flow.
struct Dinic {
    struct Edge { int to; long long cap; };  // long long: capacities up to 10^9 add up past 2^31
    vector<Edge> edges;                      // edge k is u -> v; edge k ^ 1 is its reverse, with capacity 0 at the start
    vector<vector<int>> g;                   // g[u]: numbers of the edges leaving u
    vector<int> level, it;
    Dinic(int n) : g(n), level(n), it(n) {}
    void addEdge(int u, int v, long long c) {
        g[u].push_back(edges.size()); edges.push_back({v, c});
        g[v].push_back(edges.size()); edges.push_back({u, 0});
    }
    bool buildLevels(int s, int t) {         // breadth-first search; level[v] = fewest edges from s, -1 if unreachable
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int k : g[u]) if (edges[k].cap > 0 && level[edges[k].to] < 0) { level[edges[k].to] = level[u] + 1; q.push(edges[k].to); }
        }
        return level[t] >= 0;
    }
    long long push(int u, int t, long long limit) {  // one path's worth along edges that go up one level
        if (u == t) return limit;
        for (int& i = it[u]; i < (int)g[u].size(); i++) {
            int k = g[u][i], v = edges[k].to;
            if (edges[k].cap > 0 && level[v] == level[u] + 1) {
                long long sent = push(v, t, min(limit, edges[k].cap));
                if (sent > 0) { edges[k].cap -= sent; edges[k ^ 1].cap += sent; return sent; }
            }
        }
        return 0;
    }
    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (buildLevels(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (long long sent = push(s, t, LLONG_MAX)) flow += sent;
        }
        return flow;
    }
};
// snippet:end

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Dinic d(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        d.addEdge(u - 1, v - 1, c);
    }
    cout << d.maxFlow(s - 1, t - 1) << "\n";
}
