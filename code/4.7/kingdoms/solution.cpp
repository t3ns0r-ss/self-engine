/*
Problem: kingdoms (CSES 1683 style).
Input: n m, then m lines "a b": a one-way teleporter from planet a to planet b. Two planets are in one kingdom if each can be reached from the other.
Output: the number of kingdoms, then n numbers: the kingdom of each planet, numbered 1, 2, ... in the order of the first planet that belongs to them.
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
// Theorem 4.7.5, then renumber the groups by the first planet in each (so that the answer does not depend on the walk).
vector<int> kingdomOfEach(const Digraph& adj, int& count) {
    auto comp = stronglyConnected(adj, count);
    vector<int> newName(count + 1, 0), kingdom(adj.size(), 0);
    int next = 0;
    for (int v = 1; v < (int)adj.size(); v++) {
        if (!newName[comp[v]]) newName[comp[v]] = ++next;
        kingdom[v] = newName[comp[v]];
    }
    return kingdom;
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
    int count;
    auto kingdom = kingdomOfEach(adj, count);
    cout << count << "\n";
    for (int v = 1; v <= n; v++) cout << kingdom[v] << (v < n ? ' ' : '\n');
}
