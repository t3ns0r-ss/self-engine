#include <bits/stdc++.h>
using namespace std;

using Digraph = vector<vector<int>>;

// snippet:begin
// Theorem 4.7.5 (Kosaraju). walk lists the unseen vertices reachable from s in finishing order: pass 1 on the graph, pass 2 on the reversed graph.
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
        // 1 -> 2 -> 3 -> 1 is a cycle; 3 -> 4; 4 <-> 5; 6 is alone with 6 -> 1.
        Digraph adj(7);
        auto edge = [&](int a, int b) { adj[a].push_back(b); };
        edge(1, 2), edge(2, 3), edge(3, 1), edge(3, 4), edge(4, 5), edge(5, 4), edge(6, 1);
        int count;
        auto comp = stronglyConnected(adj, count);
        cout << "cycle 1-2-3, then 3->4, the pair 4<->5, and 6->1: " << count << " components, labels:";
        for (int v = 1; v <= 6; v++) cout << ' ' << comp[v];
        cout << "\n";
    }
    {
        Digraph adj(4);
        adj[1] = {2}, adj[2] = {3};
        int count;
        auto comp = stronglyConnected(adj, count);
        cout << "the path 1->2->3: " << count << " components, labels:";
        for (int v = 1; v <= 3; v++) cout << ' ' << comp[v];
        cout << "\n";
    }
    // Check against the definition: same component exactly when each reaches the other; every edge goes from a smaller to a larger or an
    // equal label (components are numbered in a topological order of the condensation).
    mt19937 rng(4705);
    for (int trial = 0; trial < 30000; trial++) {
        int n = rng() % 8 + 1, m = rng() % 14;
        auto adj = randomDigraph(rng, n, m);
        int count;
        auto comp = stronglyConnected(adj, count);
        auto reach = reachability(adj);
        for (int a = 1; a <= n; a++) {
            for (int b = 1; b <= n; b++)
                if ((reach[a][b] && reach[b][a]) != (comp[a] == comp[b])) return 1;
            for (int to : adj[a])
                if (comp[a] > comp[to]) return 1;
        }
        set<int> labels(comp.begin() + 1, comp.end());
        if ((int)labels.size() != count || *labels.begin() != 1 || *labels.rbegin() != count) return 1;
    }
}
