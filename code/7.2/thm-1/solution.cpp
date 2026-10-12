#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> randomDag(int n, mt19937& rng, int percent) {
    vector<int> label(n);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin(), label.end(), rng);
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if ((int)(rng() % 100) < percent) edges.push_back({label[i], label[j]});
    return edges;
}

// snippet:begin
// Theorem 7.2.1. Kahn's algorithm: take a vertex with no incoming edge left, remove it. All n vertices are taken exactly
// when the graph has no directed cycle. indeg[v] = the number of edges into v.
vector<int> topologicalOrder(const vector<vector<int>>& out, vector<int> indeg) {
    int n = out.size();
    vector<int> order;
    for (int v = 0; v < n; v++)
        if (indeg[v] == 0) order.push_back(v);
    for (size_t i = 0; i < order.size(); i++)  // order grows while it is read
        for (int u : out[order[i]])
            if (--indeg[u] == 0) order.push_back(u);
    return order;  // shorter than n if there is a cycle
}
// The largest number of edges of a path that ends at v: dp[v] = max(dp[u] + 1) over the edges u -> v, in topological order.
vector<int> longestEndingAt(const vector<vector<int>>& out, const vector<int>& order) {
    vector<int> dp(out.size(), 0);
    for (int v : order)
        for (int u : out[v]) dp[u] = max(dp[u], dp[v] + 1);
    return dp;
}
// snippet:end

vector<int> indegrees(int n, const vector<pair<int, int>>& edges) {
    vector<int> d(n, 0);
    for (auto [a, b] : edges) d[b]++;
    return d;
}
vector<vector<int>> adjacency(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> out(n);
    for (auto [a, b] : edges) out[a].push_back(b);
    return out;
}
int bruteLongest(int n, const vector<pair<int, int>>& edges) {  // depth-first search from every vertex (the graph is acyclic)
    auto out = adjacency(n, edges);
    function<int(int)> go = [&](int v) {
        int best = 0;
        for (int u : out[v]) best = max(best, 1 + go(u));
        return best;
    };
    int best = 0;
    for (int v = 0; v < n; v++) best = max(best, go(v));
    return best;
}
bool hasCycle(int n, const vector<pair<int, int>>& edges) {  // reachability by repeated relaxation
    vector<vector<char>> reach(n, vector<char>(n, 0));
    for (auto [a, b] : edges) reach[a][b] = 1;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (reach[i][k] && reach[k][j]) reach[i][j] = 1;
    for (int v = 0; v < n; v++)
        if (reach[v][v]) return true;
    return false;
}

int main() {
    vector<pair<int, int>> dag = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {2, 5}};
    auto out = adjacency(6, dag);
    auto order = topologicalOrder(out, indegrees(6, dag));
    cout << "order:";
    for (int v : order) cout << " " << v;
    cout << "\nlongest path ending at each vertex:";
    for (int x : longestEndingAt(out, order)) cout << " " << x;
    cout << "\n";
    vector<pair<int, int>> cyclic = {{0, 1}, {1, 2}, {2, 1}, {2, 3}};
    auto got = topologicalOrder(adjacency(4, cyclic), indegrees(4, cyclic));
    cout << "graph with a cycle: " << got.size() << " of 4 vertices taken\n";
    // Check (not printed): for 3000 random graphs of up to 8 vertices (acyclic ones and ones with cycles), all vertices are taken
    // exactly when there is no cycle; every edge goes forward in the order; and the longest path equals a depth-first search.
    mt19937 rng(5);
    for (int it = 0; it < 3000; it++) {
        int n = 1 + rng() % 8;
        vector<pair<int, int>> edges;
        if (it % 2 == 0) edges = randomDag(n, rng, 30);
        else
            for (int a = 0; a < n; a++)
                for (int b = 0; b < n; b++)
                    if (a != b && rng() % 100 < 15) edges.push_back({a, b});
        auto o = topologicalOrder(adjacency(n, edges), indegrees(n, edges));
        bool cyc = hasCycle(n, edges);
        if (((int)o.size() == n) == cyc) return 1;
        if (!cyc) {
            vector<int> pos(n);
            for (int i = 0; i < n; i++) pos[o[i]] = i;
            for (auto [a, b] : edges)
                if (pos[a] >= pos[b]) return 1;
            auto dp = longestEndingAt(adjacency(n, edges), o);
            if (*max_element(dp.begin(), dp.end()) != bruteLongest(n, edges)) return 1;
        }
    }
}
