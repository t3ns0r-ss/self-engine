#include <bits/stdc++.h>
using namespace std;

struct Rooted {
    int n;
    vector<vector<int>> adj, children;
    vector<int> parent, order;
    Rooted(int n, const vector<pair<int, int>>& edges) : n(n), adj(n), children(n), parent(n, -1) {
        for (auto [a, b] : edges) adj[a].push_back(b), adj[b].push_back(a);
        order = {0};
        for (size_t i = 0; i < order.size(); i++) {
            int v = order[i];
            for (int u : adj[v])
                if (u != parent[v]) parent[u] = v, children[v].push_back(u), order.push_back(u);
        }
    }
};
vector<pair<int, int>> randomTree(int n, mt19937& rng) {
    vector<int> label(n);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin(), label.end(), rng);
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) edges.push_back({label[i], label[rng() % i]});
    return edges;
}

// snippet:begin
// Theorem 7.1.2. The largest sum of vertex values on a path (a single vertex is a path).
// down[v] = the best downward path that starts at v; the best path with top v joins the two best children.
long long bestPath(const vector<vector<int>>& children, const vector<int>& order, const vector<long long>& w) {
    int n = order.size();
    vector<long long> down(n);
    long long best = LLONG_MIN;
    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        long long top1 = 0, top2 = 0;  // the two best child paths; 0 means the child is not used
        for (int c : children[v]) {
            long long d = max(0LL, down[c]);
            if (d > top1) top2 = top1, top1 = d;
            else top2 = max(top2, d);
        }
        down[v] = w[v] + top1;
        best = max(best, w[v] + top1 + top2);
    }
    return best;
}
// snippet:end

vector<pair<int, int>> sampleEdges = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};

long long brutePath(int n, const vector<pair<int, int>>& edges, const vector<long long>& w) {
    vector<vector<int>> adj(n);
    for (auto [a, b] : edges) adj[a].push_back(b), adj[b].push_back(a);
    long long best = LLONG_MIN;
    for (int s = 0; s < n; s++) {  // every path is found from each end: depth-first search with the sum so far
        function<void(int, int, long long)> go = [&](int v, int p, long long sum) {
            sum += w[v];
            best = max(best, sum);
            for (int u : adj[v])
                if (u != p) go(u, v, sum);
        };
        go(s, -1, 0);
    }
    return best;
}

int main() {
    Rooted t(5, sampleEdges);
    cout << "values -2 5 1 3 -4: " << bestPath(t.children, t.order, {-2, 5, 1, 3, -4}) << "\n";
    cout << "values -2 -5 -1 -3 -4: " << bestPath(t.children, t.order, {-2, -5, -1, -3, -4}) << "\n";
    cout << "values 0 4 0 0 4: " << bestPath(t.children, t.order, {0, 4, 0, 0, 4}) << "\n";
    // Check (not printed): the same as trying every path, for 3000 random trees of up to 10 vertices with values from -6 to 6.
    mt19937 rng(11);
    for (int it = 0; it < 3000; it++) {
        int n = 1 + rng() % 10;
        auto edges = randomTree(n, rng);
        Rooted r(n, edges);
        vector<long long> w(n);
        for (auto& x : w) x = (int)(rng() % 13) - 6;
        if (bestPath(r.children, r.order, w) != brutePath(n, edges, w)) return 1;
    }
}
