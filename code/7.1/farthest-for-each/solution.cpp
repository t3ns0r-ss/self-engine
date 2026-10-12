#include <bits/stdc++.h>
using namespace std;

/*
Problem: a tree of n vertices (n up to 2·10^5). For every vertex print the distance to the farthest vertex.
Input: n, then the n - 1 edges.
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
// Theorem 7.1.3 for a maximum, which has no inverse: the two best downward values of every vertex tell what remains when one
// child is left out. down[v] = the height of the subtree; up[c] = the longest path that leaves c through its parent.
vector<int> farthestForEach(const Rooted& t) {
    vector<int> down(t.n, 0), up(t.n, 0), answer(t.n);
    for (int i = t.n - 1; i > 0; i--) {
        int v = t.order[i];
        down[t.parent[v]] = max(down[t.parent[v]], down[v] + 1);
    }
    for (int v : t.order) {
        int best1 = up[v], best2 = 0;  // the two longest ways out of v, one of them may be the way up
        for (int c : t.children[v]) {
            int d = down[c] + 1;
            if (d > best1) best2 = best1, best1 = d;
            else best2 = max(best2, d);
        }
        answer[v] = best1;
        for (int c : t.children[v]) up[c] = 1 + (down[c] + 1 == best1 ? best2 : best1);  // leave c's own way out
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
    vector<int> answer = farthestForEach(t);
    for (int v = 0; v < n; v++) cout << answer[v] << (v + 1 < n ? " " : "\n");
}
