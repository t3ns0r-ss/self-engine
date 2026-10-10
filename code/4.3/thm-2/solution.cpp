#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.3.2. Shortest distance from s when every weight is 0 or 1: a deque takes the place of the heap (INT_MAX if unreachable).
vector<int> zeroOneBfs(const vector<vector<pair<int, int>>>& adj, int s) {
    vector<int> dist(adj.size(), INT_MAX);
    deque<int> line;
    dist[s] = 0;
    line.push_back(s);
    while (!line.empty()) {
        int u = line.front();
        line.pop_front();
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) line.push_front(v);  // same distance as u: it goes to the front
                else line.push_back(v);          // one more than u: it goes to the back
            }
        }
    }
    return dist;
}
// snippet:end

string show(const vector<int>& dist, int n) {
    string out = "dist:";
    for (int v = 1; v <= n; v++) out += " " + (dist[v] == INT_MAX ? string("-") : to_string(dist[v]));
    return out;
}

int main() {
    {
        vector<vector<pair<int, int>>> adj(5);
        adj[1] = {{2, 1}, {3, 0}};
        adj[3] = {{2, 0}, {4, 1}};
        adj[2] = {{4, 1}};
        cout << "arrows 1>2 (1), 1>3 (0), 3>2 (0), 3>4 (1), 2>4 (1), from 1: " << show(zeroOneBfs(adj, 1), 4) << "\n";
    }
    {
        vector<vector<pair<int, int>>> adj(6);
        auto edge = [&](int a, int b, int w) {
            adj[a].push_back({b, w});
            adj[b].push_back({a, w});
        };
        edge(1, 2, 1);
        edge(2, 3, 1);
        edge(3, 4, 0);
        edge(4, 5, 1);
        edge(1, 5, 1);
        cout << "edges 1-2 (1), 2-3 (1), 3-4 (0), 4-5 (1), 1-5 (1), from 1: " << show(zeroOneBfs(adj, 1), 5) << "\n";
    }
    {
        vector<vector<pair<int, int>>> adj(4);
        adj[1] = {{2, 0}};
        cout << "arrow 1>2 (0), vertex 3 alone, from 1: " << show(zeroOneBfs(adj, 1), 3) << "\n";
    }
    // Check against Floyd-Warshall on random directed graphs with weights 0 and 1.
    mt19937 rng(777);
    for (int trial = 0; trial < 20000; trial++) {
        int n = 7;
        const int INF = 1e9;
        vector<vector<pair<int, int>>> adj(n + 1);
        vector<vector<int>> d(n + 1, vector<int>(n + 1, INF));
        for (int v = 1; v <= n; v++) d[v][v] = 0;
        int edges = rng() % 18;
        for (int i = 0; i < edges; i++) {
            int a = rng() % n + 1, b = rng() % n + 1, w = rng() % 2;
            adj[a].push_back({b, w});
            d[a][b] = min(d[a][b], w);
        }
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (d[i][k] < INF && d[k][j] < INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        int s = rng() % n + 1;
        auto dist = zeroOneBfs(adj, s);
        for (int v = 1; v <= n; v++)
            if ((d[s][v] >= INF ? INT_MAX : d[s][v]) != dist[v]) return 1;
    }
}
