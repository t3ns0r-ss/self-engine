#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.1.4. The fewest edges from the nearest of several sources to every vertex (-1 if no source reaches it):
// all sources start in the queue at distance 0.
vector<int> multiSourceBfs(const vector<vector<int>>& adj, const vector<int>& sources) {
    vector<int> dist(adj.size(), -1);
    queue<int> q;
    for (int s : sources) {
        dist[s] = 0;
        q.push(s);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int w : adj[u]) {
            if (dist[w] == -1) {
                dist[w] = dist[u] + 1;
                q.push(w);
            }
        }
    }
    return dist;
}
// snippet:end

vector<int> singleSource(const vector<vector<int>>& adj, int s) {
    return multiSourceBfs(adj, {s});
}

void printRun(int n, vector<pair<int, int>> edges, vector<int> sources) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : edges) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> dist = multiSourceBfs(adj, sources);
    cout << "dist:";
    for (int v = 1; v <= n; v++) cout << ' ' << dist[v];
    cout << "\n";
}

int main() {
    cout << "path 1-2-3-4-5-6-7, sources 1 and 7 -> ";
    printRun(7, {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}}, {1, 7});
    cout << "n=6, edges 1-2 2-3 4-5, sources 1 and 4 -> ";
    printRun(6, {{1, 2}, {2, 3}, {4, 5}}, {1, 4});
    cout << "cycle 1-2-3-4-5-1, sources 1 and 3 -> ";
    printRun(5, {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 1}}, {1, 3});
    // Check against "run a search from every source and take the smallest" on every undirected graph with 5 vertices and every source set.
    int n = 5;
    vector<pair<int, int>> pairs;
    for (int a = 1; a <= n; a++)
        for (int b = a + 1; b <= n; b++) pairs.push_back({a, b});
    for (int mask = 0; mask < (1 << pairs.size()); mask++) {
        vector<vector<int>> adj(n + 1);
        for (size_t i = 0; i < pairs.size(); i++) {
            if (!(mask >> i & 1)) continue;
            adj[pairs[i].first].push_back(pairs[i].second);
            adj[pairs[i].second].push_back(pairs[i].first);
        }
        for (int srcMask = 1; srcMask < (1 << n); srcMask++) {
            vector<int> sources, best(n + 1, -1);
            for (int s = 1; s <= n; s++) {
                if (!(srcMask >> (s - 1) & 1)) continue;
                sources.push_back(s);
                vector<int> d = singleSource(adj, s);
                for (int v = 1; v <= n; v++)
                    if (d[v] != -1 && (best[v] == -1 || d[v] < best[v])) best[v] = d[v];
            }
            if (multiSourceBfs(adj, sources) != best) {
                // index 0 is unused in both; compare as is
                return 1;
            }
        }
    }
}
