/*
Problem: sizes of the connected components (the same task as the template "component-sizes", solved with recursion).
Input: n m, then m lines "a b": an undirected edge between a and b.
Output: the number of components, then their sizes in increasing order.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.1.1 written as a recursive depth-first search: marks everything reachable from u and returns how many vertices it marked.
int dfs(const vector<vector<int>>& adj, vector<bool>& marked, int u) {
    marked[u] = true;
    int count = 1;
    for (int w : adj[u]) {
        if (!marked[w]) count += dfs(adj, marked, w);
    }
    return count;
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
    vector<bool> marked(n + 1, false);
    vector<int> sizes;
    for (int s = 1; s <= n; s++)
        if (!marked[s]) sizes.push_back(dfs(adj, marked, s));
    sort(sizes.begin(), sizes.end());
    cout << sizes.size() << "\n";
    for (size_t i = 0; i < sizes.size(); i++) cout << (i ? " " : "") << sizes[i];
    cout << "\n";
}
