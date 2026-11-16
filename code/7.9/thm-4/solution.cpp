#include <bits/stdc++.h>
using namespace std;

const int N = 6;
struct Edge { int to; long long cap; };
vector<Edge> E;       // edges in pairs: E[k] is u -> v, E[k ^ 1] is the reverse v -> u (residual capacity 0 at the start)
vector<int> g[N];     // g[u] lists the numbers of the edges that leave u
int level[N], it[N];
void addEdge(int u, int v, long long c) {
    g[u].push_back(E.size()); E.push_back({v, c});
    g[v].push_back(E.size()); E.push_back({u, 0});
}

// snippet:begin
// Theorem 7.9.4. Dinic: in each phase push flow along shortest paths only, until none is left.
bool buildLevels(int s, int t) {  // level[v] = fewest edges from s (breadth-first search), -1 if unreachable
    fill(level, level + N, -1);
    level[s] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int k : g[u]) if (E[k].cap > 0 && level[E[k].to] < 0) { level[E[k].to] = level[u] + 1; q.push(E[k].to); }
    }
    return level[t] >= 0;
}
long long push(int u, int t, long long limit) {  // sends one path's worth along edges that go up one level
    if (u == t) return limit;
    for (int& i = it[u]; i < (int)g[u].size(); i++) {  // it[u]: first edge of u not yet known to be useless
        int k = g[u][i], v = E[k].to;
        if (E[k].cap > 0 && level[v] == level[u] + 1) {
            long long sent = push(v, t, min(limit, E[k].cap));
            if (sent > 0) { E[k].cap -= sent; E[k ^ 1].cap += sent; return sent; }
        }
    }
    return 0;
}
long long dinic(int s, int t) {
    long long flow = 0;
    while (buildLevels(s, t)) {  // one phase for each distance from s to t
        fill(it, it + N, 0);
        while (long long sent = push(s, t, LLONG_MAX)) flow += sent;
    }
    return flow;
}
// snippet:end

void clearGraph() {
    E.clear();
    for (auto& list : g) list.clear();
}

// Runs the phases one by one and records level[t] at the start of each phase.
long long runPhases(int s, int t, vector<int>& distances) {
    long long flow = 0;
    while (buildLevels(s, t)) {
        distances.push_back(level[t]);
        fill(it, it + N, 0);
        while (long long sent = push(s, t, LLONG_MAX)) flow += sent;
    }
    return flow;
}

void show(const char* name, int s, int t) {
    vector<int> distances;
    long long flow = runPhases(s, t, distances);
    cout << name << ": flow = " << flow << ", distance from s to t in each phase:";
    for (int d : distances) cout << " " << d;
    cout << "\n";
}

long long bruteCut(int s, int t, const vector<array<long long, 3>>& edges) {
    long long best = LLONG_MAX;
    for (int mask = 0; mask < (1 << N); mask++) {
        if (!(mask >> s & 1) || (mask >> t & 1)) continue;
        long long total = 0;
        for (auto e : edges)
            if ((mask >> e[0] & 1) && !(mask >> e[1] & 1)) total += e[2];
        best = min(best, total);
    }
    return best;
}

int main() {
    auto build = [&](vector<array<long long, 3>> edges) {
        clearGraph();
        for (auto e : edges) addEdge(e[0], e[1], e[2]);
    };
    build({{0, 1, 2}, {0, 2, 2}, {1, 2, 1}, {1, 3, 1}, {2, 3, 2}});
    show("tiny", 0, 3);
    build({{0, 1, 1000}, {0, 2, 1000}, {1, 2, 1}, {1, 3, 1000}, {2, 3, 1000}});
    show("wide paths", 0, 3);
    build({{0, 1, 1}, {0, 2, 1}, {1, 3, 1}, {2, 3, 1}, {3, 4, 2}, {4, 5, 2}, {1, 5, 1}});
    show("six vertices", 0, 5);

    // Check on random graphs: the flow equals the cheapest cut, and the distance from s to t grows in every phase, so there are at most N - 1 phases.
    mt19937 rng(11);
    for (int round = 0; round < 30000; round++) {
        vector<array<long long, 3>> edges;
        int m = rng() % 12 + 1;
        for (int k = 0; k < m; k++) {
            int u = rng() % N, v = rng() % N;
            if (u != v) edges.push_back({u, v, (long long)(rng() % 5)});
        }
        build(edges);
        vector<int> distances;
        long long flow = runPhases(0, N - 1, distances);
        if (flow != bruteCut(0, N - 1, edges)) return 1;
        for (size_t i = 1; i < distances.size(); i++)
            if (distances[i] <= distances[i - 1]) return 1;
        if ((int)distances.size() > N - 1) return 1;
    }
}
