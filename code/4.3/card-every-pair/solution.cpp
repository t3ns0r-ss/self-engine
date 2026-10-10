#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX / 4;

// Method: Floyd-Warshall (Theorem 4.3.4) on a table d[1..n][1..n].
vector<vector<long long>> floyd(int n, const vector<array<long long, 3>>& edges) {
    vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));
    for (int v = 1; v <= n; v++) d[v][v] = 0;
    for (auto [a, b, w] : edges) d[a][b] = min(d[a][b], w);
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][k] < INF && d[k][j] < INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    return d;
}

// Brute force: the smallest length over all simple paths from a to b.
void tryPaths(int u, int t, long long length, vector<bool>& seen, const vector<array<long long, 3>>& edges, long long& best) {
    if (u == t) {
        best = min(best, length);
        return;
    }
    seen[u] = true;
    for (auto [a, b, w] : edges)
        if (a == u && !seen[b]) tryPaths(b, t, length + w, seen, edges, best);
    seen[u] = false;
}
long long bruteDistance(int n, const vector<array<long long, 3>>& edges, int a, int b) {
    long long best = INF;
    vector<bool> seen(n + 1, false);
    tryPaths(a, b, 0, seen, edges, best);
    return best;
}

// Does a negative cycle exist? Bellman-Ford from a virtual start (every distance 0): a change in round n shows one.
bool negativeCycle(int n, const vector<array<long long, 3>>& edges) {
    vector<long long> dist(n + 1, 0);
    for (int round = 1; round <= n; round++) {
        bool changed = false;
        for (auto [u, v, w] : edges)
            if (dist[u] + w < dist[v]) dist[v] = dist[u] + w, changed = true;
        if (!changed) return false;
    }
    return true;
}

vector<array<long long, 3>> twoWay(vector<array<long long, 3>> edges) {
    vector<array<long long, 3>> out;
    for (auto [a, b, w] : edges) out.push_back({a, b, w}), out.push_back({b, a, w});
    return out;
}

int main() {
    // P1: four towns in a ring of two-way roads 1-2 (2), 2-3 (2), 3-4 (2), 1-4 (7); the distance from 1 to 4.
    auto ring = twoWay({{1, 2, 2}, {2, 3, 2}, {3, 4, 2}, {1, 4, 7}});
    cout << "P1 brute=" << bruteDistance(4, ring, 1, 4) << " method=" << floyd(4, ring)[1][4] << "\n";
    // P2: roads 1-2 (1), 2-3 (1) and an isolated town 4: how many pairs u < v are at distance at most 2?
    auto small = twoWay({{1, 2, 1}, {2, 3, 1}});
    auto table = floyd(4, small);
    int methodPairs = 0, brutePairs = 0;
    for (int u = 1; u <= 4; u++)
        for (int v = u + 1; v <= 4; v++) {
            methodPairs += table[u][v] <= 2;
            brutePairs += bruteDistance(4, small, u, v) <= 2;
        }
    cout << "P2 brute=" << brutePairs << " method=" << methodPairs << "\n";
    // N1: arrows 1>2 (1) and 2>1 (-2): the cycle 1 > 2 > 1 has total -1, so the distance from 1 to 2 is unbounded.
    vector<array<long long, 3>> loop = {{1, 2, 1}, {2, 1, -2}};
    cout << "N1 brute=" << (negativeCycle(2, loop) ? string("unbounded") : to_string(bruteDistance(2, loop, 1, 2))) << " method=" << floyd(2, loop)[1][2] << "\n";
}
