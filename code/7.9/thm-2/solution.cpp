#include <bits/stdc++.h>
using namespace std;

// The matrix version of maxFlow from Theorem 7.9.1, with room for 6 items and the two special vertices.
const int N = 8;
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
// Theorem 7.9.2. Item i pays a[i] if it takes side S and b[i] if it takes side T.
// For every triple (i, j, w) in pairs, the penalty w is paid when i is on side S and j is on side T.
// Returns the smallest total cost over all 2^n ways to choose the sides (maxFlow is the function of Theorem 7.9.1).
long long cheapestSides(int n, vector<long long> a, vector<long long> b, vector<array<long long, 3>> pairs) {
    int s = n, t = n + 1;  // the two special vertices
    memset(cap, 0, sizeof cap);
    for (int i = 0; i < n; i++) {
        cap[s][i] += b[i];  // this edge is cut exactly when i is on side T
        cap[i][t] += a[i];  // this edge is cut exactly when i is on side S
    }
    for (auto [i, j, w] : pairs) cap[i][j] += w;  // cut exactly when i is on side S and j on side T
    return maxFlow(s, t);
}
// snippet:end

long long bruteForce(int n, const vector<long long>& a, const vector<long long>& b, const vector<array<long long, 3>>& pairs) {
    long long best = LLONG_MAX;
    for (int mask = 0; mask < (1 << n); mask++) {  // bit i set: item i is on side S
        long long cost = 0;
        for (int i = 0; i < n; i++) cost += (mask >> i & 1) ? a[i] : b[i];
        for (auto [i, j, w] : pairs)
            if ((mask >> i & 1) && !(mask >> j & 1)) cost += w;
        best = min(best, cost);
    }
    return best;
}

int main() {
    auto show = [&](const char* name, int n, vector<long long> a, vector<long long> b, vector<array<long long, 3>> pairs) {
        long long viaCut = cheapestSides(n, a, b, pairs);
        long long brute = bruteForce(n, a, b, pairs);
        cout << name << ": cheapest = " << viaCut << " (all 2^" << n << " choices give " << brute << ")\n";
        if (viaCut != brute) exit(1);
    };
    show("two items", 2, {2, 6}, {5, 1}, {{0, 1, 3}});
    show("a cycle of pairs", 3, {4, 4, 4}, {4, 4, 4}, {{0, 1, 1}, {1, 2, 1}, {2, 0, 1}});
    show("a very large penalty", 2, {1, 1}, {9, 9}, {{0, 1, 100}});
    show("free items", 3, {0, 0, 0}, {0, 0, 0}, {});

    mt19937 rng(7);
    for (int round = 0; round < 20000; round++) {
        int n = rng() % 6 + 1;
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; i++) { a[i] = rng() % 7; b[i] = rng() % 7; }
        vector<array<long long, 3>> pairs;
        int m = rng() % 8;
        for (int k = 0; k < m; k++) {
            int i = rng() % n, j = rng() % n;
            if (i != j) pairs.push_back({i, j, (long long)(rng() % 6)});
        }
        if (cheapestSides(n, a, b, pairs) != bruteForce(n, a, b, pairs)) return 1;
    }
}
