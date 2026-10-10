#include <bits/stdc++.h>
using namespace std;

// Method: with c components, a simple undirected graph has m - (n - c) edges beyond a forest (Theorem 4.2.2). Arrows are read as edges.
int extraEdges(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : edges) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<bool> marked(n + 1, false);
    int components = 0;
    for (int s = 1; s <= n; s++) {
        if (marked[s]) continue;
        components++;
        vector<int> stack = {s};
        marked[s] = true;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (int w : adj[u])
                if (!marked[w]) {
                    marked[w] = true;
                    stack.push_back(w);
                }
        }
    }
    return (int)edges.size() - (n - components);
}

// Brute force 1: is the undirected graph a forest? Remove vertices of degree 0 or 1 until none is left; edges left mean a cycle.
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
// Brute force 2: the fewest edges whose removal leaves no cycle (try every subset).
int fewestToRemove(int n, const vector<pair<int, int>>& edges) {
    int m = edges.size(), best = m;
    for (int mask = 0; mask < (1 << m); mask++) {
        vector<pair<int, int>> kept;
        for (int i = 0; i < m; i++)
            if (!(mask >> i & 1)) kept.push_back(edges[i]);
        if (!hasCycle(n, kept)) best = min(best, __builtin_popcount(mask));
    }
    return best;
}
// Brute force 3: does the DIRECTED graph have a cycle? Some vertex reaches itself (closure).
bool directedCycle(int n, const vector<pair<int, int>>& arrows) {
    vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));
    for (auto [a, b] : arrows) reach[a][b] = true;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (reach[i][k] && reach[k][j]) reach[i][j] = true;
    for (int v = 1; v <= n; v++)
        if (reach[v][v]) return true;
    return false;
}

int main() {
    // P1: six computers, cables 1-2, 2-3, 3-1, 4-5, 5-6; the fewest cables to remove so that no loop of cables remains.
    vector<pair<int, int>> cables = {{1, 2}, {2, 3}, {3, 1}, {4, 5}, {5, 6}};
    cout << "P1 brute=" << fewestToRemove(6, cables) << " method=" << extraEdges(6, cables) << "\n";
    // N1: one-way roads 1>2, 1>3, 2>3: is there a directed cycle? The edge count m > n - c reads them as two-way roads.
    vector<pair<int, int>> arrows = {{1, 2}, {1, 3}, {2, 3}};
    cout << "N1 brute=" << (directedCycle(3, arrows) ? "yes" : "no") << " method=" << (extraEdges(3, arrows) > 0 ? "yes" : "no") << "\n";
}
