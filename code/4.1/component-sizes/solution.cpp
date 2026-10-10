/*
Problem: sizes of the connected components.
Input: n m, then m lines "a b": an undirected edge between a and b.
Output: the number of components, then their sizes in increasing order.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.1.2. The size of every connected component of a graph with vertices 1..n (adj[0] is unused).
vector<int> componentSizes(const vector<vector<int>>& adj) {
    int n = adj.size() - 1;
    vector<bool> marked(n + 1, false);
    vector<int> sizes;
    for (int s = 1; s <= n; s++) {
        if (marked[s]) continue;  // s belongs to a component that was already walked
        int size = 0;
        vector<int> stack = {s};
        marked[s] = true;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            size++;
            for (int w : adj[u]) {
                if (!marked[w]) {
                    marked[w] = true;
                    stack.push_back(w);
                }
            }
        }
        sizes.push_back(size);
    }
    return sizes;
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
    vector<int> sizes = componentSizes(adj);
    sort(sizes.begin(), sizes.end());
    cout << sizes.size() << "\n";
    for (size_t i = 0; i < sizes.size(); i++) cout << (i ? " " : "") << sizes[i];
    cout << "\n";
}
