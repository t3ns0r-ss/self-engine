/*
Problem: AtCoder ABC 333 D, Erase Leaves.
Input: N, then N - 1 lines "u v": the edges of a tree. A leaf is a vertex of degree at most 1; one operation deletes a leaf.
Output: the fewest operations that delete vertex 1.
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
// Example 1. Root the tree at vertex 1. Vertex 1 can be deleted once it is a leaf, i.e. once all subtrees under it but one are deleted.
// The cheapest is to keep the largest subtree under vertex 1: delete all the others and then vertex 1 itself, which is n - (largest).
int fewestDeletions(const vector<vector<int>>& adj) {
    int n = adj.size() - 1;
    auto t = rootAt(adj, 1);
    vector<int> size(n + 1, 1);
    for (int i = n - 1; i > 0; i--) size[t.parent[t.order[i]]] += size[t.order[i]];
    int largest = 0;
    for (int child : adj[1]) largest = max(largest, size[child]);
    return n - largest;
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
    cout << fewestDeletions(adj) << "\n";
}
