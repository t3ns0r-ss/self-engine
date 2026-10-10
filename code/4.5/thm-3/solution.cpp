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
// Theorem 4.5.3. The positions tin[v]..tout[v] of the subtree of v in the visit order; u is an ancestor of v (or u = v) exactly
// when tin[u] <= tin[v] <= tout[u].
void eulerRanges(const Rooted& t, vector<int>& tin, vector<int>& tout) {
    int n = t.order.size();
    vector<int> size(n + 1, 1);
    tin.assign(n + 1, 0);
    tout.assign(n + 1, 0);
    for (int i = 0; i < n; i++) tin[t.order[i]] = i;
    for (int i = n - 1; i > 0; i--) size[t.parent[t.order[i]]] += size[t.order[i]];
    for (int v = 1; v <= n; v++) tout[v] = tin[v] + size[v] - 1;  // the subtree is the next size[v] positions
}
// snippet:end

int main() {
    {
        vector<vector<int>> adj(6);
        auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
        edge(1, 2), edge(1, 3), edge(3, 4), edge(3, 5);
        auto t = rootAt(adj, 1);
        vector<int> tin, tout;
        eulerRanges(t, tin, tout);
        cout << "tree 1-2, 1-3, 3-4, 3-5 from 1, ranges:";
        for (int v = 1; v <= 5; v++) cout << ' ' << v << "=[" << tin[v] << ',' << tout[v] << "]";
        cout << "\n";
        cout << "is 3 an ancestor of 4: " << (tin[3] <= tin[4] && tin[4] <= tout[3]) << ", of 2: " << (tin[3] <= tin[2] && tin[2] <= tout[3]) << "\n";
    }
    {
        vector<vector<int>> adj(2);
        auto t = rootAt(adj, 1);
        vector<int> tin, tout;
        eulerRanges(t, tin, tout);
        cout << "one vertex: [" << tin[1] << "," << tout[1] << "]\n";
    }
    // Check against: the ancestor test by following parents, and the subtree as the set of vertices with tin inside the range.
    mt19937 rng(4503);
    auto randomTree = [](mt19937& rng, int n) {
        vector<int> label(n);
        iota(label.begin(), label.end(), 1);
        shuffle(label.begin(), label.end(), rng);
        vector<vector<int>> adj(n + 1);
        for (int i = 1; i < n; i++) {
            int a = label[i], b = label[rng() % i];
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        return adj;
    };
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 9 + 1, root = rng() % n + 1;
        auto adj = randomTree(rng, n);
        auto t = rootAt(adj, root);
        vector<int> tin, tout;
        eulerRanges(t, tin, tout);
        for (int u = 1; u <= n; u++)
            for (int v = 1; v <= n; v++) {
                bool ancestor = false;
                for (int x = v; x != 0; x = t.parent[x]) if (x == u) ancestor = true;
                if (ancestor != (tin[u] <= tin[v] && tin[v] <= tout[u])) return 1;
            }
    }
}
