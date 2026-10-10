/*
Problem: loops of cables.
Input: n m, then m lines "a b": a cable between computers a and b (no repeated cables, a != b).
Output: the fewest cables to remove so that no loop of cables remains.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.2. The number of edges that must go to leave a forest: m - (n - components) for a simple undirected graph.
int edgesToRemove(const vector<vector<int>>& adj) {
    int n = adj.size() - 1, entries = 0, components = 0;
    vector<bool> marked(n + 1, false);
    for (int s = 1; s <= n; s++) {
        entries += adj[s].size();  // the lists hold every edge twice
        if (marked[s]) continue;
        components++;
        vector<int> stack = {s};
        marked[s] = true;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (int w : adj[u]) {
                if (!marked[w]) {
                    marked[w] = true;
                    stack.push_back(w);
                }
            }
        }
    }
    int m = entries / 2;
    return m - (n - components);
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cout << edgesToRemove(adj) << "\n";
}
