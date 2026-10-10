#include <bits/stdc++.h>
using namespace std;

using Digraph = vector<vector<int>>;

vector<int> walk(const Digraph& g, int s, vector<bool>& seen) {
    vector<int> done;
    vector<pair<int, int>> stack = {{s, 0}};  // (vertex, how many of its edges were looked at)
    seen[s] = true;
    while (!stack.empty()) {
        auto [v, i] = stack.back();
        if (i == (int)g[v].size()) done.push_back(v), stack.pop_back();
        else {
            stack.back().second++;
            if (!seen[g[v][i]]) seen[g[v][i]] = true, stack.push_back({g[v][i], 0});
        }
    }
    return done;
}
vector<int> stronglyConnected(const Digraph& adj, int& count) {
    int n = adj.size() - 1;
    Digraph rev(n + 1);
    for (int v = 1; v <= n; v++) for (int to : adj[v]) rev[to].push_back(v);
    vector<bool> seen(n + 1, false);
    vector<int> finish, comp(n + 1, 0);
    for (int s = 1; s <= n; s++) if (!seen[s]) for (int v : walk(adj, s, seen)) finish.push_back(v);
    seen.assign(n + 1, false), count = 0;
    for (int i = n - 1; i >= 0; i--) {  // the vertex that finished last first; each walk is one component, numbered 1, 2, ... as found
        if (seen[finish[i]]) continue;
        count++;
        for (int v : walk(rev, finish[i], seen)) comp[v] = count;
    }
    return comp;
}

// snippet:begin
// Theorem 4.7.6. A vertex s reaches every vertex exactly when its component is the only component that has no edge entering it.
bool reachesEverything(const Digraph& adj, int s) {
    int count;
    auto comp = stronglyConnected(adj, count);
    vector<bool> entered(count + 1, false);
    for (int v = 1; v < (int)adj.size(); v++)
        for (int to : adj[v])
            if (comp[v] != comp[to]) entered[comp[to]] = true;  // an edge between two different components
    for (int c = 1; c <= count; c++)
        if (!entered[c] && c != comp[s]) return false;  // another source that s cannot reach
    return !entered[comp[s]];
}
// snippet:end

// Test helpers: random directed graphs and the reachability table by Floyd-Warshall.
Digraph randomDigraph(mt19937& rng, int n, int m) {
    Digraph adj(n + 1);
    for (int i = 0; i < m; i++) adj[rng() % n + 1].push_back(rng() % n + 1);
    return adj;
}
vector<vector<bool>> reachability(const Digraph& adj) {
    int n = adj.size() - 1;
    vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));
    for (int v = 1; v <= n; v++) {
        reach[v][v] = true;
        for (int to : adj[v]) reach[v][to] = true;
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (reach[i][k] && reach[k][j]) reach[i][j] = true;
    return reach;
}

int main() {
    {
        Digraph adj(5);
        adj[1] = {2, 3}, adj[2] = {4}, adj[3] = {4}, adj[4] = {};
        cout << "1->2, 1->3, 2->4, 3->4: from 1 " << reachesEverything(adj, 1) << ", from 2 " << reachesEverything(adj, 2) << "\n";
    }
    {
        Digraph adj(4);
        adj[1] = {2}, adj[2] = {1}, adj[3] = {1};
        cout << "1<->2 and 3->1: from 1 " << reachesEverything(adj, 1) << ", from 3 " << reachesEverything(adj, 3) << "\n";
    }
    mt19937 rng(4706);
    for (int trial = 0; trial < 30000; trial++) {
        int n = rng() % 8 + 1, m = rng() % 14;
        auto adj = randomDigraph(rng, n, m);
        auto reach = reachability(adj);
        for (int s = 1; s <= n; s++) {
            bool all = true;
            for (int v = 1; v <= n; v++) all = all && reach[s][v];
            if (reachesEverything(adj, s) != all) return 1;
        }
    }
}
