#include <bits/stdc++.h>
using namespace std;

/*
Problem: AtCoder DP V, Subtree. A tree of n vertices (n up to 10^5) and a modulus M (any number from 2 to 10^9). For every vertex v,
count the ways to paint some vertices black so that the black vertices form a connected set that contains v; print it modulo M.
Input: n, M, then the n - 1 edges.
Output: n lines.
*/

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

// snippet:begin
// Theorem 7.1.3: down[v] = ways inside the subtree of v; up[c] = ways for the part above c as seen from its parent p. Prefix and
// suffix products over the children take one child out without a division (M need not be a prime).
vector<long long> countConnectedSets(const Rooted& t, long long M) {
    vector<long long> down(t.n, 1 % M), up(t.n, 0), answer(t.n);
    for (int i = t.n - 1; i >= 0; i--)
        for (int c : t.children[t.order[i]]) down[t.order[i]] = down[t.order[i]] * ((down[c] + 1) % M) % M;
    for (int v : t.order) {
        int k = t.children[v].size();
        vector<long long> suffix(k + 1, 1 % M);
        for (int i = k - 1; i >= 0; i--) suffix[i] = suffix[i + 1] * ((down[t.children[v][i]] + 1) % M) % M;
        long long prefix = (up[v] + 1) % M;
        for (int i = 0; i < k; i++) {
            int c = t.children[v][i];
            up[c] = prefix * suffix[i + 1] % M;
            prefix = prefix * ((down[c] + 1) % M) % M;
        }
        answer[v] = down[v] * ((up[v] + 1) % M) % M;
    }
    return answer;
}
// snippet:end

int main() {
    int n;
    long long M;
    cin >> n >> M;
    vector<pair<int, int>> edges(n - 1);
    for (auto& [a, b] : edges) cin >> a >> b, a--, b--;
    Rooted t(n, edges);
    for (long long x : countConnectedSets(t, M)) cout << x << "\n";
}
