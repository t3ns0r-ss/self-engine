/*
Problem: levels of a company.
Input: n, then n - 1 lines "a b": a direct reporting line between employees a and b; employee 1 is the boss; the lines form a tree.
Output: the number of employees at each level (the boss is at level 0), for levels 0, 1, 2, ... up to the deepest one, on one line.
*/
#include <bits/stdc++.h>
using namespace std;

struct Rooted {
    vector<int> order, parent, depth;
};
Rooted rootAt(const vector<vector<int>>& adj, int root) {
    int n = adj.size() - 1;
    Rooted t{{}, vector<int>(n + 1, 0), vector<int>(n + 1, 0)};
    vector<int> stack = {root};
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        t.order.push_back(u);
        for (int v : adj[u])
            if (v != t.parent[u]) {  // in a tree the only visited neighbour of u is its parent
                t.parent[v] = u;
                t.depth[v] = t.depth[u] + 1;
                stack.push_back(v);
            }
    }
    return t;
}

// snippet:begin
// Theorem 4.5.1. The number of vertices at each depth when the tree is rooted at vertex 1.
vector<int> countPerDepth(const vector<vector<int>>& adj) {
    auto t = rootAt(adj, 1);
    int deepest = *max_element(t.depth.begin() + 1, t.depth.end());
    vector<int> count(deepest + 1, 0);
    for (int v = 1; v < (int)adj.size(); v++) count[t.depth[v]]++;
    return count;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i + 1 < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    auto count = countPerDepth(adj);
    for (size_t d = 0; d < count.size(); d++) cout << count[d] << (d + 1 < count.size() ? " " : "\n");
}
