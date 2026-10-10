/*
Problem: AtCoder ABC 288 C, Don't be cycle.
Input: N M, then M lines "A B": an edge of a simple undirected graph.
Output: the fewest edges to delete so that the graph has no cycle.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Example 2. The fewest edges to delete so that no cycle remains: the edges beyond one spanning forest, m - (n - components).
int fewestDeletions(int n, int m, const vector<vector<int>>& adj) {
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
            for (int w : adj[u]) {
                if (!marked[w]) {
                    marked[w] = true;
                    stack.push_back(w);
                }
            }
        }
    }
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
    cout << fewestDeletions(n, m, adj) << "\n";
}
