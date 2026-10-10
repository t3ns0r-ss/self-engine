#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.3. The vertices in an order where every edge goes from an earlier to a later vertex. Fewer than n vertices come back
// exactly when the directed graph has a cycle.
vector<int> topologicalOrder(const vector<vector<int>>& adj) {
    int n = adj.size() - 1;
    vector<int> indegree(n + 1, 0), order;
    for (int u = 1; u <= n; u++)
        for (int w : adj[u]) indegree[w]++;
    queue<int> ready;  // vertices whose incoming edges have all been used up
    for (int v = 1; v <= n; v++)
        if (indegree[v] == 0) ready.push(v);
    while (!ready.empty()) {
        int u = ready.front();
        ready.pop();
        order.push_back(u);
        for (int w : adj[u])
            if (--indegree[w] == 0) ready.push(w);
    }
    return order;
}
// snippet:end

void show(int n, vector<pair<int, int>> arrows) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : arrows) adj[a].push_back(b);
    vector<int> order = topologicalOrder(adj);
    if ((int)order.size() == n) {
        cout << "order:";
        for (int v : order) cout << ' ' << v;
        cout << "\n";
    } else {
        cout << "cycle: only " << order.size() << " of " << n << " vertices come out\n";
    }
}

int main() {
    cout << "arrows 1>2 1>3 2>4 3>4: ";
    show(4, {{1, 2}, {1, 3}, {2, 4}, {3, 4}});
    cout << "arrows 5>1 1>2 2>3 3>1 3>4: ";
    show(5, {{5, 1}, {1, 2}, {2, 3}, {3, 1}, {3, 4}});
    cout << "arrows 3>1 3>2 1>2: ";
    show(3, {{3, 1}, {3, 2}, {1, 2}});
    // Check against all orders of the vertices, on every directed graph with 4 vertices (2^12).
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
        auto valid = [&](const vector<int>& order) {
            int position[5];
            for (size_t i = 0; i < order.size(); i++) position[order[i]] = i;
            for (auto [a, b] : arrows)
                if (position[a] > position[b]) return false;
            return true;
        };
        bool someOrder = false;
        vector<int> perm = {1, 2, 3, 4};
        do {
            if (valid(perm)) someOrder = true;
        } while (next_permutation(perm.begin(), perm.end()));
        vector<int> order = topologicalOrder(adj);
        if ((int)order.size() == n) {
            if (!someOrder || !valid(order)) return 1;
        } else if (someOrder) {
            return 1;
        }
    }
}
