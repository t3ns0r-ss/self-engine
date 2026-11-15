#include <bits/stdc++.h>
using namespace std;

struct Tree {
    int n, timer = 0;
    vector<vector<int>> adj;
    vector<int> parent, depth, tin, tout, euler;  // euler lists every vertex twice: when it is entered and when it is left
    Tree(int vertices) : n(vertices), adj(vertices), parent(vertices, -1), depth(vertices, 0), tin(vertices), tout(vertices) {}
    void addEdge(int u, int v) { adj[u].push_back(v), adj[v].push_back(u); }
    void walk(int v) {
        tin[v] = timer++, euler.push_back(v);
        for (int w : adj[v])
            if (w != parent[v]) parent[w] = v, depth[w] = depth[v] + 1, walk(w);
        tout[v] = timer++, euler.push_back(v);
    }
    int lca(int u, int v) const {  // by climbing; topic 4.6 does this in O(log n)
        while (u != v) {
            if (depth[u] < depth[v]) swap(u, v);
            u = parent[u];
        }
        return u;
    }
};

vector<int> moOrder(const vector<array<int, 2>>& queries, int n) {
    int B = max(1, (int)(n / sqrt((double)max<size_t>(1, queries.size()))));
    vector<int> order(queries.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int x, int y) {
        int bx = queries[x][0] / B, by = queries[y][0] / B;
        if (bx != by) return bx < by;
        return bx % 2 == 0 ? queries[x][1] < queries[y][1] : queries[x][1] > queries[y][1];
    });
    return order;
}

// The range of the Euler order for the path from u to v, and the vertex that must be added on its own (or -1).
pair<array<int, 2>, int> pathRange(const Tree& t, int u, int v) {
    if (t.tin[u] > t.tin[v]) swap(u, v);
    int w = t.lca(u, v);
    if (w == u) return {{t.tin[u], t.tin[v]}, -1};
    return {{t.tout[u], t.tin[v]}, w};
}

// snippet:begin
// Theorem 5.6.4. The number of different colours on the path from u to v, for many paths of a tree.
vector<int> pathColours(const Tree& t, const vector<int>& colour, const vector<array<int, 2>>& paths) {
    vector<array<int, 2>> ranges;  // each path as a range of the Euler order
    vector<int> extra;             // the vertex to add on its own, or -1
    for (auto [u, v] : paths) {
        auto [range, w] = pathRange(t, u, v);
        ranges.push_back(range), extra.push_back(w);
    }
    vector<int> cnt(*max_element(colour.begin(), colour.end()) + 1, 0), inside(t.n, 0), answer(paths.size());
    int distinct = 0;
    auto flip = [&](int x) {  // vertex x enters the path or, the second time, leaves it
        if (inside[x] ^= 1) distinct += cnt[colour[x]]++ == 0;
        else distinct -= --cnt[colour[x]] == 0;
    };
    int l = 0, r = -1;
    for (int q : moOrder(ranges, 2 * t.n)) {
        while (l > ranges[q][0]) flip(t.euler[--l]);
        while (r < ranges[q][1]) flip(t.euler[++r]);
        while (l < ranges[q][0]) flip(t.euler[l++]);
        while (r > ranges[q][1]) flip(t.euler[r--]);
        if (extra[q] >= 0) flip(extra[q]);  // the lowest common ancestor is not in the range
        answer[q] = distinct;
        if (extra[q] >= 0) flip(extra[q]);
    }
    return answer;
}
// snippet:end

int main() {
    Tree t(7);
    for (auto [u, v] : vector<array<int, 2>>{{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}}) t.addEdge(u, v);
    t.walk(0);
    cout << "euler:";
    for (int v : t.euler) cout << ' ' << v;
    cout << "\n";
    vector<array<int, 2>> paths = {{3, 6}, {1, 4}, {5, 6}};
    for (auto [u, v] : paths) {
        auto [range, w] = pathRange(t, u, v);
        vector<int> once;
        for (int i = range[0]; i <= range[1]; i++)
            if (count(t.euler.begin() + range[0], t.euler.begin() + range[1] + 1, t.euler[i]) == 1) once.push_back(t.euler[i]);
        sort(once.begin(), once.end());
        cout << "path " << u << "-" << v << ": range [" << range[0] << ", " << range[1] << "], once:";
        for (int x : once) cout << ' ' << x;
        cout << ", extra " << w << "\n";
    }
    cout << "different colours:";
    for (int x : pathColours(t, {1, 2, 3, 1, 2, 3, 4}, paths)) cout << ' ' << x;
    cout << "\n";
    // Check against: walking the path from u to v with the parents, on random trees and colourings, for every pair.
    mt19937 rng(13);
    for (int round = 0; round < 2000; round++) {
        int n = rng() % 10 + 1;
        Tree g(n);
        for (int v = 1; v < n; v++) g.addEdge(v, rng() % v);
        g.walk(0);
        vector<int> colour(n);
        for (int& c : colour) c = rng() % 4;
        vector<array<int, 2>> all;
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++) all.push_back({u, v});
        vector<int> got = pathColours(g, colour, all);
        for (size_t i = 0; i < all.size(); i++) {
            auto [u, v] = all[i];
            int w = g.lca(u, v);
            set<int> seen;
            for (int x = u; x != w; x = g.parent[x]) seen.insert(colour[x]);
            for (int x = v; x != w; x = g.parent[x]) seen.insert(colour[x]);
            seen.insert(colour[w]);
            if ((int)seen.size() != got[i]) return 1;
        }
    }
}
