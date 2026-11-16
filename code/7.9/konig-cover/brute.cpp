#include <bits/stdc++.h>
using namespace std;

// Brute force: the matching by the recursion over left vertices, the independent set by trying every set of vertices.
int L, R;
vector<int> adj[8];
int matching(int i, int used) {
    if (i == L) return 0;
    int best = matching(i + 1, used);
    for (int v : adj[i])
        if (!(used >> v & 1)) best = max(best, 1 + matching(i + 1, used | 1 << v));
    return best;
}
int main() {
    int m;
    cin >> L >> R >> m;
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        edges.push_back({u - 1, v - 1});
    }
    int independent = 0;
    for (int mask = 0; mask < (1 << (L + R)); mask++) {  // bit u: left u; bit L + v: right v
        bool ok = true;
        for (auto [u, v] : edges)
            if ((mask >> u & 1) && (mask >> (L + v) & 1)) { ok = false; break; }
        if (ok) independent = max(independent, __builtin_popcount(mask));
    }
    cout << matching(0, 0) << " " << independent << "\n";
}
