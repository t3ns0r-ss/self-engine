#include <bits/stdc++.h>
using namespace std;

/*
Problem: CF 1324F style. A tree of n vertices (n up to 2·10^5), an integer value on each vertex. For every vertex v print the
largest sum of the values of a connected set of vertices that contains v.
Input: n, the n values, then the n - 1 edges.
Output: n numbers on one line.
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
// Theorem 7.1.3, with the contribution of one child taken out of its parent. down[v] = w[v] + the child values that are above 0.
// answer[c] = down[c] + the part above c, which is answer[p] without what c itself gave to p.
vector<long long> bestSubtreeForEach(const Rooted& t, const vector<long long>& w) {
    vector<long long> down(w), answer(t.n);
    for (int i = t.n - 1; i > 0; i--) {
        int v = t.order[i];
        down[t.parent[v]] += max(0LL, down[v]);
    }
    answer[0] = down[0];
    for (int i = 1; i < t.n; i++) {
        int c = t.order[i], p = t.parent[c];
        answer[c] = down[c] + max(0LL, answer[p] - max(0LL, down[c]));
    }
    return answer;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> w(n);
    for (auto& x : w) cin >> x;
    vector<pair<int, int>> edges(n - 1);
    for (auto& [a, b] : edges) cin >> a >> b, a--, b--;
    Rooted t(n, edges);
    vector<long long> answer = bestSubtreeForEach(t, w);
    for (int v = 0; v < n; v++) cout << answer[v] << (v + 1 < n ? " " : "\n");
}
