#include <bits/stdc++.h>
using namespace std;

struct Edge { int to; long long cap; };
vector<Edge> E;
vector<vector<int>> g;
vector<int> level, it;
void clearGraph(int n) { E.clear(); g.assign(n, {}); level.assign(n, 0); it.assign(n, 0); }
void addEdge(int u, int v, long long c) {
    g[u].push_back(E.size()); E.push_back({v, c});
    g[v].push_back(E.size()); E.push_back({u, 0});
}
// Dinic's phases (Theorem 7.9.4): levels by breadth-first search, then one path at a time along edges that go up one level.
bool buildLevels(int s, int t) {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int k : g[u]) if (E[k].cap > 0 && level[E[k].to] < 0) { level[E[k].to] = level[u] + 1; q.push(E[k].to); }
    }
    return level[t] >= 0;
}
long long push(int u, int t, long long limit) {
    if (u == t) return limit;
    for (int& i = it[u]; i < (int)g[u].size(); i++) {
        int k = g[u][i], v = E[k].to;
        if (E[k].cap > 0 && level[v] == level[u] + 1) {
            long long sent = push(v, t, min(limit, E[k].cap));
            if (sent > 0) { E[k].cap -= sent; E[k ^ 1].cap += sent; return sent; }
        }
    }
    return 0;
}

// snippet:begin
// Theorem 7.9.9. Dinic on the unit network of a bipartite graph (this is the Hopcroft-Karp algorithm).
// Left vertices 0..L-1, right vertices L..L+R-1, s = L + R, t = L + R + 1, every capacity 1.
// Returns the size of a largest matching and counts the phases; the theorem bounds them by 2 * sqrt(V) + 3.
int matchingByDinic(int L, int R, const vector<pair<int, int>>& pairs, int& phases) {
    int s = L + R, t = L + R + 1;
    clearGraph(L + R + 2);
    for (int u = 0; u < L; u++) addEdge(s, u, 1);
    for (int v = 0; v < R; v++) addEdge(L + v, t, 1);
    for (auto [u, v] : pairs) addEdge(u, L + v, 1);
    int size = 0;
    phases = 0;
    while (buildLevels(s, t)) {  // one phase per distance from s to t
        phases++;
        fill(it.begin(), it.end(), 0);
        while (push(s, t, 1)) size++;
    }
    return size;
}
// snippet:end

int kuhnSize(int L, int R, const vector<pair<int, int>>& pairs) {
    vector<vector<int>> adj(L);
    for (auto [u, v] : pairs) adj[u].push_back(v);
    vector<int> matchOf(R, -1);
    vector<bool> seen;
    function<bool(int)> go = [&](int u) {
        for (int v : adj[u]) {
            if (seen[v]) continue;
            seen[v] = true;
            if (matchOf[v] < 0 || go(matchOf[v])) { matchOf[v] = u; return true; }
        }
        return false;
    };
    int size = 0;
    for (int u = 0; u < L; u++) { seen.assign(R, false); size += go(u); }
    return size;
}

int main() {
    int phases;
    auto show = [&](const char* name, int L, int R, vector<pair<int, int>> pairs) {
        int size = matchingByDinic(L, R, pairs, phases);
        cout << name << ": matching = " << size << ", phases = " << phases << "\n";
        if (size != kuhnSize(L, R, pairs)) exit(1);
    };
    show("three disjoint pairs", 3, 3, {{0, 0}, {1, 1}, {2, 2}});
    show("a reroute", 3, 3, {{0, 0}, {0, 1}, {1, 0}, {2, 0}});

    // The 100 by 100 grid of free cells: chessboard colouring, the black cells on the left, the white on the right, a pair for every two neighbouring cells.
    int n = 100;
    vector<int> id(n * n);
    int left = 0, right = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) id[i * n + j] = (i + j) % 2 == 0 ? left++ : right++;
    vector<pair<int, int>> pairs;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if ((i + j) % 2) continue;
            int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
            for (int d = 0; d < 4; d++) {
                int a = i + dx[d], b = j + dy[d];
                if (a >= 0 && a < n && b >= 0 && b < n) pairs.push_back({id[i * n + j], id[a * n + b]});
            }
        }
    int size = matchingByDinic(left, right, pairs, phases);
    double bound = 2 * sqrt((double)(left + right + 2)) + 3;
    cout << "grid 100 x 100: matching = " << size << ", phases within 2 sqrt(V) + 3: " << (phases <= bound ? "yes" : "no") << "\n";
    if (size != 5000 || phases > bound) return 1;

    // Random bipartite graphs: the size equals Kuhn's, and the number of phases respects the bound.
    mt19937 rng(3);
    for (int round = 0; round < 3000; round++) {
        int L = rng() % 30 + 1, R = rng() % 30 + 1, m = rng() % (3 * (L + R)) + 1;
        set<pair<int, int>> chosen;
        for (int k = 0; k < m; k++) chosen.insert({(int)(rng() % L), (int)(rng() % R)});
        vector<pair<int, int>> ps(chosen.begin(), chosen.end());
        int sz = matchingByDinic(L, R, ps, phases);
        if (sz != kuhnSize(L, R, ps) || phases > 2 * sqrt((double)(L + R + 2)) + 3) return 1;
    }
}
