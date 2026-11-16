#include <bits/stdc++.h>
using namespace std;

/*
Problem: n items each choose side S or side T. Item i pays a_i on side S and b_i on side T. For each of m given triples (i, j, w), the penalty w
is paid when item i is on side S and item j is on side T. Find the smallest total cost.
Input: n m, then n lines a_i b_i, then m lines i j w (items 1..n, i != j, w >= 0).
Output: the smallest total cost.
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
// Cheapest choice of sides as a minimum cut (Theorem 7.9.2). Vertex i is item i; s is the source, t the sink.
long long cheapestSides(int n, const vector<long long>& a, const vector<long long>& b, const vector<array<long long, 3>>& pairs) {
    int s = n, t = n + 1;
    Dinic d(n + 2);
    for (int i = 0; i < n; i++) {
        d.addEdge(s, i, b[i]);  // cut exactly when i is on side T, which costs b[i]
        d.addEdge(i, t, a[i]);  // cut exactly when i is on side S, which costs a[i]
    }
    for (auto [i, j, w] : pairs) d.addEdge(i, j, w);  // cut exactly when i is on side S and j is on side T
    return d.maxFlow(s, t);
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    vector<array<long long, 3>> pairs(m);
    for (auto& p : pairs) {
        cin >> p[0] >> p[1] >> p[2];
        p[0]--; p[1]--;
    }
    cout << cheapestSides(n, a, b, pairs) << "\n";
}
