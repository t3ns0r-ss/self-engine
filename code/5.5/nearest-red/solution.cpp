#include <bits/stdc++.h>
using namespace std;

/*
Problem: a tree of n vertices; vertex 1 is red at the start. q operations: "1 v" paints v red, "2 v" asks the distance from v to the nearest red vertex.
Input: n q, then n - 1 edges, then q lines "type v".
Output: one line per question, in the order of the input.
*/

const int INF = 1e9;

struct Tree {
    int n, LOG = 1;
    vector<vector<int>> adj, up;  // up[j][v] is the 2^j-th ancestor (topic 4.7)
    vector<int> depth;
    Tree(int vertices) : n(vertices), adj(vertices), depth(vertices, 0) {
        while ((1 << LOG) < n) LOG++;
    }
    void addEdge(int u, int v) { adj[u].push_back(v), adj[v].push_back(u); }
    void root() {
        up.assign(LOG, vector<int>(n, 0));
        vector<int> order = {0};
        for (size_t i = 0; i < order.size(); i++)
            for (int w : adj[order[i]])
                if (w != up[0][order[i]]) up[0][w] = order[i], depth[w] = depth[order[i]] + 1, order.push_back(w);
        for (int j = 1; j < LOG; j++)
            for (int v = 0; v < n; v++) up[j][v] = up[j - 1][up[j - 1][v]];
    }
    int dist(int u, int v) const {
        int a = u, b = v;
        if (depth[a] < depth[b]) swap(a, b);
        for (int j = LOG - 1; j >= 0; j--)
            if (depth[a] - (1 << j) >= depth[b]) a = up[j][a];
        if (a != b) {
            for (int j = LOG - 1; j >= 0; j--)
                if (up[j][a] != up[j][b]) a = up[j][a], b = up[j][b];
            a = up[0][a];
        }
        return depth[u] + depth[v] - 2 * depth[a];
    }
};

// snippet:begin
// The nearest red vertex of a tree: the table is rebuilt by a search from all red vertices after every B new ones.
struct NearestRed {
    const Tree& tree;
    int B;
    vector<int> best, red, pending;  // best: distance to the nearest red vertex at the last rebuild
    NearestRed(const Tree& t, int batch) : tree(t), B(batch), best(t.n, INF) {}
    void paint(int v) {
        red.push_back(v);
        pending.push_back(v);
        if ((int)pending.size() == B) rebuild();
    }
    void rebuild() {
        fill(best.begin(), best.end(), INF);
        queue<int> bfs;
        for (int v : red) best[v] = 0, bfs.push(v);
        for (; !bfs.empty(); bfs.pop())
            for (int w : tree.adj[bfs.front()])
                if (best[w] == INF) best[w] = best[bfs.front()] + 1, bfs.push(w);
        pending.clear();
    }
    int ask(int v) const {
        int answer = best[v];
        for (int m : pending) answer = min(answer, tree.dist(v, m));
        return answer;
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    Tree t(n);
    for (int i = 0; i + 1 < n; i++) {
        int u, v;
        cin >> u >> v;
        t.addEdge(u - 1, v - 1);
    }
    t.root();
    NearestRed red(t, max(1, (int)sqrt((double)q)));
    red.paint(0);
    while (q--) {
        int type, v;
        cin >> type >> v;
        if (type == 1) red.paint(v - 1);
        else cout << red.ask(v - 1) << "\n";
    }
}
