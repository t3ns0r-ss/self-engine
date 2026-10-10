#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX / 4;

// Method: Bellman-Ford (Theorem 4.3.3); returns the distance from 1 to t, or "unbounded" if round n still changes something.
string bellman(int n, const vector<array<long long, 3>>& edges, int t) {
    vector<long long> dist(n + 1, INF);
    dist[1] = 0;
    for (int round = 1; round <= n; round++) {
        bool changed = false;
        for (auto [u, v, w] : edges)
            if (dist[u] < INF && dist[u] + w < dist[v]) dist[v] = dist[u] + w, changed = true;
        if (!changed) break;
        if (round == n) return "unbounded";
    }
    return to_string(dist[t]);
}

// Brute force: the smallest length over all simple paths from 1 to t (each vertex at most once), by recursion.
void tryPaths(int u, int t, long long length, vector<bool>& seen, const vector<array<long long, 3>>& edges, long long& best, bool longest) {
    if (u == t) {
        best = longest ? max(best, length) : min(best, length);
        return;
    }
    seen[u] = true;
    for (auto [a, b, w] : edges)
        if (a == u && !seen[b]) tryPaths(b, t, length + w, seen, edges, best, longest);
    seen[u] = false;
}

int main() {
    // P1: arrows 1>2 (2), 2>3 (-4), 1>3 (1); the shortest distance from 1 to 3.
    vector<array<long long, 3>> edges = {{1, 2, 2}, {2, 3, -4}, {1, 3, 1}};
    long long best = INF;
    vector<bool> seen(4, false);
    tryPaths(1, 3, 0, seen, edges, best, false);
    cout << "P1 brute=" << best << " method=" << bellman(3, edges, 3) << "\n";
    // N1: two-way roads 1-2, 2-3, 1-3 of length 1 each; the LONGEST route from 1 to 3 that visits no place twice. Negating the
    // lengths and asking for the shortest route is the idea of the method; every road becomes two arrows of weight -1.
    vector<array<long long, 3>> roads = {{1, 2, 1}, {2, 1, 1}, {2, 3, 1}, {3, 2, 1}, {1, 3, 1}, {3, 1, 1}};
    long long longest = -INF;
    vector<bool> seen2(4, false);
    tryPaths(1, 3, 0, seen2, roads, longest, true);
    vector<array<long long, 3>> negated;
    for (auto [a, b, w] : roads) negated.push_back({a, b, -w});
    cout << "N1 brute=" << longest << " method=" << bellman(3, negated, 3) << "\n";
}
