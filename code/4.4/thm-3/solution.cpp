#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.4.3. Edges are {a, b, weight}; side[v] is 0 or 1 and describes the cut. Returns the index of a lightest edge that
// crosses the cut (-1 if none): adding it to a set of edges that lies inside one MST and crosses no cut edge keeps it inside one.
int lightestCrossing(const vector<array<long long, 3>>& edges, const vector<int>& side) {
    int best = -1;
    for (int i = 0; i < (int)edges.size(); i++) {
        auto [a, b, w] = edges[i];
        if (side[a] != side[b] && (best == -1 || w < edges[best][2])) best = i;  // crosses, and lighter than the best so far
    }
    return best;
}
// snippet:end

// All spanning trees of a connected graph with n <= 7 vertices: the bitmasks of n - 1 edges that connect everything.
vector<int> spanningTrees(int n, const vector<array<long long, 3>>& edges) {
    vector<int> trees;
    int m = edges.size();
    for (int mask = 0; mask < (1 << m); mask++) {
        if (__builtin_popcount(mask) != n - 1) continue;
        vector<int> label(n);
        iota(label.begin(), label.end(), 0);
        for (int i = 0; i < m; i++)
            if (mask >> i & 1) {
                int a = label[edges[i][0]], b = label[edges[i][1]];
                for (int& x : label) if (x == b) x = a;
            }
        if (set<int>(label.begin(), label.end()).size() == 1) trees.push_back(mask);
    }
    return trees;
}

int main() {
    vector<array<long long, 3>> edges = {{0, 1, 4}, {1, 2, 2}, {0, 2, 3}, {2, 3, 7}, {1, 3, 5}};
    auto show = [&](vector<int> side) {
        int i = lightestCrossing(edges, side);
        return i < 0 ? string("none") : to_string(edges[i][0]) + "-" + to_string(edges[i][1]) + " (" + to_string(edges[i][2]) + ")";
    };
    cout << "cut {0} | {1,2,3}: " << show({0, 1, 1, 1}) << "\n";
    cout << "cut {0,1,2} | {3}: " << show({0, 0, 0, 1}) << "\n";
    cout << "cut {1} | {0,2,3}: " << show({0, 1, 0, 0}) << "\n";
    // Check against: all spanning trees. Take a random minimum spanning tree T, a random part F of it, and a random cut that no edge
    // of F crosses (each group of F is on one side). Some minimum spanning tree must contain F and the lightest crossing edge.
    mt19937 rng(4403);
    for (int trial = 0; trial < 6000; trial++) {
        int n = rng() % 5 + 2, m = rng() % 6 + n - 1;
        vector<array<long long, 3>> es;
        for (int v = 1; v < n; v++) es.push_back({(long long)(rng() % v), v, (long long)(rng() % 6 + 1)});  // a random tree: connected
        while ((int)es.size() < m) {
            long long a = rng() % n, b = rng() % n;
            if (a != b) es.push_back({a, b, (long long)(rng() % 6 + 1)});
        }
        m = es.size();
        auto trees = spanningTrees(n, es);
        auto weight = [&](int mask) {
            long long s = 0;
            for (int i = 0; i < m; i++) if (mask >> i & 1) s += es[i][2];
            return s;
        };
        long long best = LLONG_MAX;
        for (int t : trees) best = min(best, weight(t));
        vector<int> msts;
        for (int t : trees) if (weight(t) == best) msts.push_back(t);
        int T = msts[rng() % msts.size()], F = 0;
        for (int i = 0; i < m; i++) if ((T >> i & 1) && rng() % 2) F |= 1 << i;
        vector<int> label(n);  // groups of F
        iota(label.begin(), label.end(), 0);
        for (int i = 0; i < m; i++)
            if (F >> i & 1) {
                int a = label[es[i][0]], b = label[es[i][1]];
                for (int& x : label) if (x == b) x = a;
            }
        vector<int> sideOfGroup(n), side(n);
        for (int g = 0; g < n; g++) sideOfGroup[g] = rng() % 2;
        for (int v = 0; v < n; v++) side[v] = sideOfGroup[label[v]];
        int e = lightestCrossing(es, side);
        if (e < 0) continue;  // all vertices on one side
        bool ok = false;
        for (int t : msts) if ((t & F) == F && (t >> e & 1)) ok = true;
        if (!ok) return 1;
    }
}
