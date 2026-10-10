#include <bits/stdc++.h>
using namespace std;

struct Rooted {
    vector<int> order, parent, depth;
};
Rooted rootAt(const vector<vector<int>>& adj, int root) {
    int n = adj.size() - 1;
    Rooted t{{}, vector<int>(n + 1, 0), vector<int>(n + 1, 0)};
    vector<int> stack = {root};
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        t.order.push_back(u);
        for (int v : adj[u])
            if (v != t.parent[u]) {  // in a tree the only visited neighbour of u is its parent
                t.parent[v] = u;
                t.depth[v] = t.depth[u] + 1;
                stack.push_back(v);
            }
    }
    return t;
}

struct Lifting {
    vector<vector<int>> up;  // up[j][v]: the 2^j-th ancestor of v, or 0 if there is none (up[j][0] = 0)
    vector<int> depth;
    Lifting(const vector<vector<int>>& adj, int root) {
        int n = adj.size() - 1, levels = 1;
        while ((1 << levels) <= n) levels++;
        Rooted t = rootAt(adj, root);
        depth = t.depth;
        up.assign(levels, t.parent);  // up[0] is the parent
        for (int j = 1; j < levels; j++)
            for (int v = 1; v <= n; v++) up[j][v] = up[j - 1][up[j - 1][v]];  // two jumps of 2^(j-1)
    }
    int kthAncestor(int v, int k) const {  // 0 if v has fewer than k ancestors
        if (k > depth[v]) return 0;
        for (int j = 0; j < (int)up.size(); j++)
            if (k >> j & 1) v = up[j][v];
        return v;
    }
};

int lca(const Lifting& L, int u, int v) {
    if (L.depth[u] < L.depth[v]) swap(u, v);
    u = L.kthAncestor(u, L.depth[u] - L.depth[v]);
    if (u == v) return u;
    for (int j = (int)L.up.size() - 1; j >= 0; j--)
        if (L.up[j][u] != L.up[j][v]) u = L.up[j][u], v = L.up[j][v];  // still below the meeting point: take the jump
    return L.up[0][u];
}

int main() {
    // P1: the smallest edge weight on the path from 3 to 5 in the tree 1-2 (3), 2-3 (4), 2-4 (1), 4-5 (6), 1-6 (2).
    // Brute force: walk the path from 3 and keep the smallest weight; method: the table of minima over the jumps.
    {
        vector<array<int, 3>> edges = {{1, 2, 3}, {2, 3, 4}, {2, 4, 1}, {4, 5, 6}, {1, 6, 2}};
        int n = 6;
        vector<vector<int>> adj(n + 1);
        for (auto [a, b, w] : edges) adj[a].push_back(b), adj[b].push_back(a);
        auto t = rootAt(adj, 1);
        Lifting L(adj, 1);
        const long long INF = LLONG_MAX / 4;
        vector<long long> w0(n + 1, INF);
        for (int v : t.order) if (t.parent[v]) for (auto [a, b, w] : edges) if ((a == v && b == t.parent[v]) || (b == v && a == t.parent[v])) w0[v] = w;
        vector<vector<long long>> mn(L.up.size(), w0);
        for (size_t j = 1; j < mn.size(); j++) for (int v = 1; v <= n; v++) { int mid = L.up[j - 1][v]; mn[j][v] = mid == 0 ? mn[j - 1][v] : min(mn[j - 1][v], mn[j - 1][mid]); }
        auto query = [&](int u, int v) {
            long long best = INF;
            if (L.depth[u] < L.depth[v]) swap(u, v);
            for (int j = 0; j < (int)mn.size(); j++) if ((L.depth[u] - L.depth[v]) >> j & 1) best = min(best, mn[j][u]), u = L.up[j][u];
            if (u == v) return best;
            for (int j = (int)mn.size() - 1; j >= 0; j--) if (L.up[j][u] != L.up[j][v]) best = min({best, mn[j][u], mn[j][v]}), u = L.up[j][u], v = L.up[j][v];
            return min({best, mn[0][u], mn[0][v]});
        };
        long long brute = INF;
        vector<int> stack = {3};
        vector<long long> low(n + 1, -1);
        low[3] = INF;
        while (!stack.empty()) {
            int x = stack.back();
            stack.pop_back();
            for (auto [a, b, w] : edges) {
                int y = a == x ? b : (b == x ? a : 0);
                if (y && low[y] < 0) low[y] = min<long long>(low[x], w), stack.push_back(y);
            }
        }
        brute = low[5];
        cout << "P1 brute=" << brute << " method=" << query(3, 5) << "\n";
    }
    // P2: a dish with candies; K = 5 steps, A = (1, 2, 3): each step puts A[X mod 3] more candies on the dish, X being the number there.
    // Brute force: simulate. Method: the position X mod N is the vertex, the next vertex is (X + A) mod N, and the jump table also sums the gains.
    {
        vector<long long> A = {1, 2, 3};
        int N = 3, K = 5, levels = 3;
        long long X = 0;
        for (int i = 0; i < K; i++) X += A[X % N];
        vector<vector<int>> next(levels, vector<int>(N));
        vector<vector<long long>> gain(levels, vector<long long>(N));
        for (int v = 0; v < N; v++) next[0][v] = (v + A[v]) % N, gain[0][v] = A[v];
        for (int j = 1; j < levels; j++) for (int v = 0; v < N; v++) { int mid = next[j - 1][v]; next[j][v] = next[j - 1][mid]; gain[j][v] = gain[j - 1][v] + gain[j - 1][mid]; }
        long long total = 0;
        int v = 0;
        for (int j = 0; j < levels; j++) if (K >> j & 1) total += gain[j][v], v = next[j][v];
        cout << "P2 brute=" << X << " method=" << total << "\n";
    }
    // N1: the triangle 1-2 (5), 2-3 (5), 1-3 (1) is a graph with a cycle. The best trip from 2 to 3 (the largest smallest edge) is the edge 2-3 (5).
    // A table on the tree of a walk from vertex 1 (edges 1-2 and 1-3) says min(5, 1) = 1.
    {
        int direct = 5, throughOne = min(5, 1);  // the two routes from 2 to 3 and their smallest edges
        int bestRoute = max(direct, throughOne);
        vector<vector<int>> tree(4);
        tree[1] = {2, 3}, tree[2] = {1}, tree[3] = {1};
        long long w[4] = {0, 0, 5, 1};  // weight of the edge from the vertex to its parent 1
        cout << "N1 brute=" << bestRoute << " method=" << min(w[2], w[3]) << "\n";
    }
}
