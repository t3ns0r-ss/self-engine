#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.5.1. Walk a tree from the root: the visit order (every vertex after its parent), parent[root] = 0, and the depths.
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
// snippet:end

int main() {
    {
        vector<vector<int>> adj(6);
        auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
        edge(1, 2), edge(1, 3), edge(3, 4), edge(3, 5);
        auto t = rootAt(adj, 1);
        cout << "tree 1-2, 1-3, 3-4, 3-5 from 1: order";
        for (int v : t.order) cout << ' ' << v;
        cout << "; parent";
        for (int v = 1; v <= 5; v++) cout << ' ' << t.parent[v];
        cout << "; depth";
        for (int v = 1; v <= 5; v++) cout << ' ' << t.depth[v];
        cout << "\n";
        auto u = rootAt(adj, 4);
        cout << "same tree from 4: depth";
        for (int v = 1; v <= 5; v++) cout << ' ' << u.depth[v];
        cout << "\n";
    }
    {
        vector<vector<int>> adj(2);
        auto t = rootAt(adj, 1);
        cout << "one vertex: order size " << t.order.size() << ", depth " << t.depth[1] << "\n";
    }
    // Check against: distances found by relaxing all edges again and again (no walk), on random trees.
    mt19937 rng(4501);
    auto randomTree = [](mt19937& rng, int n) {  // vertices 1..n, vertex i hangs under a random earlier one, labels shuffled
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
        if ((int)t.order.size() != n) return 1;
        vector<int> dist(n + 1, 1000000), seenAt(n + 1, -1);
        dist[root] = 0;
        for (int round = 0; round < n; round++)
            for (int u = 1; u <= n; u++)
                for (int v : adj[u]) dist[v] = min(dist[v], dist[u] + 1);
        for (int i = 0; i < n; i++) seenAt[t.order[i]] = i;
        for (int v = 1; v <= n; v++) {
            if (t.depth[v] != dist[v]) return 1;
            if (v != root && (seenAt[t.parent[v]] >= seenAt[v] || t.depth[t.parent[v]] + 1 != t.depth[v])) return 1;
        }
    }
}
