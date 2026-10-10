#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.1. Give every vertex colour 0 or 1 so that every edge joins different colours; returns false if that is impossible.
bool twoColour(const vector<vector<int>>& adj, vector<int>& colour) {
    int n = adj.size() - 1;
    colour.assign(n + 1, -1);  // -1 means "not coloured yet"
    for (int s = 1; s <= n; s++) {
        if (colour[s] != -1) continue;
        colour[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int w : adj[u]) {
                if (colour[w] == -1) {
                    colour[w] = 1 - colour[u];  // the opposite colour of its neighbour
                    q.push(w);
                } else if (colour[w] == colour[u]) {
                    return false;  // an edge inside one colour
                }
            }
        }
    }
    return true;
}
// snippet:end

void show(int n, vector<pair<int, int>> edges) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : edges) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> colour;
    if (!twoColour(adj, colour)) {
        cout << "impossible\n";
        return;
    }
    cout << "colours:";
    for (int v = 1; v <= n; v++) cout << ' ' << colour[v];
    cout << "\n";
}

int main() {
    cout << "path 1-2-3-4: ";
    show(4, {{1, 2}, {2, 3}, {3, 4}});
    cout << "triangle 1-2-3: ";
    show(3, {{1, 2}, {2, 3}, {1, 3}});
    cout << "edges 1-2 3-4 4-5, vertex 6 alone: ";
    show(6, {{1, 2}, {3, 4}, {4, 5}});
    // Check against all 2^n colourings and against the search for an odd cycle, on every graph with 5 vertices.
    int n = 5;
    vector<pair<int, int>> pairs;
    for (int a = 1; a <= n; a++)
        for (int b = a + 1; b <= n; b++) pairs.push_back({a, b});
    for (int mask = 0; mask < (1 << pairs.size()); mask++) {
        vector<vector<int>> adj(n + 1);
        bool edge[6][6] = {};
        for (size_t i = 0; i < pairs.size(); i++) {
            if (!(mask >> i & 1)) continue;
            auto [a, b] = pairs[i];
            adj[a].push_back(b);
            adj[b].push_back(a);
            edge[a][b] = edge[b][a] = true;
        }
        bool bruteColourable = false;
        for (int c = 0; c < (1 << n) && !bruteColourable; c++) {
            bool ok = true;
            for (size_t i = 0; i < pairs.size(); i++)
                if ((mask >> i & 1) && ((c >> (pairs[i].first - 1) & 1) == (c >> (pairs[i].second - 1) & 1))) ok = false;
            if (ok) bruteColourable = true;
        }
        // An odd cycle of length 3 or 5: an ordered tuple of distinct vertices with every cyclic neighbour pair an edge.
        bool oddCycle = false;
        vector<int> perm = {1, 2, 3, 4, 5};
        do {
            for (int k : {3, 5}) {
                bool all = true;
                for (int i = 0; i < k; i++)
                    if (!edge[perm[i]][perm[(i + 1) % k]]) all = false;
                if (all) oddCycle = true;
            }
        } while (next_permutation(perm.begin(), perm.end()));
        vector<int> colour;
        bool got = twoColour(adj, colour);
        if (got != bruteColourable || got == oddCycle) return 1;
        if (got)
            for (auto [a, b] : pairs)
                if (edge[a][b] && colour[a] == colour[b]) return 1;
    }
}
