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

int main() {
    // P1: subtree sizes of the tree 1-2, 1-3, 3-4, 3-5 rooted at 1. Brute force: count, for each vertex, the vertices whose parent chain passes it.
    {
        vector<vector<int>> adj(6);
        auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
        edge(1, 2), edge(1, 3), edge(3, 4), edge(3, 5);
        auto t = rootAt(adj, 1);
        vector<int> size(6, 1);
        for (int i = 4; i > 0; i--) size[t.parent[t.order[i]]] += size[t.order[i]];
        string brute, method;
        for (int v = 1; v <= 5; v++) {
            int count = 0;
            for (int u = 1; u <= 5; u++)
                for (int x = u; x != 0; x = t.parent[x]) if (x == v) { count++; break; }
            brute += (v > 1 ? "," : "") + to_string(count);
            method += (v > 1 ? "," : "") + to_string(size[v]);
        }
        cout << "P1 brute=" << brute << " method=" << method << "\n";
    }
    // N1: the path 1-2-3-4 rooted at 1; how far is the vertex farthest from vertex 4? The subtree of 4 only reaches downwards: height 0.
    {
        vector<vector<int>> adj(5);
        auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
        edge(1, 2), edge(2, 3), edge(3, 4);
        auto t = rootAt(adj, 1);
        vector<int> height(5, 0);
        for (int i = 3; i > 0; i--) { int v = t.order[i]; height[t.parent[v]] = max(height[t.parent[v]], height[v] + 1); }
        int brute = 0;
        for (int u = 1; u <= 4; u++) brute = max(brute, abs(u - 4));  // on a path, the distance is the difference of the numbers
        cout << "N1 brute=" << brute << " method=" << height[4] << "\n";
    }
}
