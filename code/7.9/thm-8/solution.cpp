#include <bits/stdc++.h>
using namespace std;

// The matrix version of maxFlow from Theorem 7.9.1, with room for 5 vertices, each split in two.
const int N = 10;
long long cap[N][N];
long long maxFlow(int s, int t) {
    long long flow = 0;
    while (true) {
        int parent[N];
        fill(parent, parent + N, -1);
        parent[s] = s;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < N; v++)
                if (parent[v] < 0 && cap[u][v] > 0) { parent[v] = u; q.push(v); }
        }
        if (parent[t] < 0) return flow;
        long long push = LLONG_MAX;
        for (int v = t; v != s; v = parent[v]) push = min(push, cap[parent[v]][v]);
        for (int v = t; v != s; v = parent[v]) { cap[parent[v]][v] -= push; cap[v][parent[v]] += push; }
        flow += push;
    }
}

// snippet:begin
// Theorem 7.9.8. edges holds directed edges u -> v between the vertices 0..n-1. Returns the largest number of paths from s to t
// that share no edge (vertexDisjoint = false) or share no vertex except s and t (vertexDisjoint = true).
// For the second case every vertex v is split into an entry v and an exit v + n joined by one edge of capacity 1.
int disjointPaths(int n, const vector<pair<int, int>>& edges, int s, int t, bool vertexDisjoint) {
    memset(cap, 0, sizeof cap);
    for (auto [u, v] : edges) cap[vertexDisjoint ? u + n : u][v] = 1;  // an edge leaves the exit of u and enters the entry of v
    if (vertexDisjoint)
        for (int v = 0; v < n; v++) cap[v][v + n] = 1;  // passing through v costs one unit of its capacity
    return (int)maxFlow(vertexDisjoint ? s + n : s, t);  // start at the exit of s, end at the entry of t
}
// snippet:end

// Brute force: list every simple path from s to t, then find the largest family of pairwise disjoint paths.
struct PathInfo { int edgeMask, innerMask; };
vector<PathInfo> paths;
void listPaths(int n, const vector<pair<int, int>>& edges, int u, int t, int visited, int edgeMask, int innerMask) {
    if (u == t) { paths.push_back({edgeMask, innerMask}); return; }
    for (int k = 0; k < (int)edges.size(); k++)
        if (edges[k].first == u && !(visited >> edges[k].second & 1)) {
            int v = edges[k].second;
            listPaths(n, edges, v, t, visited | 1 << v, edgeMask | 1 << k, v == t ? innerMask : innerMask | 1 << v);
        }
}
int bestFamily(size_t from, int usedEdges, int usedInner, bool vertexDisjoint) {
    int best = 0;
    for (size_t i = from; i < paths.size(); i++) {
        bool clash = vertexDisjoint ? (paths[i].innerMask & usedInner) != 0 : (paths[i].edgeMask & usedEdges) != 0;
        if (vertexDisjoint && paths[i].innerMask == 0 && (usedEdges & paths[i].edgeMask)) clash = true;  // the edge s -> t itself can be used once
        if (!clash) best = max(best, 1 + bestFamily(i + 1, usedEdges | paths[i].edgeMask, usedInner | paths[i].innerMask, vertexDisjoint));
    }
    return best;
}
int brute(int n, const vector<pair<int, int>>& edges, int s, int t, bool vertexDisjoint) {
    paths.clear();
    listPaths(n, edges, s, t, 1 << s, 0, 0);
    return bestFamily(0, 0, 0, vertexDisjoint);
}

int main() {
    auto show = [&](const char* name, int n, vector<pair<int, int>> edges, int s, int t) {
        int a = disjointPaths(n, edges, s, t, false), b = disjointPaths(n, edges, s, t, true);
        cout << name << ": edge-disjoint = " << a << ", vertex-disjoint = " << b << "\n";
        if (a != brute(n, edges, s, t, false) || b != brute(n, edges, s, t, true)) exit(1);
    };
    show("two routes", 4, {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {1, 2}}, 0, 3);
    show("one shared vertex", 5, {{0, 1}, {1, 2}, {0, 2}, {2, 3}, {3, 4}, {2, 4}}, 0, 4);
    show("no path", 4, {{0, 1}, {2, 3}}, 0, 3);
    show("direct edge and a detour", 4, {{0, 3}, {0, 1}, {1, 3}}, 0, 3);

    // Check every directed graph on 4 vertices, and 100000 random ones on 5, with s = 0 and t = n - 1.
    for (int n = 4; n <= 5; n++) {
        vector<pair<int, int>> all;
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (u != v) all.push_back({u, v});
        mt19937 rng(5);
        int rounds = n == 4 ? (1 << 12) : 100000;
        for (int round = 0; round < rounds; round++) {
            unsigned code = n == 4 ? round : rng();
            vector<pair<int, int>> edges;
            for (size_t k = 0; k < all.size(); k++)
                if (code >> k & 1) edges.push_back(all[k]);
            for (bool vertexDisjoint : {false, true})
                if (disjointPaths(n, edges, 0, n - 1, vertexDisjoint) != brute(n, edges, 0, n - 1, vertexDisjoint)) return 1;
        }
    }
}
