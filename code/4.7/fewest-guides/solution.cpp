/*
Problem: guides in a bus network.
Input: n m, then m lines "a b": a one-way line from stop a to stop b.
Output: the fewest stops to put a guide at, so that every stop can be reached from the stop of some guide.
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
// Theorems 4.7.5 and 4.7.6. Every group that no line enters from another group needs a guide, and one guide in each such group is enough.
int fewestGuides(const Digraph& adj) {
    int count;
    auto comp = stronglyConnected(adj, count);
    vector<bool> entered(count + 1, false);
    for (int v = 1; v < (int)adj.size(); v++)
        for (int to : adj[v])
            if (comp[v] != comp[to]) entered[comp[to]] = true;
    return count - (int)count_if(entered.begin() + 1, entered.end(), [](bool b) { return b; });
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
    cout << fewestGuides(adj) << "\n";
}
