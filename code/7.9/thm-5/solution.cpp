#include <bits/stdc++.h>
using namespace std;

// The matrix version of maxFlow from Theorem 7.9.1, with room for 4 + 4 vertices and the two special vertices.
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
// Theorem 7.9.5. ok[i][j] is true when left vertex i (0 <= i < L) and right vertex j (0 <= j < R) may be paired.
// Network: s -> i, i -> L + j (when ok[i][j]) and L + j -> t, every capacity 1.
// Returns the size of a largest matching; the pairs are the middle edges whose capacity has dropped to 0.
int matchByFlow(int L, int R, const bool ok[5][5], vector<pair<int, int>>& pairs) {
    int s = L + R, t = L + R + 1;
    memset(cap, 0, sizeof cap);
    for (int i = 0; i < L; i++) cap[s][i] = 1;
    for (int j = 0; j < R; j++) cap[L + j][t] = 1;
    for (int i = 0; i < L; i++)
        for (int j = 0; j < R; j++)
            if (ok[i][j]) cap[i][L + j] = 1;
    int size = (int)maxFlow(s, t);
    for (int i = 0; i < L; i++)
        for (int j = 0; j < R; j++)
            if (ok[i][j] && cap[i][L + j] == 0) pairs.push_back({i, j});  // this edge carries one unit of flow
    return size;
}
// snippet:end

int bruteMatching(int L, int R, const bool ok[5][5], int i, int usedRight) {
    if (i == L) return 0;
    int best = bruteMatching(L, R, ok, i + 1, usedRight);  // left vertex i stays unpaired
    for (int j = 0; j < R; j++)
        if (ok[i][j] && !(usedRight >> j & 1)) best = max(best, 1 + bruteMatching(L, R, ok, i + 1, usedRight | 1 << j));
    return best;
}

int main() {
    auto show = [&](const char* name, int L, int R, vector<pair<int, int>> edges) {
        bool ok[5][5] = {};
        for (auto [i, j] : edges) ok[i][j] = true;
        vector<pair<int, int>> pairs;
        int size = matchByFlow(L, R, ok, pairs);
        cout << name << ": size = " << size << ", pairs";
        for (auto [i, j] : pairs) cout << " (" << i << "," << j << ")";
        cout << "\n";
        if (size != bruteMatching(L, R, ok, 0, 0)) exit(1);
    };
    show("three left vertices", 3, 3, {{0, 0}, {0, 1}, {1, 0}, {2, 0}});
    show("a full square", 2, 2, {{0, 0}, {0, 1}, {1, 0}, {1, 1}});
    show("no edges", 2, 3, {});
    show("one left vertex", 1, 3, {{0, 0}, {0, 1}, {0, 2}});

    // Check every bipartite graph with 1 to 4 vertices on each side: the flow value is the size of a largest matching,
    // and the pairs read from the flow form a matching of that size.
    for (int L = 1; L <= 4; L++)
        for (int R = 1; R <= 4; R++)
            for (int code = 0; code < (1 << (L * R)); code++) {
                bool ok[5][5] = {};
                for (int i = 0; i < L; i++)
                    for (int j = 0; j < R; j++) ok[i][j] = code >> (i * R + j) & 1;
                vector<pair<int, int>> pairs;
                int size = matchByFlow(L, R, ok, pairs);
                if (size != bruteMatching(L, R, ok, 0, 0) || (int)pairs.size() != size) return 1;
                int leftUsed = 0, rightUsed = 0;
                for (auto [i, j] : pairs) {
                    if ((leftUsed >> i & 1) || (rightUsed >> j & 1)) return 1;
                    leftUsed |= 1 << i;
                    rightUsed |= 1 << j;
                }
            }
}
