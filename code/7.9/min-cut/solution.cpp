#include <bits/stdc++.h>
using namespace std;

/*
Problem: a directed network with n vertices and m edges, edge i from u to v with capacity c >= 1. Find a minimum cut between s and t.
Input: n m s t, then m lines u v c (vertices 1..n).
Output: three numbers: the capacity of the cut, the number of vertices on the source side, and the number of edges that cross from the
source side to the other side. The source side is the smallest set that can be a minimum cut: the vertices reachable from s in the residual graph.
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
// Recovering a minimum cut (Theorem 7.9.1). Call after d.maxFlow(s, t). The source side is every vertex that can still be
// reached from s along edges with positive residual capacity; every original edge from that side to the rest is saturated.
vector<bool> sourceSide(const Dinic& d, int s) {
    vector<bool> inS(d.g.size(), false);
    inS[s] = true;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int k : d.g[u])
            if (d.edges[k].cap > 0 && !inS[d.edges[k].to]) { inS[d.edges[k].to] = true; q.push(d.edges[k].to); }
    }
    return inS;
}
// snippet:end

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Dinic d(n);
    vector<array<int, 2>> ends(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        d.addEdge(u - 1, v - 1, c);
        ends[i] = {u - 1, v - 1};
    }
    long long value = d.maxFlow(s - 1, t - 1);
    vector<bool> inS = sourceSide(d, s - 1);
    int size = 0, crossing = 0;
    for (int v = 0; v < n; v++) size += inS[v];
    for (int i = 0; i < m; i++) crossing += inS[ends[i][0]] && !inS[ends[i][1]];  // edge i is edge number 2i of the network
    cout << value << " " << size << " " << crossing << "\n";
}
