#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.5. Among all orders in which every edge goes from an earlier to a later vertex, the one that is smallest when read
// as a sequence of vertex numbers (fewer than n vertices come back if the graph has a cycle).
vector<int> smallestOrder(const vector<vector<int>>& adj) {
    int n = adj.size() - 1;
    vector<int> indegree(n + 1, 0), order;
    for (int u = 1; u <= n; u++)
        for (int w : adj[u]) indegree[w]++;
    priority_queue<int, vector<int>, greater<int>> ready;  // the smallest ready vertex first
    for (int v = 1; v <= n; v++)
        if (indegree[v] == 0) ready.push(v);
    while (!ready.empty()) {
        int u = ready.top();
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
    cout << "order:";
    for (int v : smallestOrder(adj)) cout << ' ' << v;
    cout << "\n";
}

int main() {
    cout << "arrows 2>1 (3 vertices): ";
    show(3, {{2, 1}});
    cout << "arrows 1>3 2>3 4>2: ";
    show(4, {{1, 3}, {2, 3}, {4, 2}});
    cout << "arrows 3>1 3>2 1>2: ";
    show(3, {{3, 1}, {3, 2}, {1, 2}});
    // Check against the smallest of all valid orders, on every acyclic graph with 4 vertices whose arrows go as in a random labelling.
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
        vector<int> best, perm = {1, 2, 3, 4};
        do {
            int position[5];
            for (int i = 0; i < n; i++) position[perm[i]] = i;
            bool ok = true;
            for (auto [a, b] : arrows)
                if (position[a] > position[b]) ok = false;
            if (ok && best.empty()) best = perm;  // permutations come in increasing order: the first valid one is the smallest
        } while (next_permutation(perm.begin(), perm.end()));
        vector<int> order = smallestOrder(adj);
        if (best.empty() ? (int)order.size() == n : order != best) return 1;
    }
}
