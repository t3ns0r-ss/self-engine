/*
Problem: flight routes check (CSES 1682 style).
Input: n m, then m lines "a b": a one-way flight from city a to city b.
Output: YES if one can travel from every city to every other city, otherwise NO.
*/
#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<pair<int, int>>>;
using Digraph = vector<vector<int>>;

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

// snippet:begin
// Theorems 4.7.5 and 4.7.6. With the groups numbered in the order found, every edge goes to the same or a larger number, so if there is more
// than one group, no city of the last group can reach a city of the first. A pair (from, to) with no route is returned, or {0, 0}.
pair<int, int> unreachablePair(const Digraph& adj) {
    int count;
    auto comp = stronglyConnected(adj, count);
    if (count == 1) return {0, 0};
    int from = 0, to = 0;
    for (int v = 1; v < (int)adj.size(); v++) {
        if (comp[v] == count) from = v;
        if (comp[v] == 1) to = v;
    }
    return {from, to};
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    Digraph adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }
    auto [from, to] = unreachablePair(adj);
    if (from) {  // check the pair with a plain search
        vector<bool> seen(n + 1, false);
        vector<int> stack = {from};
        seen[from] = true;
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            for (int u : adj[v])
                if (!seen[u]) seen[u] = true, stack.push_back(u);
        }
        if (seen[to]) return 1;
    }
    cout << (from ? "NO" : "YES") << "\n";
}
