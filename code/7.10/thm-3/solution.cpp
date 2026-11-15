#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 7.10.3. edges[i] = {u, v} is the directed edge u -> v of a tree. r[v] = the fewest edges to reverse so that every
// vertex can be reached from v: the number of edges that point toward v.
vector<int> reversalsFromEach(int n, const vector<pair<int, int>>& edges) {
    vector<vector<pair<int, int>>> adj(n);  // (neighbour, +1 if the edge leaves this vertex, -1 if it enters it)
    for (auto [u, v] : edges) adj[u].push_back({v, 1}), adj[v].push_back({u, -1});
    vector<int> r(n, 0), parent(n, -1), step(n, 0), order = {0};
    for (size_t i = 0; i < order.size(); i++) {
        int p = order[i];
        for (auto [c, dir] : adj[p]) {
            if (c == parent[p]) continue;
            parent[c] = p, step[c] = dir, order.push_back(c);
            if (dir < 0) r[0]++;  // the edge c -> p points toward the root 0
        }
    }
    for (int i = 1; i < n; i++) r[order[i]] = r[parent[order[i]]] + step[order[i]];  // one edge changes its meaning
    return r;
}
// snippet:end

int main() {
    auto show = [](int n, vector<pair<int, int>> edges, const char* name) {
        cout << name << ":";
        for (int x : reversalsFromEach(n, edges)) cout << " " << x;
        cout << "\n";
    };
    show(3, {{0, 1}, {1, 2}}, "0->1, 1->2");
    show(4, {{1, 0}, {2, 0}, {0, 3}}, "1->0, 2->0, 0->3");
    show(4, {{0, 1}, {2, 1}, {2, 3}}, "0->1, 2->1, 2->3");
    // Check (not printed): for every labelled tree with 2 to 6 vertices (all Prüfer sequences) and every choice of directions,
    // the result equals the number of edges that point toward v, counted by a search from v.
    for (int n = 2; n <= 6; n++) {
        int seqs = 1;
        for (int i = 0; i < n - 2; i++) seqs *= n;
        for (int code = 0; code < seqs; code++) {
            vector<int> prufer(n - 2), degree(n, 1);
            for (int i = 0, c = code; i < n - 2; i++, c /= n) prufer[i] = c % n, degree[prufer[i]]++;
            vector<pair<int, int>> tree;
            for (int x : prufer) {
                for (int leaf = 0; leaf < n; leaf++)
                    if (degree[leaf] == 1) {
                        tree.push_back({leaf, x}), degree[leaf]--, degree[x]--;
                        break;
                    }
            }
            vector<int> last;
            for (int v = 0; v < n; v++)
                if (degree[v] == 1) last.push_back(v);
            tree.push_back({last[0], last[1]});
            for (int dirs = 0; dirs < (1 << (n - 1)); dirs++) {
                vector<pair<int, int>> edges = tree;
                for (int i = 0; i < n - 1; i++)
                    if (dirs >> i & 1) swap(edges[i].first, edges[i].second);
                vector<int> got = reversalsFromEach(n, edges);
                for (int v = 0; v < n; v++) {
                    int count = 0;
                    function<void(int, int)> go = [&](int x, int p) {
                        for (auto [a, b] : edges) {
                            if (a == x && b != p) go(b, x);                // the edge x -> b points away from v
                            else if (b == x && a != p) count++, go(a, x);  // the edge a -> x points toward v
                        }
                    };
                    go(v, -1);
                    if (got[v] != count) return 1;
                }
            }
        }
    }
}
