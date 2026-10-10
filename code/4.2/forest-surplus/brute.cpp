#include <bits/stdc++.h>
using namespace std;

// Try every set of edges to remove; a graph has no cycle when removing vertices of degree 0 or 1 again and again removes every edge.
bool hasCycle(int n, const vector<pair<int, int>>& edges) {
    vector<bool> alive(edges.size(), true);
    bool changed = true;
    while (changed) {
        changed = false;
        vector<int> degree(n + 1, 0);
        for (size_t i = 0; i < edges.size(); i++)
            if (alive[i]) degree[edges[i].first]++, degree[edges[i].second]++;
        for (size_t i = 0; i < edges.size(); i++)
            if (alive[i] && (degree[edges[i].first] == 1 || degree[edges[i].second] == 1)) alive[i] = false, changed = true;
    }
    return count(alive.begin(), alive.end(), true) > 0;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& e : edges) cin >> e.first >> e.second;
    int best = m;
    for (int mask = 0; mask < (1 << m); mask++) {
        vector<pair<int, int>> kept;
        for (int i = 0; i < m; i++)
            if (!(mask >> i & 1)) kept.push_back(edges[i]);
        if (!hasCycle(n, kept)) best = min(best, __builtin_popcount(mask));
    }
    cout << best << "\n";
}
