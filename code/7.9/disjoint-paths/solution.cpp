#include <bits/stdc++.h>
using namespace std;

/*
Problem: a directed graph with n vertices and m edges, and two vertices s and t. Find the largest number of paths from s to t that
share no edge, and the largest number of paths that share no vertex except s and t.
Input: n m s t, then m lines u v (an edge from u to v; vertices 1..n; no repeated edges).
Output: two numbers: the edge-disjoint count and the vertex-disjoint count.
*/

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

// snippet:begin
// Disjoint paths as maximum flow (Theorem 7.9.8). With vertexDisjoint = false every edge has capacity 1.
// With vertexDisjoint = true, vertex v becomes an entry v and an exit v + n joined by one edge of capacity 1.
int disjointPaths(int n, const vector<array<int, 2>>& edges, int s, int t, bool vertexDisjoint) {
    Dinic d(2 * n);
    for (auto [u, v] : edges) d.addEdge(vertexDisjoint ? u + n : u, v, 1);  // an edge leaves the exit of u and enters the entry of v
    if (vertexDisjoint)
        for (int v = 0; v < n; v++) d.addEdge(v, v + n, 1);  // passing through v uses up its one unit
    return (int)d.maxFlow(vertexDisjoint ? s + n : s, t);   // start at the exit of s, end at the entry of t
}
// snippet:end

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<array<int, 2>> edges(m);
    for (auto& e : edges) {
        cin >> e[0] >> e[1];
        e[0]--; e[1]--;
    }
    cout << disjointPaths(n, edges, s - 1, t - 1, false) << " " << disjointPaths(n, edges, s - 1, t - 1, true) << "\n";
}
