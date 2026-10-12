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

const long long NEG = LLONG_MIN / 4;
// snippet:begin
// Theorem 7.1.4. dp[v][j] = the largest sum of a connected set that contains v, lies in the subtree of v and has j vertices.
// Merging a child costs (vertices merged so far) * (size of the child); in all n(n-1)/2 steps. work counts them.
vector<long long> bestConnected(const vector<vector<int>>& children, const vector<int>& order, const vector<long long>& w, long long& work) {
    int n = order.size();
    vector<vector<long long>> dp(n);
    work = 0;
    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        dp[v] = {NEG, w[v]};  // index 0 is unused: a set that contains v has at least one vertex
        for (int c : children[v]) {
            vector<long long> merged(dp[v].size() + dp[c].size() - 1, NEG);
            for (size_t a = 1; a < dp[v].size(); a++) {
                merged[a] = max(merged[a], dp[v][a]);  // nothing is taken from the subtree of c
                for (size_t b = 1; b < dp[c].size(); b++, work++) merged[a + b] = max(merged[a + b], dp[v][a] + dp[c][b]);
            }
            dp[v] = merged;
        }
    }
    return dp[order[0]];
}
// snippet:end

vector<pair<int, int>> sampleEdges = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};

// All connected sets that contain the vertex 0, found by trying every subset.
vector<long long> bruteConnected(int n, const vector<pair<int, int>>& edges, const vector<long long>& w) {
    vector<long long> best(n + 1, NEG);
    for (int mask = 1; mask < (1 << n); mask++) {
        if (!(mask & 1)) continue;
        vector<int> seen(n, 0), stack = {0};
        seen[0] = 1;
        int reached = 1;
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            for (auto [a, b] : edges) {
                int u = a == v ? b : b == v ? a : -1;
                if (u >= 0 && (mask >> u & 1) && !seen[u]) seen[u] = 1, reached++, stack.push_back(u);
            }
        }
        if (reached != __builtin_popcount(mask)) continue;
        long long sum = 0;
        for (int v = 0; v < n; v++)
            if (mask >> v & 1) sum += w[v];
        best[reached] = max(best[reached], sum);
    }
    return best;
}

int main() {
    Rooted t(5, sampleEdges);
    long long work;
    auto dp = bestConnected(t.children, t.order, {1, -5, -5, 10, 10}, work);
    cout << "sample tree with values 1 -5 -5 10 10, best connected set containing the root with j vertices:";
    for (size_t j = 1; j < dp.size(); j++) cout << " " << dp[j];
    cout << "\nmerging steps " << work << " = 5 * 4 / 2\n";
    // Check (not printed): the same as trying all subsets, and work = n(n-1)/2, for 2000 random trees of up to 11 vertices.
    mt19937 rng(17);
    for (int it = 0; it < 2000; it++) {
        int n = 1 + rng() % 11;
        auto edges = randomTree(n, rng);
        Rooted r(n, edges);
        vector<long long> vals(n);
        for (auto& x : vals) x = (int)(rng() % 21) - 10;
        auto got = bestConnected(r.children, r.order, vals, work);
        auto want = bruteConnected(n, edges, vals);
        if (work != (long long)n * (n - 1) / 2) return 1;
        for (int j = 1; j <= n; j++)
            if (got[j] != want[j]) return 1;
    }
}
