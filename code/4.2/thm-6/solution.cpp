#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.6. Among all orders where every edge goes from an earlier to a later vertex, the one that puts vertex 1 as early as
// possible, then vertex 2, and so on. Built from the back: the largest vertex with no remaining edge out of it takes the last free place.
vector<int> earliestSmallOrder(const vector<vector<int>>& adj) {
    int n = adj.size() - 1;
    vector<vector<int>> before(n + 1);  // before[w] lists the vertices with an edge to w
    vector<int> outDegree(n + 1, 0), order(n);
    for (int u = 1; u <= n; u++)
        for (int w : adj[u]) before[w].push_back(u), outDegree[u]++;
    priority_queue<int> sinks;  // the largest sink first
    for (int v = 1; v <= n; v++)
        if (outDegree[v] == 0) sinks.push(v);
    for (int place = n - 1; place >= 0; place--) {
        if (sinks.empty()) return {};  // a directed cycle is left
        int v = sinks.top();
        sinks.pop();
        order[place] = v;
        for (int u : before[v])
            if (--outDegree[u] == 0) sinks.push(u);
    }
    return order;
}
// snippet:end

void show(int n, vector<pair<int, int>> arrows) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : arrows) adj[a].push_back(b);
    cout << "order:";
    for (int v : earliestSmallOrder(adj)) cout << ' ' << v;
    cout << "\n";
}

int main() {
    cout << "arrows 3>1 (3 vertices): ";
    show(3, {{3, 1}});
    cout << "arrows 2>1 2>3 (4 vertices): ";
    show(4, {{2, 1}, {2, 3}});
    cout << "arrows 1>2 2>3: ";
    show(3, {{1, 2}, {2, 3}});
    // Check against all valid orders: the one whose positions of 1, 2, 3, ... are smallest, on every digraph with 4 vertices.
    int n = 4;
    vector<pair<int, int>> pairs;
    for (int a = 1; a <= n; a++)
        for (int b = 1; b <= n; b++)
            if (a != b) pairs.push_back({a, b});
    for (int mask = 0; mask < (1 << pairs.size()); mask++) {
        vector<vector<int>> adj(n + 1);
        vector<pair<int, int>> arrows;
        for (size_t i = 0; i < pairs.size(); i++)
            if (mask >> i & 1) {
                adj[pairs[i].first].push_back(pairs[i].second);
                arrows.push_back(pairs[i]);
            }
        vector<int> best, bestPositions, perm = {1, 2, 3, 4};
        do {
            vector<int> position(n + 1);
            for (int i = 0; i < n; i++) position[perm[i]] = i;
            bool ok = true;
            for (auto [a, b] : arrows)
                if (position[a] >= position[b]) ok = false;
            if (!ok) continue;
            vector<int> positions(position.begin() + 1, position.end());
            if (best.empty() || positions < bestPositions) best = perm, bestPositions = positions;
        } while (next_permutation(perm.begin(), perm.end()));
        if (earliestSmallOrder(adj) != best) return 1;
    }
}
