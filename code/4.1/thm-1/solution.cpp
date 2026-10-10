#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.1.1. Which vertices can be reached from s? Mark s, then keep taking a marked vertex out of the container and marking its
// unmarked neighbours.
vector<bool> reachable(const vector<vector<int>>& adj, int s) {
    vector<bool> marked(adj.size(), false);
    vector<int> container = {s};  // used as a stack: take from the back
    marked[s] = true;
    while (!container.empty()) {
        int u = container.back();
        container.pop_back();
        for (int w : adj[u]) {
            if (!marked[w]) {
                marked[w] = true;
                container.push_back(w);
            }
        }
    }
    return marked;
}
// snippet:end

// The same loop with a queue; the marked set must not change (Theorem 4.1.1 allows any container).
vector<bool> reachableQueue(const vector<vector<int>>& adj, int s) {
    vector<bool> marked(adj.size(), false);
    queue<int> q;
    q.push(s);
    marked[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int w : adj[u]) {
            if (!marked[w]) {
                marked[w] = true;
                q.push(w);
            }
        }
    }
    return marked;
}

string show(const vector<bool>& marked) {
    string out = "{";
    bool first = true;
    for (size_t v = 1; v < marked.size(); v++) {
        if (!marked[v]) continue;
        if (!first) out += ", ";
        out += to_string(v);
        first = false;
    }
    return out + "}";
}

int main() {
    // Examples, in the order shown in the lesson.
    {
        vector<vector<int>> adj(7);
        int edges[4][2] = {{1, 2}, {2, 3}, {1, 3}, {4, 5}};
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        cout << "n=6, edges 1-2 2-3 1-3 4-5: from 1 reaches " << show(reachable(adj, 1)) << "\n";
        cout << "n=6, edges 1-2 2-3 1-3 4-5: from 4 reaches " << show(reachable(adj, 4)) << "\n";
    }
    {
        vector<vector<int>> adj(4);
        adj[1].push_back(2);
        adj[3].push_back(2);
        cout << "n=3, arrows 1>2 3>2: from 3 reaches " << show(reachable(adj, 3)) << "; from 2 reaches " << show(reachable(adj, 2)) << "\n";
    }
    // Check against the transitive closure on every graph with 4 vertices (undirected: 2^6, directed: 2^12).
    for (int directed = 0; directed < 2; directed++) {
        int n = 4;
        vector<pair<int, int>> pairs;
        for (int a = 1; a <= n; a++)
            for (int b = 1; b <= n; b++)
                if (directed ? a != b : a < b) pairs.push_back({a, b});
        for (int mask = 0; mask < (1 << pairs.size()); mask++) {
            vector<vector<int>> adj(n + 1);
            bool closure[5][5] = {};
            for (int v = 1; v <= n; v++) closure[v][v] = true;
            for (size_t i = 0; i < pairs.size(); i++) {
                if (!(mask >> i & 1)) continue;
                auto [a, b] = pairs[i];
                adj[a].push_back(b);
                closure[a][b] = true;
                if (!directed) {
                    adj[b].push_back(a);
                    closure[b][a] = true;
                }
            }
            for (int k = 1; k <= n; k++)
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= n; j++)
                        if (closure[i][k] && closure[k][j]) closure[i][j] = true;
            for (int s = 1; s <= n; s++) {
                vector<bool> got = reachable(adj, s), gotQueue = reachableQueue(adj, s);
                for (int v = 1; v <= n; v++)
                    if (got[v] != closure[s][v] || gotQueue[v] != closure[s][v]) return 1;
            }
        }
    }
}
