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
    vector<vector<int>> adj(6);
    auto edge = [&](int a, int b) { adj[a].push_back(b), adj[b].push_back(a); };
    edge(1, 2), edge(1, 3), edge(3, 4), edge(3, 5);
    auto t = rootAt(adj, 1);
    // P1: how many vertices lie at depth 0, 1 and 2? Brute force: relax the distances from the root again and again.
    {
        vector<int> dist(6, 1000);
        dist[1] = 0;
        for (int round = 0; round < 5; round++)
            for (int u = 1; u <= 5; u++) for (int v : adj[u]) dist[v] = min(dist[v], dist[u] + 1);
        vector<int> brute(3, 0), method(3, 0);
        for (int v = 1; v <= 5; v++) brute[dist[v]]++, method[t.depth[v]]++;
        auto show = [](const vector<int>& c) { return to_string(c[0]) + "," + to_string(c[1]) + "," + to_string(c[2]); };
        cout << "P1 brute=" << show(brute) << " method=" << show(method) << "\n";
    }
    // P2: the path from vertex 5 up to the root. Brute force: search all simple paths from 5 to 1.
    {
        vector<int> path = {5}, found;
        function<void(int)> go = [&](int u) {
            if (u == 1) { found = path; return; }
            for (int v : adj[u])
                if (find(path.begin(), path.end(), v) == path.end()) path.push_back(v), go(v), path.pop_back();
        };
        go(5);
        vector<int> chain;
        for (int v = 5; v != 0; v = t.parent[v]) chain.push_back(v);
        auto show = [](const vector<int>& p) { string s; for (int v : p) s += (s.empty() ? "" : ",") + to_string(v); return s; };
        cout << "P2 brute=" << show(found) << " method=" << show(chain) << "\n";
    }
    // N1: a forest: the vertex 4 is in another component than the root 1, so it is never reached and keeps the default depth 0.
    {
        vector<vector<int>> forest(5);
        forest[1].push_back(2), forest[2].push_back(1), forest[3].push_back(4), forest[4].push_back(3);
        auto f = rootAt(forest, 1);
        bool reached = find(f.order.begin(), f.order.end(), 4) != f.order.end();
        cout << "N1 brute=" << (reached ? "reachable" : "unreachable") << " method=" << f.depth[4] << "\n";
    }
}
