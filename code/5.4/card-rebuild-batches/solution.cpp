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

int main() {
    // P1: the path 0-1-2-3-4-5, batches of 2: paint 0 and 5 (rebuild), then 2 (pending); the distance from 3 to the nearest painted vertex.
    {
        Tree t(6);
        for (int i = 0; i + 1 < 6; i++) t.addEdge(i, i + 1);
        t.root();
        NearestMarked m(t, 2);
        for (int v : {0, 5, 2}) m.mark(v);
        int brute = INF;
        for (int v : {0, 5, 2}) brute = min(brute, t.dist(3, v));
        cout << "P1 brute=" << brute << " method=" << m.ask(3) << "\n";
    }
    // N1: the path 0-1-2-3-4, batches of 2: paint 0 and 4 (rebuild), then 0 is painted over (removed); the distance from 1 to the nearest painted vertex.
    // The table was built with vertex 0 and does not know about the removal.
    {
        Tree t(5);
        for (int i = 0; i + 1 < 5; i++) t.addEdge(i, i + 1);
        t.root();
        NearestMarked m(t, 2);
        for (int v : {0, 4}) m.mark(v);
        cout << "N1 brute=" << t.dist(1, 4) << " method=" << m.ask(1) << "\n";
    }
}
