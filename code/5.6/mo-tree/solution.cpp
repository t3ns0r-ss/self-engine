#include <bits/stdc++.h>
using namespace std;

/*
Problem: a tree of n vertices with a colour on each; q questions (u, v): the number of colours that occur exactly once among the vertices of the path from u to v.
Input: n q, the n colours, n - 1 edges, then q lines u v (1-based).
Output: one line per question, in the order of the input.
*/

struct Tree {
    int n, LOG = 1;
    vector<vector<int>> adj, up;  // up[j][v] is the 2^j-th ancestor of v (topic 4.6)
    vector<int> depth, tin, tout, euler;  // euler lists every vertex twice: when it is entered and when it is left
    Tree(int vertices) : n(vertices), adj(vertices), depth(vertices, 0), tin(vertices), tout(vertices) {
        while ((1 << LOG) < n) LOG++;
    }
    void addEdge(int u, int v) { adj[u].push_back(v), adj[v].push_back(u); }
    void walk() {  // an iterative walk from vertex 0
        up.assign(LOG, vector<int>(n, 0));
        vector<int> next(n, 0), stack = {0};
        tin[0] = 0, euler.push_back(0);
        while (!stack.empty()) {
            int v = stack.back();
            if (next[v] < (int)adj[v].size()) {
                int w = adj[v][next[v]++];
                if (w == up[0][v] && v != 0) continue;
                up[0][w] = v, depth[w] = depth[v] + 1, tin[w] = euler.size(), euler.push_back(w), stack.push_back(w);
            } else {
                tout[v] = euler.size(), euler.push_back(v), stack.pop_back();
            }
        }
        for (int j = 1; j < LOG; j++)
            for (int v = 0; v < n; v++) up[j][v] = up[j - 1][up[j - 1][v]];
    }
    int lca(int u, int v) const {
        if (depth[u] < depth[v]) swap(u, v);
        for (int j = LOG - 1; j >= 0; j--)
            if (depth[u] - (1 << j) >= depth[v]) u = up[j][u];
        if (u == v) return u;
        for (int j = LOG - 1; j >= 0; j--)
            if (up[j][u] != up[j][v]) u = up[j][u], v = up[j][v];
        return up[0][u];
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

// snippet:begin
// Mo's algorithm on a tree: each path is a range of the Euler order, and a vertex seen twice cancels itself.
vector<int> coloursSeenOnce(const Tree& t, const vector<int>& colour, const vector<array<int, 2>>& paths) {
    vector<array<int, 2>> ranges;
    vector<int> extra;  // the lowest common ancestor when it is not inside the range, else -1
    for (auto [u, v] : paths) {
        if (t.tin[u] > t.tin[v]) swap(u, v);
        int w = t.lca(u, v);
        if (w == u) ranges.push_back({t.tin[u], t.tin[v]}), extra.push_back(-1);
        else ranges.push_back({t.tout[u], t.tin[v]}), extra.push_back(w);
    }
    vector<int> cnt(*max_element(colour.begin(), colour.end()) + 1, 0), inside(t.n, 0), answer(paths.size());
    int once = 0;  // the number of colours with exactly one vertex in the window
    auto flip = [&](int x) {
        int c = colour[x];
        if (inside[x] ^= 1) {
            once += cnt[c] == 0, once -= cnt[c] == 1, cnt[c]++;
        } else {
            cnt[c]--, once += cnt[c] == 1, once -= cnt[c] == 0;
        }
    };
    int l = 0, r = -1;
    for (int q : moOrder(ranges, 2 * t.n)) {
        while (l > ranges[q][0]) flip(t.euler[--l]);
        while (r < ranges[q][1]) flip(t.euler[++r]);
        while (l < ranges[q][0]) flip(t.euler[l++]);
        while (r > ranges[q][1]) flip(t.euler[r--]);
        if (extra[q] >= 0) flip(extra[q]);
        answer[q] = once;
        if (extra[q] >= 0) flip(extra[q]);
    }
    return answer;
}
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> colour(n);
    for (int& c : colour) cin >> c;
    Tree t(n);
    for (int i = 0; i + 1 < n; i++) {
        int u, v;
        cin >> u >> v;
        t.addEdge(u - 1, v - 1);
    }
    t.walk();
    vector<array<int, 2>> paths(q);
    for (auto& p : paths) cin >> p[0] >> p[1], p[0]--, p[1]--;
    for (int x : coloursSeenOnce(t, colour, paths)) cout << x << "\n";
}
