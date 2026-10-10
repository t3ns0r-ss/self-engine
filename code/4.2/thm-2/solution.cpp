#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.2. A cycle of a simple undirected graph as a list of vertices (empty if there is none). Walk with a queue, keep parent
// and depth; an edge to a marked vertex other than the parent closes a cycle with the two climbs to their meeting vertex.
vector<int> findCycle(const vector<vector<int>>& adj) {
    vector<int> parent(adj.size(), 0), depth(adj.size(), -1);  // depth -1: not marked yet
    for (int s = 1; s < (int)adj.size(); s++) {
        if (depth[s] != -1) continue;
        depth[s] = 0;
        vector<int> todo = {s};  // a queue: read from the front, add at the back
        for (size_t i = 0; i < todo.size(); i++) {
            int u = todo[i];
            for (int w : adj[u]) {
                if (w == parent[u]) continue;  // the edge we came along
                if (depth[w] == -1) {
                    depth[w] = depth[u] + 1, parent[w] = u;
                    todo.push_back(w);
                    continue;
                }
                vector<int> left, right;  // a non-tree edge u-w: climb from both ends
                for (int a = u, b = w; a != b;) {
                    if (depth[a] >= depth[b]) left.push_back(a), a = parent[a];
                    else right.push_back(b), b = parent[b];
                    if (a == b) left.push_back(a);  // the meeting vertex
                }
                left.insert(left.end(), right.rbegin(), right.rend());
                return left;
            }
        }
    }
    return {};
}
// snippet:end

string show(int n, vector<pair<int, int>> edges) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : edges) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> cycle = findCycle(adj);
    if (cycle.empty()) return "no cycle";
    string out = "cycle:";
    for (int v : cycle) out += " " + to_string(v);
    return out;
}

int main() {
    cout << "edges 1-2 2-3 1-3 3-4: " << show(4, {{1, 2}, {2, 3}, {1, 3}, {3, 4}}) << "\n";
    cout << "path 1-2-3: " << show(3, {{1, 2}, {2, 3}}) << "\n";
    cout << "square 1-2 2-3 3-4 4-1: " << show(4, {{1, 2}, {2, 3}, {3, 4}, {4, 1}}) << "\n";
    // Check against a search for a cycle by ordered tuples, and against the count m > n - components, on every simple graph with 5 vertices.
    int n = 5;
    vector<pair<int, int>> pairs;
    for (int a = 1; a <= n; a++)
        for (int b = a + 1; b <= n; b++) pairs.push_back({a, b});
    for (int mask = 0; mask < (1 << pairs.size()); mask++) {
        vector<vector<int>> adj(n + 1);
        bool edge[6][6] = {};
        int m = 0;
        for (size_t i = 0; i < pairs.size(); i++) {
            if (!(mask >> i & 1)) continue;
            auto [a, b] = pairs[i];
            adj[a].push_back(b);
            adj[b].push_back(a);
            edge[a][b] = edge[b][a] = true;
            m++;
        }
        bool bruteCycle = false;
        vector<int> perm = {1, 2, 3, 4, 5};
        do {
            for (int k = 3; k <= 5; k++) {
                bool all = true;
                for (int i = 0; i < k; i++)
                    if (!edge[perm[i]][perm[(i + 1) % k]]) all = false;
                if (all) bruteCycle = true;
            }
        } while (next_permutation(perm.begin(), perm.end()));
        // components by label propagation
        int label[6];
        for (int v = 1; v <= n; v++) label[v] = v;
        for (int round = 0; round < n; round++)
            for (auto [a, b] : pairs)
                if (edge[a][b]) label[a] = label[b] = min(label[a], label[b]);
        set<int> comps;
        for (int v = 1; v <= n; v++) comps.insert(label[v]);
        bool formula = m > n - (int)comps.size();
        vector<int> cycle = findCycle(adj);
        if (cycle.empty() == bruteCycle || bruteCycle != formula) return 1;
        if (!cycle.empty()) {
            if (cycle.size() < 3) return 1;
            set<int> distinct(cycle.begin(), cycle.end());
            if (distinct.size() != cycle.size()) return 1;
            for (size_t i = 0; i < cycle.size(); i++)
                if (!edge[cycle[i]][cycle[(i + 1) % cycle.size()]]) return 1;
        }
    }
}
