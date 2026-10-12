#include <bits/stdc++.h>
using namespace std;

/*
Problem: LeetCode 1530, Number of Good Leaf Nodes Pairs (written for any rooted tree). A tree rooted at the vertex 1 and a number
distance (1 to 10). A leaf is a vertex other than the root that has no children. Count the pairs of leaves whose distance is at most
distance.
Input: n, distance, then the n - 1 edges.
Output: the number of good pairs.
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
// Theorem 7.1.2 with counts: below[v][x] = the number of leaves at distance x under v. Every pair of leaves has a top vertex v
// where the two paths go into different children; there the pairs are counted by the two distances, and then v's counts are updated.
long long goodLeafPairs(const Rooted& t, int distance) {
    vector<vector<long long>> below(t.n, vector<long long>(distance + 1, 0));
    long long pairs = 0;
    for (int i = t.n - 1; i >= 0; i--) {
        int v = t.order[i];
        if (i > 0 && t.children[v].empty()) below[v][0] = 1;
        for (int c : t.children[v]) {
            for (int x = 0; x < distance; x++)  // from v, a leaf of c is one step farther
                for (int y = 0; x + y + 1 <= distance; y++) pairs += below[v][y] * below[c][x];
            for (int x = 0; x < distance; x++) below[v][x + 1] += below[c][x];
        }
    }
    return pairs;
}
// snippet:end

int main() {
    int n, distance;
    cin >> n >> distance;
    vector<pair<int, int>> edges(n - 1);
    for (auto& [a, b] : edges) cin >> a >> b, a--, b--;
    Rooted t(n, edges);
    cout << goodLeafPairs(t, distance) << "\n";
}
