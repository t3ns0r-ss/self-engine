#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Tree {
    int n;
    vector<vector<int>> adj;
    vector<int> parent, depth;
    Tree(int vertices) : n(vertices), adj(vertices), parent(vertices, -1), depth(vertices, 0) {}
    void addEdge(int u, int v) { adj[u].push_back(v), adj[v].push_back(u); }
    void root() {  // parents and depths from vertex 0
        vector<int> order = {0};
        for (size_t i = 0; i < order.size(); i++)
            for (int w : adj[order[i]])
                if (w != parent[order[i]]) parent[w] = order[i], depth[w] = depth[order[i]] + 1, order.push_back(w);
    }
    int dist(int u, int v) const {  // by climbing; topic 4.6 does this in O(log n)
        int d = 0;
        while (u != v) {
            if (depth[u] < depth[v]) swap(u, v);
            u = parent[u], d++;
        }
        return d;
    }
};

// snippet:begin
// Theorem 5.4.5. The distance to the nearest marked vertex of a tree, with marks added one at a time.
struct NearestMarked {
    const Tree& tree;
    int B;                        // rebuild after every B new marks
    vector<int> best;             // distance to the nearest vertex marked before the last rebuild
    vector<int> marked, pending;  // all marked vertices; the marks since the last rebuild
    NearestMarked(const Tree& t, int batch) : tree(t), B(batch), best(t.n, INF) {}
    void mark(int v) {
        marked.push_back(v);
        pending.push_back(v);
        if ((int)pending.size() == B) rebuild();
    }
    void rebuild() {  // a search that starts from every marked vertex at once
        fill(best.begin(), best.end(), INF);
        queue<int> bfs;
        for (int v : marked) best[v] = 0, bfs.push(v);
        for (; !bfs.empty(); bfs.pop())
            for (int w : tree.adj[bfs.front()])
                if (best[w] == INF) best[w] = best[bfs.front()] + 1, bfs.push(w);
        pending.clear();
    }
    int ask(int v) const {
        int answer = best[v];
        for (int m : pending) answer = min(answer, tree.dist(v, m));  // fewer than B of them
        return answer;
    }
};
// snippet:end

int main() {
    Tree path(7);
    for (int i = 0; i + 1 < 7; i++) path.addEdge(i, i + 1);
    path.root();
    NearestMarked s(path, 2);
    cout << "path of 7 vertices, B = 2\n";
    s.mark(0);
    cout << "mark 0, ask 3 = " << s.ask(3) << "\n";
    s.mark(6);
    cout << "mark 6 (rebuild), best =";
    for (int v = 0; v < 7; v++) cout << ' ' << s.best[v];
    cout << "\n";
    cout << "ask 5 = " << s.ask(5) << "\n";
    s.mark(3);
    cout << "mark 3, ask 2 = " << s.ask(2) << ", ask 3 = " << s.ask(3) << "\n";
    // Check against: the distance to every marked vertex, on random trees, batch sizes and operation lists.
    mt19937 rng(5);
    for (int round = 0; round < 3000; round++) {
        int n = rng() % 12 + 1;
        Tree t(n);
        for (int v = 1; v < n; v++) t.addEdge(v, rng() % v);
        t.root();
        int batch = rng() % 5 + 1;
        NearestMarked m(t, batch);
        vector<int> all;
        for (int step = 0; step < 30; step++) {
            int v = rng() % n;
            if (rng() % 2) {
                m.mark(v), all.push_back(v);
            } else {
                int want = INF;
                for (int x : all) want = min(want, t.dist(v, x));
                if (m.ask(v) != want) return 1;
            }
        }
    }
}
