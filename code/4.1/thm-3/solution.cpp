#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.1.3. The fewest edges from s to every vertex (-1 if unreachable), and for each vertex the previous vertex on one shortest path.
vector<int> bfs(const vector<vector<int>>& adj, int s, vector<int>& parent) {
    vector<int> dist(adj.size(), -1);
    parent.assign(adj.size(), 0);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int w : adj[u]) {
            if (dist[w] == -1) {  // first time w is seen: this is its shortest distance
                dist[w] = dist[u] + 1;
                parent[w] = u;
                q.push(w);
            }
        }
    }
    return dist;
}
// snippet:end

// Same loop, also recording the order in which vertices leave the queue (to check statement (b)).
vector<int> removalOrder(const vector<vector<int>>& adj, int s) {
    vector<int> dist(adj.size(), -1), order;
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int w : adj[u])
            if (dist[w] == -1) {
                dist[w] = dist[u] + 1;
                q.push(w);
            }
    }
    return order;
}

void printRun(int n, vector<pair<int, int>> edges, bool directed, int s, int pathTo) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : edges) {
        adj[a].push_back(b);
        if (!directed) adj[b].push_back(a);
    }
    vector<int> parent;
    vector<int> dist = bfs(adj, s, parent);
    cout << "dist:";
    for (int v = 1; v <= n; v++) cout << ' ' << dist[v];
    if (pathTo != 0) {
        vector<int> path;
        for (int v = pathTo; v != s; v = parent[v]) path.push_back(v);
        path.push_back(s);
        reverse(path.begin(), path.end());
        cout << "; path to " << pathTo << ":";
        for (int v : path) cout << ' ' << v;
    }
    cout << "\n";
}

int main() {
    cout << "n=6, edges 1-2 1-3 2-4 3-4 4-5, from 1 -> ";
    printRun(6, {{1, 2}, {1, 3}, {2, 4}, {3, 4}, {4, 5}}, false, 1, 5);
    cout << "n=4, edges 1-2 2-3 3-4 4-1, from 1 -> ";
    printRun(4, {{1, 2}, {2, 3}, {3, 4}, {4, 1}}, false, 1, 0);
    cout << "n=3, arrows 1>2 2>3 1>3, from 2 -> ";
    printRun(3, {{1, 2}, {2, 3}, {1, 3}}, true, 2, 0);
    // Check against repeated relaxation on every graph with 4 vertices (directed: 2^12) and 5 vertices (undirected: 2^10).
    for (int directed = 0; directed < 2; directed++) {
        int n = directed ? 4 : 5;
        vector<pair<int, int>> pairs;
        for (int a = 1; a <= n; a++)
            for (int b = 1; b <= n; b++)
                if (directed ? a != b : a < b) pairs.push_back({a, b});
        for (int mask = 0; mask < (1 << pairs.size()); mask++) {
            vector<vector<int>> adj(n + 1);
            vector<pair<int, int>> arcs;
            for (size_t i = 0; i < pairs.size(); i++) {
                if (!(mask >> i & 1)) continue;
                auto [a, b] = pairs[i];
                adj[a].push_back(b);
                arcs.push_back({a, b});
                if (!directed) {
                    adj[b].push_back(a);
                    arcs.push_back({b, a});
                }
            }
            for (int s = 1; s <= n; s++) {
                const int INF = 1e9;
                vector<int> best(n + 1, INF);
                best[s] = 0;
                for (int round = 0; round < n; round++)
                    for (auto [a, b] : arcs)
                        if (best[a] < INF) best[b] = min(best[b], best[a] + 1);
                vector<int> parent;
                vector<int> dist = bfs(adj, s, parent);
                for (int v = 1; v <= n; v++) {
                    if (dist[v] != (best[v] == INF ? -1 : best[v])) return 1;
                    if (v == s || dist[v] == -1) continue;
                    // (c): the parent has distance one less and is joined to v by an edge
                    if (dist[parent[v]] != dist[v] - 1) return 1;
                    if (find(adj[parent[v]].begin(), adj[parent[v]].end(), v) == adj[parent[v]].end()) return 1;
                }
                vector<int> order = removalOrder(adj, s);
                for (size_t i = 1; i < order.size(); i++)
                    if (dist[order[i]] < dist[order[i - 1]]) return 1;
            }
        }
    }
}
