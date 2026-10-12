#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1133, Tree Distances II. A tree of n vertices (n up to 2·10^5). For every vertex print the sum of the distances from
it to all other vertices.
Input: n, then the n - 1 edges.
Output: n numbers on one line (they need 64 bits).
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
// Moving the root from p to a child c: the size[c] vertices below c get one step closer, the other n - size[c] one step farther
// (Theorem 7.1.3 with the sum as the rule). So answer[c] = answer[p] + n - 2 * size[c].
vector<long long> distanceSums(const Rooted& t) {
    int n = t.n;
    vector<long long> size(n, 1), depth(n, 0), answer(n);
    for (int i = n - 1; i > 0; i--) size[t.parent[t.order[i]]] += size[t.order[i]];
    for (int i = 1; i < n; i++) depth[t.order[i]] = depth[t.parent[t.order[i]]] + 1;
    answer[0] = accumulate(depth.begin(), depth.end(), 0LL);  // the sum of distances from the root is the sum of depths
    for (int i = 1; i < n; i++) {
        int c = t.order[i];
        answer[c] = answer[t.parent[c]] + n - 2 * size[c];
    }
    return answer;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> edges(n - 1);
    for (auto& [a, b] : edges) cin >> a >> b, a--, b--;
    Rooted t(n, edges);
    vector<long long> answer = distanceSums(t);
    for (int v = 0; v < n; v++) cout << answer[v] << (v + 1 < n ? " " : "\n");
}
